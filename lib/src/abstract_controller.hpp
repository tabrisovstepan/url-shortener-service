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

/**
*   @class AbstractController Базовый абстрактный класс для пользовательских контроллеров
*/
class AbstractController
{
    friend class hs::HttpServer;

public:
    /**
    *   @brief Получить префикс контроллера
    *   @return префикс
    */
    [[nodiscard]] virtual const char* path() const = 0;
    
    /**
    *   @brief Метод для обработки GET запросов
    *   @param req входящий запрос
    *   @param resp ответ [out]
    * 
    *   @details Для обработки GET запросов необходимо переопределить данный метод.
    *            По умочанию формирует ответ с кодом NOT_FOUND и помещает в параметр resp
    */
    virtual void onGetMethodRequest(request& req, response& resp);

    /**
    *   @brief Метод для обработки POST запросов
    *   @param req входящий запрос
    *   @param resp ответ [out]
    * 
    *   @details Для обработки POST запросов необходимо переопределить данный метод.
    *            По умочанию формирует ответ с кодом NOT_FOUND и помещает в параметр resp
    */
    virtual void onPostMethodRequest(request& req, response& resp);

    /**
    *   @brief Метод для обработки PUT запросов
    *   @param req входящий запрос
    *   @param resp ответ [out]
    * 
    *   @details Для обработки PUT запросов необходимо переопределить данный метод.
    *            По умочанию формирует ответ с кодом NOT_FOUND и помещает в параметр resp
    */
    
    virtual void onPutMethodRequest(request& req, response& resp);
    /**
    *   @brief Метод для обработки DELETE запросов
    *   @param req входящий запрос
    *   @param resp ответ [out]
    * 
    *   @details Для обработки DELETE запросов необходимо переопределить данный метод.
    *            По умочанию формирует ответ с кодом NOT_FOUND и помещает в параметр resp
    */
    virtual void onDeleteMethodRequest(request& req, response& resp);

    virtual ~AbstractController() = default;

protected:
    /**
    *   @brief Метод для определения соответствующего метода для обработки запроса
    *   @param req входящий запрос
    *   @param resp ответ [out]
    * 
    *   @details По умочанию ищет методы для обработки GET, POST, PUT, DELETE запросов.
    *            В случае других запросов (например PATCH) 
    *            формирует ответ с кодом NOT_FOUND и помещает в параметр resp.
    *            
    *            Для реализации поддержки других запросов PATCH, HEAD и т.д. 
    *            необходимо переопределить данный метод.
    */
    virtual void doService(request& req, response& resp);
};

} // namespace cr

} // namespace hs

#endif