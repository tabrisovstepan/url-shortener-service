#include "url_shortener_controller.hpp"
#include <utils.hpp>

#include <boost/json.hpp>

UrlShortenerController::UrlShortenerController(ScopedPtr&& service)
    : mService(std::move(service))
{

}

const char* UrlShortenerController::path() const
{
    return "/";
}

void UrlShortenerController::onGetMethodRequest(http::request<http::string_body>& req,
                                                http::response<http::string_body>& resp)
{
    std::cout << "Handling request\n";
    std::cout << "Method : " << req.method() << '\n';
    std::cout << "Target : " << req.target() << "\n\n";

    try
    {
        auto short_url = std::string{"http://"} + std::string{req.at(http::field::host)} + std::string{req.target()};
        auto url = mService->getBaseUrl(short_url);

        if (url.has_value())
        {
            resp.result(http::status::permanent_redirect);
            resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            resp.set(http::field::content_type, "text/html");
            resp.set(http::field::location, url->c_str());
            resp.keep_alive(req.keep_alive());
            resp.prepare_payload();
        }
        else
        {
            resp = hs::utils::not_found(req, req.target());
        }
    }
    catch (std::exception& ex)
    {
        std::cerr << "ERROR : " << ex.what() << std::endl;
        resp = hs::utils::server_error(req, ex.what());
    }
}

void UrlShortenerController::onPostMethodRequest(http::request<http::string_body>& req,
                                                 http::response<http::string_body>& resp)
{
    std::cout << "Handling request\n";
    std::cout << "Method : " << req.method() << '\n';
    std::cout << "Target : " << req.target() << "\n\n";
    
    if (hs::utils::route_match("/url", req.target()))
    {
        try
        {
            auto object = boost::json::parse(req.body());
            auto url = object.at("target_url").as_string();
            auto entity = mService->createShortUrl(url.c_str(), req.at(http::field::host));

            boost::json::object result { {"id", entity.id},
                                         {"base_url", entity.base_url},
                                         {"short_url",entity.short_url} };

            resp.result(http::status::created);
            resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            resp.set(http::field::content_type, "application/json");
            resp.body() = boost::json::serialize(result);
            resp.keep_alive(req.keep_alive());
            resp.prepare_payload();
        }
        catch (std::exception& ex)
        {
            std::cerr << "ERROR : " << ex.what() << std::endl;
            if (std::string(ex.what()).find("out of range") != std::string::npos)
            {
                resp = hs::utils::bad_request(req, "missing field");
            }
            else if (std::string(ex.what()).find("UNIQUE") != std::string::npos)
            {
                resp = hs::utils::conflict(req, "short url already exists");
            }
            else
            {
                resp = hs::utils::server_error(req, ex.what());
            }
        }
        return;
    } 

    if (hs::utils::route_match("/url/custom", req.target()))
    {
        try
        {
            auto object = boost::json::parse(req.body());
            auto target_url = object.at("target_url").as_string();
            auto short_url  = object.at("short_url").as_string();
            auto entity = mService->createShortUrl(target_url.c_str(),
                                                   short_url.c_str(),
                                                   req.at(http::field::host));

            boost::json::object result { {"id", entity.id},
                                         {"base_url", entity.base_url},
                                         {"short_url",entity.short_url} };

            resp.result(http::status::created);
            resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            resp.set(http::field::content_type, "application/json");
            resp.body() = boost::json::serialize(result);
            resp.keep_alive(req.keep_alive());
            resp.prepare_payload();
        }
        catch (std::exception& ex)
        {
            std::cerr << "ERROR : " << ex.what() << std::endl;
            if (std::string(ex.what()).find("out of range") != std::string::npos)
            {
                resp = hs::utils::bad_request(req, "missing field");
            }
            else if (std::string(ex.what()).find("UNIQUE") != std::string::npos)
            {
                resp = hs::utils::conflict(req, "short url already exists");
            }
            else
            {
                resp = hs::utils::server_error(req, ex.what());
            }
        }
        return;
    }
}