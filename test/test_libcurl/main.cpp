#include <stdio.h>
#include <pthread.h>
#include <curl/curl.h>

/*
  URL to fetch. If you select HTTPS, you need to use a TLS backend with mutex
  locks taken care of (OpenSSL 1.1.x, NSS, etc) or add SSL mutex callbacks!
*/
#define URL "http://localhost/4KB"

/* number of threads to fire up in parallel */
#define NUM_THREADS 67

/* how many times each URL is transferred per thread */
#define URL_ITERATIONS 11235

static pthread_mutex_t connlock;

static size_t write_db(void *ptr, size_t size, size_t nmemb, void *data)
{
    /* not interested in the downloaded bytes, return the size */
    (void)ptr;  /* unused */
    (void)data; /* unused */
    return (size_t)(size * nmemb);
}

static void lock_cb(CURL *handle, curl_lock_data data,
                    curl_lock_access access, void *userptr)
{
    (void)access; /* unused */
    (void)userptr; /* unused */
    (void)handle; /* unused */
    (void)data; /* unused */
    pthread_mutex_lock(&connlock);
}

static void unlock_cb(CURL *handle, curl_lock_data data,
                      void *userptr)
{
    (void)userptr; /* unused */
    (void)handle;  /* unused */
    (void)data;    /* unused */
    pthread_mutex_unlock(&connlock);
}

static void init_locks(void)
{
    pthread_mutex_init(&connlock, NULL);
}

static void kill_locks(void)
{
    pthread_mutex_destroy(&connlock);
}

struct initurl {
    const char *url;
    CURLSH *share;
    int threadno;
};

static void *run_thread(void *ptr)
{
    struct initurl *u = (struct initurl *)ptr;
    int i;

    for(i = 0; i < URL_ITERATIONS; i++) {
        CURL *curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, u->url);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_SHARE, u->share);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_db);
        curl_easy_perform(curl); /* ignores error */
        curl_easy_cleanup(curl);
        fprintf(stderr, "Thread %d transfer %d\n", u->threadno, i);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid[NUM_THREADS];
    int i;
    CURLSH *share;
    struct initurl url[NUM_THREADS];

    /* Must initialize libcurl before any threads are started */
    curl_global_init(CURL_GLOBAL_ALL);

    share = curl_share_init();
    curl_share_setopt(share, CURLSHOPT_LOCKFUNC, lock_cb);
    curl_share_setopt(share, CURLSHOPT_UNLOCKFUNC, unlock_cb);
    curl_share_setopt(share, CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);

    init_locks();

    for(i = 0; i< NUM_THREADS; i++) {
        int error;
        url[i].url = URL;
        url[i].share = share;
        url[i].threadno = i;
        error = pthread_create(&tid[i], NULL, run_thread, &url[i]);
        if(0 != error)
            fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
        else
            fprintf(stderr, "Thread %d, gets %s\n", i, URL);
    }

    /* now wait for all threads to terminate */
    for(i = 0; i< NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
        fprintf(stderr, "Thread %d terminated\n", i);
    }

    kill_locks();

    curl_share_cleanup(share);
    curl_global_cleanup();
    return 0;
}