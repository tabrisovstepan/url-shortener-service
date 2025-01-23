#ifndef URL_SHORTENER_CONTROLLER_H
#define URL_SHORTENER_CONTROLLER_H

#include "abstract_controller.hpp"
#include "url_shortener_service.hpp"

class UrlShortenerController
    : public ctrl::AbstractController
{
    using ScopedPtr = std::unique_ptr<UrlShortenerService>;
public:
    explicit UrlShortenerController(ScopedPtr&& service);

    std::string path() const override;

    void onGetMethodRequest(http::request<http::string_body>& req,
                            http::response<http::string_body>& resp) override;

    void onPostMethodRequest(http::request<http::string_body>& req,
                             http::response<http::string_body>& resp) override;

    ~UrlShortenerController() override = default;

private:
    ScopedPtr mService;
};

#endif