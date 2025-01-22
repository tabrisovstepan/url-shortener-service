#include "url_shortener_controller.hpp"
#include "utils.hpp"

UrlShortenerController::UrlShortenerController()
{

}

std::string UrlShortenerController::path() const
{
    return "/url";
}

void UrlShortenerController::onGetMethodRequest(http::request<http::string_body>& req,
                                                http::response<http::string_body>& resp)
{
    // parse url param
}

void UrlShortenerController::onPostMethodRequest(http::request<http::string_body>& req,
                                                 http::response<http::string_body>& resp)
{
    if (hs::utils::route_match("/url", req.target()))
    {
        return;
    } 

    if (hs::utils::route_match("/url/custom", req.target()))
    {
        return;
    }
}