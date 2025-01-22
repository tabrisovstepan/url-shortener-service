#ifndef URL_SHORTENER_CONTROLLER_H
#define URL_SHORTENER_CONTROLLER_H

#include "abstract_controller.hpp"

class UrlShortenerController
    : public ctrl::AbstractController
{

public:
    explicit UrlShortenerController();

    std::string path() const override;

    void onGetMethodRequest(http::request<http::string_body>& req,
                            http::response<http::string_body>& resp) override;

    void onPostMethodRequest(http::request<http::string_body>& req,
                             http::response<http::string_body>& resp) override;

    ~UrlShortenerController() = default;

private:

};

#endif