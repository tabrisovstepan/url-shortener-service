#ifndef URL_SHORTENER_CONTROLLER_HPP
#define URL_SHORTENER_CONTROLLER_HPP

#include <abstract_controller.hpp>
#include "../service/url_shortener_service.hpp"


/**
*   @class UrlShortenerController Класс контроллера, отвечающего за обработку запросов
*/
class UrlShortenerController
    : public hs::cr::AbstractController
{
    using ScopedPtr = std::unique_ptr<UrlShortenerService>;
public:
    explicit UrlShortenerController(ScopedPtr&& service);

    /**
    *   @brief Получить префикс контроллера
    *   @return префикс
    */
    [[nodiscard]] const char* path() const override;

    /**
    *   @brief Метод для обработки GET запросов
    */
    void onGetMethodRequest(http::request<http::string_body>& req,
                            http::response<http::string_body>& resp) override;

    /**
    *   @brief Метод для обработки POST запросов
    */
    void onPostMethodRequest(http::request<http::string_body>& req,
                             http::response<http::string_body>& resp) override;

    ~UrlShortenerController() override = default;

private:
    ScopedPtr mService;
};

#endif