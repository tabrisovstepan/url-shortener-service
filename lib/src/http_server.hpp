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

/**
*   @class HttpServer Класс HTTP сервера
*/
class HttpServer
{
    using Storage = std::vector<std::unique_ptr<cr::AbstractController>>;
public:
    explicit HttpServer(const char* ip, uint32_t port);

    /**
    *   @brief Запустить сервер
    */
    [[noreturn]] void run();

    /**
    *   @brief Добавить контроллеры
    *   @param args объекты пользовательских контроллеров
    */
    template <typename ...Args>
    void addController(Args&&... args)
    {
        mControllers.emplace_back(std::forward<Args>(args)...);
    }

private:
    /**
    *   @brief Метод для приема и отправки запросов
    */
    void doProcessRequests(io::ip::tcp::socket&& socket);
    
    /**
    *   @brief Метод для передачи запросов контроллерам
    */
    void doServiceRequests(request& req, response& resp);

private:
    io::io_context mIOContext {1};
    io::ip::tcp::acceptor mAcceptor;
    Storage mControllers;
};

}

#endif