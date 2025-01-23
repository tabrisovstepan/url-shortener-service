#ifndef UTILS_INCLUDE_H
#define UTILS_INCLUDE_H

#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <boost/beast.hpp>
#include <boost/json.hpp>

namespace beast   = boost::beast;
namespace http    = beast::http;
namespace json    = boost::json;

namespace hs 
{

namespace utils 
{

inline http::response<http::string_body> not_found(const http::request<http::string_body>& req, std::string_view target)
{
    http::response<http::string_body> resp {http::status::not_found, req.version()};
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\":\"The resource " + std::string(target) + " was not found.\"}";
    resp.prepare_payload();
    return resp;
}

inline http::response<http::string_body> bad_request(const http::request<http::string_body>& req, std::string_view cause)
{
    http::response<http::string_body> resp {http::status::bad_request, req.version()};
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\":\"" + std::string(cause) + "\"}";
    resp.prepare_payload();
    return resp;
}

inline http::response<http::string_body> server_error(const http::request<http::string_body>& req, std::string_view cause)
{
    http::response<http::string_body> resp {http::status::internal_server_error, req.version()};
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\":\"An error occurred: " + std::string(cause) + "\"}";
    resp.prepare_payload();
    return resp;
}

    inline http::response<http::string_body> conflict(const http::request<http::string_body>& req, std::string_view cause)
    {
        http::response<http::string_body> resp {http::status::conflict, req.version()};
        resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        resp.set(http::field::content_type, "application/json");
        resp.keep_alive(req.keep_alive());
        resp.body() = "{\"message\":\"Conflict: " + std::string(cause) + "\"}";
        resp.prepare_payload();
        return resp;
    }

inline bool route_match(std::string_view pattern, std::string_view target)
{
    std::vector<std::string> pattern_segments;
    std::vector<std::string> target_segments;

    auto match = [] (auto c) { return c == '/'; };

    boost::algorithm::split(pattern_segments, 
                            std::string_view(pattern.data() + 1, pattern.size() - 1), 
                            match);

    boost::algorithm::split(target_segments, 
                            std::string_view(target.data() + 1, target.size() - 1), 
                            match);

    if (pattern_segments.size() != target_segments.size()) return false;

    for (size_t i = 0; i < pattern_segments.size() - 1; ++i)
    {
        if (pattern_segments[i] != target_segments[i]) return false;            
    }
    return true;
}

} // namespace utils

} // namespace hs

#endif