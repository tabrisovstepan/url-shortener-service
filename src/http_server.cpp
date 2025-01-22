#include "http_server.hpp"

namespace hs 
{

HttpServer::HttpServer(const char* ip, uint32_t port)
    : mAcceptor({mIOContext, {io::ip::make_address(ip), static_cast<unsigned short>(port)}})
{

}

void HttpServer::run()
{
    assert(mControllers.empty() && "There`re no controllers for handle requests");

    for (;;)
    {
        io::ip::tcp::socket socket {mIOContext};
        mAcceptor.accept(socket);
        std::thread { &HttpServer::doProcessRequests, this, std::move(socket)}.detach();
    }
}

void HttpServer::doProcessRequests(io::ip::tcp::socket&& socket)
{
    beast::flat_buffer buffer;
    beast::error_code  errorCode;

    for (;;)
    {
        http::request<http::string_body> request;
        http::response<http::string_body> response;

        http::read(socket, buffer, request, errorCode);

        if (errorCode == http::error::end_of_stream) break;
        
        doServiceRequests(request, response);

        http::write(socket, response);

        if (response.need_eof()) break;
    }
    socket.shutdown(io::ip::tcp::socket::shutdown_send);
}

void HttpServer::doServiceRequests(http::request<http::string_body>& req,
                                   http::response<http::string_body>& resp)
{
    for (const auto& controller: mControllers)
    {
        if (req.target().find(controller->path()) == 0)
        {
            controller->doService(req, resp);
            return;
        }
    }
    std::cout << "Wrong request. Route not found. Send 404" << std::endl;
}

}