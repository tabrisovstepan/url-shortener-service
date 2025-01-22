#include "abstract_controller.hpp"
#include <boost/json.hpp>

namespace ctrl 
{

void AbstractController::onGetMethodRequest(http::request<http::string_body>& req,
                                            http::response<http::string_body>& resp)
{
    //not found
    resp.result(http::status::not_found);
    resp.version(req.version());
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\": \"not found\"}"; // boost::format
    resp.prepare_payload();
}

void AbstractController::onPostMethodRequest(http::request<http::string_body>& req,
                                             http::response<http::string_body>& resp)
{
    resp.result(http::status::not_found);
    resp.version(req.version());
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\": \"not found\"}"; // boost::format
    resp.prepare_payload();
}                                            

void AbstractController::onPutMethodRequest(http::request<http::string_body>& req,
                                            http::response<http::string_body>& resp)
{
    resp.result(http::status::not_found);
    resp.version(req.version());
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\": \"not found\"}"; // boost::format
    resp.prepare_payload();
}

void AbstractController::onDeleteMethodRequest(http::request<http::string_body>& req,
                                               http::response<http::string_body>& resp)
{
    resp.result(http::status::not_found);
    resp.version(req.version());
    resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    resp.set(http::field::content_type, "application/json");
    resp.keep_alive(req.keep_alive());
    resp.body() = "{\"message\": \"not found\"}"; // boost::format
    resp.prepare_payload();
}

void AbstractController::doService(http::request<http::string_body>& req,
                                   http::response<http::string_body>& resp)
{

    //validate target

    switch (req.method())
    {
    case http::verb::get: 
        onGetMethodRequest(req, resp);
        break;
    case http::verb::post:
        onPostMethodRequest(req, resp); 
        break;
    case http::verb::put:
        onPutMethodRequest(req, resp);
        break;
    case http::verb::delete_:
        onDeleteMethodRequest(req, resp);
        break;
    default: 
        resp.result(http::status::bad_request);
        resp.version(req.version());
        resp.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        resp.set(http::field::content_type, "application/json");
        resp.keep_alive(req.keep_alive());
        resp.body() = "{\"message\": \"illegal request-target\"}"; // boost::format
        resp.prepare_payload();
        break;
    }    
}     

}