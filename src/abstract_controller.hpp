#ifndef ABSTRACT_CONTROLLER_INCLUDE_H
#define ABSTRACT_CONTROLLER_INCLUDE_H

#include <string>
#include <iostream>

#include <boost/beast.hpp>

namespace beast   = boost::beast;
namespace http    = beast::http;

namespace hs { class HttpServer; }

namespace ctrl {

class AbstractController
{
    friend class hs::HttpServer;

public:
    virtual std::string path() const = 0;

    virtual void onGetMethodRequest(http::request<http::string_body>& req,
                                    http::response<http::string_body>& resp);

    virtual void onPostMethodRequest(http::request<http::string_body>& req,
                                     http::response<http::string_body>& resp);

    virtual void onPutMethodRequest(http::request<http::string_body>& req,
                                    http::response<http::string_body>& resp);

    virtual void onDeleteMethodRequest(http::request<http::string_body>& req,
                                       http::response<http::string_body>& resp);

    virtual ~AbstractController() = default;

protected:         
    virtual void doService(http::request<http::string_body>& req,
                           http::response<http::string_body>& resp);
private:

};                              

}

#endif