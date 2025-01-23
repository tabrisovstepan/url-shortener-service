#ifndef HTTP_SERVER_INCLUDE_HPP
#define HTTP_SERVER_INCLUDE_HPP

#include <vector>
#include <memory>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "abstract_controller.hpp"

namespace io = boost::asio;

namespace hs {

class HttpServer
{
    using Storage = std::vector<std::unique_ptr<cr::AbstractController>>;
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
    void doServiceRequests(request& req, response& resp);

private:
    io::io_context mIOContext {1};
    io::ip::tcp::acceptor mAcceptor;
    Storage mControllers;
};

}

#endif