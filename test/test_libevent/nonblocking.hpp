//
// Created by simon on 2020/4/16.
//
#include <netinet/in.h>
/* For socket functions */
#include <sys/socket.h>
/* For fcntl */
#include <fcntl.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include<cassert>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cerrno>

#define MAX_LINE 16384

void do_read(evutil_socket_t fd, short events, void *arg);

void do_write(evutil_socket_t fd, short events, void *arg);

char
rot13_char(char c) {
/* We don’t want to use isalpha here; setting the locale would change
* which characters are considered alphabetical. */
    if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
        return c + 13;
    else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z'))
        return c - 13;
    else
        return c;
}

void
readcb(struct bufferevent *bev, void *ctx) {
    struct evbuffer *input, *output;
    char *line;
    size_t n;
    int i;
    input = bufferevent_get_input(bev);
    output = bufferevent_get_output(bev);
    while ((line = evbuffer_readln(input, &n, EVBUFFER_EOL_LF))) {
        for (i = 0; i < n; ++i)
            line[i] = rot13_char(line[i]);
        evbuffer_add(output, line, n);
        evbuffer_add(output, "\n", 1);
        free(line);
    }
    if (evbuffer_get_length(input) >= MAX_LINE) {
/* Too long; just process what there is and go on so that the buffer
* doesn’t grow infinitely long. */
        char buf[1024];
        while (evbuffer_get_length(input)) {
            int n = evbuffer_remove(input, buf, sizeof(buf));
            for (i = 0; i < n; ++i)
                buf[i] = rot13_char(buf[i]);
            evbuffer_add(output, buf, n);
        }
        evbuffer_add(output, "\n", 1);
    }
}

void
errorcb(struct bufferevent *bev, short error, void *ctx) {
    if (error & BEV_EVENT_EOF) {
/* connection has been closed, do any clean up here */
/* ... */
    } else if (error & BEV_EVENT_ERROR) {
/* check errno to see what error occurred */
/* ... */

    } else if (error & BEV_EVENT_TIMEOUT) {
/* must be a timeout event handle, handle it */
/* ... */
        perror("timeout event handle");
    }
    bufferevent_free(bev);
}

struct fd_state {
    char buffer[MAX_LINE];
    size_t buffer_used;
    size_t n_written;
    size_t write_upto;
    struct event *read_event;
    struct event *write_event;
};

struct fd_state *
alloc_fd_state(struct event_base *base, evutil_socket_t fd) {
    auto *state = static_cast<fd_state *>(malloc(sizeof(struct fd_state)));
    if (!state)
        return nullptr;
    state->read_event = event_new(base, fd, EV_READ | EV_PERSIST, do_read, state);
    if (!state->read_event) {
        free(state);
        return nullptr;
    }
    state->write_event =
            event_new(base, fd, EV_WRITE | EV_PERSIST, do_write, state);
    if (!state->write_event) {
        event_free(state->read_event);
        free(state);
        return nullptr;
    }
    state->buffer_used = state->n_written = state->write_upto = 0;
    assert(state->write_event);
    return state;
}

void
free_fd_state(struct fd_state *state) {
    event_free(state->read_event);
    event_free(state->write_event);
    free(state);
}

void
do_read(evutil_socket_t fd, short events, void *arg) {
    auto *state = static_cast<fd_state *>(arg);
    char buf[1024];
    int i;
    ssize_t result;
    while (1) {
        assert(state->write_event);
        result = recv(fd, buf, sizeof(buf), 0);
        if (result <= 0)
            break;
        for (i = 0; i < result; ++i) {
            if (state->buffer_used < sizeof(state->buffer))
                state->buffer[state->buffer_used++] = rot13_char(buf[i]);
            if (buf[i] == '\n') {
                assert(state->write_event);
                event_add(state->write_event, nullptr);
                state->write_upto = state->buffer_used;
            }
        }
    }
    if (result == 0) {
        free_fd_state(state);
    } else if (result < 0) {
        if (errno == EAGAIN) // XXXX use evutil macro
            return;
        perror("recv");
        free_fd_state(state);
    }
}

void
do_write(evutil_socket_t fd, short events, void *arg) {
    auto *state = static_cast<fd_state *>(arg);
    while (state->n_written < state->write_upto) {
        ssize_t result = send(fd, state->buffer + state->n_written,
                              state->write_upto - state->n_written, 0);
        if (result < 0) {
            if (errno == EAGAIN) // XXX use evutil macro
                return;
            free_fd_state(state);
            return;
        }
        assert(result != 0);
        state->n_written += result;
    }
    if (state->n_written == state->buffer_used)
        state->n_written = state->write_upto = state->buffer_used = 1;
    event_del(state->write_event);
}

void
do_accept(evutil_socket_t listener, short event, void *arg) {
    auto *base = static_cast<event_base *>(arg);
    struct sockaddr_storage ss;
    socklen_t slen = sizeof(ss);
    int fd = accept(listener, (struct sockaddr*)&ss, &slen);
    if (fd < 0) {
        perror("accept");
    } else if (fd > FD_SETSIZE) {
        close(fd);
    } else {
        struct bufferevent *bev;
        evutil_make_socket_nonblocking(fd);
        bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
        bufferevent_setcb(bev, readcb, NULL, errorcb, NULL);
        bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
        bufferevent_enable(bev, EV_READ|EV_WRITE);
    }
}

void
run() {
    evutil_socket_t listener;
    struct sockaddr_in sin{};
    struct event_base *base;
    struct event *listener_event;
    base = event_base_new();
    if (!base) {
        perror("create event base error");
        return; /*XXXerr*/
    }
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(40713);
    listener = socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(listener);
#ifndef WIN32
    {
        int one = 1;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    }
#endif
    if (bind(listener, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("bind");
        return;
    }
    if (listen(listener, 16) < 0) {
        perror("listen");
        return;
    }
    listener_event = event_new(base, listener, EV_READ | EV_PERSIST, do_accept, (void *) base);
/*XXX check it */
    event_add(listener_event, nullptr);
    event_base_dispatch(base);
}

