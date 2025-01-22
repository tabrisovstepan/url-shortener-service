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
    resp.result(http::status::permanent_redirect);
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "text/html");
    resp.set(http::field::location, "http://www.google.com");
    resp.keep_alive(req.keep_alive());
    resp.prepare_payload();
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