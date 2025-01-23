#include "abstract_controller.hpp"

namespace hs::cr
{

void AbstractController::onGetMethodRequest(http::request<http::string_body>& req,
                                            http::response<http::string_body>& resp)
{
    resp = hs::utils::not_found(req, req.target());
}

void AbstractController::onPostMethodRequest(http::request<http::string_body>& req,
                                             http::response<http::string_body>& resp)
{
    resp = hs::utils::not_found(req, req.target());
}                                            

void AbstractController::onPutMethodRequest(http::request<http::string_body>& req,
                                            http::response<http::string_body>& resp)
{
    resp = hs::utils::not_found(req, req.target());
}

void AbstractController::onDeleteMethodRequest(http::request<http::string_body>& req,
                                               http::response<http::string_body>& resp)
{
    resp = hs::utils::not_found(req, req.target());
}

void AbstractController::doService(http::request<http::string_body>& req,
                                   http::response<http::string_body>& resp)
{
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
        resp = hs::utils::bad_request(req, req.target());
        break;
    }    
}     

}