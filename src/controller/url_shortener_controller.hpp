#ifndef URL_SHORTENER_CONTROLLER_HPP
#define URL_SHORTENER_CONTROLLER_HPP

#include "../lib/abstract_controller.hpp"
#include "../service/url_shortener_service.hpp"

class UrlShortenerController
    : public hs::cr::AbstractController
{
    using ScopedPtr = std::unique_ptr<UrlShortenerService>;
public:
    explicit UrlShortenerController(ScopedPtr&& service);

    [[nodiscard]] const char* path() const override;

    void onGetMethodRequest(http::request<http::string_body>& req,
                            http::response<http::string_body>& resp) override;

    void onPostMethodRequest(http::request<http::string_body>& req,
                             http::response<http::string_body>& resp) override;

    ~UrlShortenerController() override = default;

private:
    ScopedPtr mService;
};

#endif