#ifndef HTTP_SERVER_INCLUDE_H
#define HTTP_SERVER_INCLUDE_H

#include <vector>
#include <memory>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>

#include "abstract_controller.hpp"

namespace beast   = boost::beast;
namespace http    = beast::http;
namespace io      = boost::asio;

namespace hs {

class HttpServer
{
public:
    explicit HttpServer(const char* ip, uint32_t port);

    [[noreturn]] void run();

    template <typename ...Args>
    void addController(Args&&... args)
    {
        mControllers.emplace_back(std::forward<Args>(args)...);
    }

private:
    void doProcessRequests(io::ip::tcp::socket&& socket);
    void doServiceRequests(http::request<http::string_body>& req,
                           http::response<http::string_body>& resp);

private:
    io::io_context mIOContext {1};
    io::ip::tcp::acceptor mAcceptor;
    std::vector<std::unique_ptr<ctrl::AbstractController>> mControllers;
};

}

#endif