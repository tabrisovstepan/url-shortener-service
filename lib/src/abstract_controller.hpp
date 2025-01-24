#ifndef ABSTRACT_CONTROLLER_INCLUDE_HPP
#define ABSTRACT_CONTROLLER_INCLUDE_HPP

#include <string>
#include <iostream>

#include <boost/beast.hpp>
#include "utils.hpp"

namespace hs
{

class HttpServer;

namespace cr
{

class AbstractController
{
    friend class hs::HttpServer;

public:
    [[nodiscard]] virtual const char* path() const = 0;

    virtual void onGetMethodRequest(request& req, response& resp);

    virtual void onPostMethodRequest(request& req, response& resp);

    virtual void onPutMethodRequest(request& req, response& resp);

    virtual void onDeleteMethodRequest(request& req, response& resp);

    virtual ~AbstractController() = default;

protected:
    virtual void doService(request& req, response& resp);
};

} // namespace cr

} // namespace hs

#endif