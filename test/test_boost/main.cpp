
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

inline int boost_http_sync_client(const std::string& server, const std::string& port, const std::string& path,
                                  std::string& out_response_status_line, std::string& out_response_header, std::string& out_response_data)
{
    try
    {
        boost::asio::io_service io_service;

        // Get a list of endpoints corresponding to the server name.
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(server, port/*"http"*/);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET " << path/*argv[2]*/ << " HTTP/1.0\r\n";
        request_stream << "Host: " << server/*argv[1]*/ << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        if (true)
        {
            boost::asio::streambuf::const_buffers_type cbt = response.data();
            std::string temp_data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
            std::size_t idx = temp_data.find('\n');
            idx == std::string::npos ? temp_data.size() : idx;
            out_response_status_line = temp_data.substr(0, idx + 1);
        }

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Invalid response\n";
            return 1;
        }
        if (status_code != 200)
        {
            std::cout << "Response returned with status code " << status_code << "\n";
            return 1;
        }

        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");
        if (true)
        {
            boost::asio::streambuf::const_buffers_type cbt = response.data();
            std::string temp_data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
            std::size_t idx = temp_data.find("\r\n\r\n");
            idx == std::string::npos ? temp_data.length() : idx;
            out_response_header = temp_data.substr(0, idx + 2);
        }

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            ;//std::cout << header << "\n";
        //std::cout << "\n";

        // Write whatever content we already have to output.
        //if (response.size() > 0)
        //    std::cout << &response;
        if (true)
        {
            boost::asio::streambuf::const_buffers_type cbt = response.data();
            out_response_data = std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
        }

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response,
                                 boost::asio::transfer_at_least(1), error))
            //std::cout << &response;
        {
            boost::asio::streambuf::const_buffers_type cbt = response.data();
            out_response_data += std::string(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
        return -1;
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////
//可以解析下列三种类型的URL:
//http://yunhq.sse.com.cn:32041/v1/sh1/snap/204001?callback=jQuery_test&select=name%2Clast%2Cchg_rate%2Cchange%2Camount%2Cvolume%2Copen%2Cprev_close%2Cask%2Cbid%2Chigh%2Clow%2Ctradephase
//http://hq.sinajs.cn/list=sh204001
//https://www.baidu.com
//////////////////////////////////////////////////////////////////////////
inline int parse_url(const std::string& url, std::string& out_server, std::string& out_port, std::string& out_path)
{
    const std::string http___ = "http://";
    const std::string https___ = "https://";
    std::string temp_data = url;

    if (temp_data.find(http___) == 0)
        temp_data = temp_data.substr(http___.length());
    else if (temp_data.find(https___) == 0)
        temp_data = temp_data.substr(https___.length());
    else
        return -1;

    std::size_t idx = temp_data.find('/');
    if (std::string::npos == idx)
    {
        out_path = "/";
        idx = temp_data.size();
    }
    else
    {
        out_path = temp_data.substr(idx);
    }

    out_server = temp_data.substr(0, idx);
    idx = out_server.find(':');
    if (std::string::npos == idx)
    {
        out_port = "http";
        out_port = "80";
    }
    else
    {
        out_port = out_server.substr(idx + 1);
        out_server = out_server.substr(0, idx);
    }

    return 0;
}
//
inline int get_url_response(const std::string& url, std::string& out_response_data)
{
    int rv = 0;
    do
    {
        std::string server;
        std::string port;
        std::string path;
        rv = parse_url(url, server, port, path);
        if (rv)  break;
        std::string out_response_status_line;
        std::string out_response_header;
        rv = boost_http_sync_client(server, port, path, out_response_status_line, out_response_header, out_response_data);
        if (rv)  break;
    } while (false);
    return rv;
}
//
int parse_hq_sinajs_cn_and_get_last_price(const std::string& market_data, double& last_price)
{
    std::string temp_data = market_data;
    std::size_t idx;

    idx = temp_data.find('"');
    if (std::string::npos == idx)
        return -1;
    temp_data = temp_data.substr(idx + 1);

    idx = temp_data.find('"');
    if (std::string::npos == idx)
        return -1;
    temp_data = temp_data.substr(0, idx);

    std::vector<std::string> fields;
    std::size_t beg_idx, end_idx;
    for (beg_idx = end_idx = 0; (end_idx = temp_data.find(',', beg_idx)) != std::string::npos; beg_idx = end_idx + 1)
        fields.push_back(temp_data.substr(beg_idx, end_idx - beg_idx));
    fields.push_back(temp_data.substr(beg_idx));

    if (fields.size() != 33)
        return -1;

    last_price = atof(fields[3].c_str());

    return 0;
}
//
int main()
{
    int rv = 0;
    std::string url = "http://www.baidu.com";
    std::string response_data;
    rv = get_url_response(url, response_data);
    if (rv)  return -1;
    std::cout << response_data << std::endl;

    double last_price = 0;
    rv = parse_hq_sinajs_cn_and_get_last_price(response_data, last_price);
    if (rv)  return -1;
    std::cout << last_price << std::endl;

    return 0;
}