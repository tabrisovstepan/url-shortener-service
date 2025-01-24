#ifndef URL_SHORTENER_SERVICE_INCLUDE_HPP
#define URL_SHORTENER_SERVICE_INCLUDE_HPP

#include <optional>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

/**
*   @brief UrlEntity Сущность для представления записи в БД
*/
struct UrlEntity
{
    int32_t id {};
    std::string base_url;
    std::string short_url;
};

/**
*   @class UrlShortenerService Класс сервиса, отвечающего за хранение и создание короткого представления URL
*/
class UrlShortenerService final
{
    using Storage = std::unordered_map<std::string, std::string>;
public:
    explicit UrlShortenerService(const std::string& path);

    /**
    *   @brief Создать короткое представление URL
    *   @param url базовое представление URL
    *   @param host хост системы
    *   @return объект UrlEntity сохраненный в БД
    */
    UrlEntity createShortUrl(const std::string& url,
                             const std::string& host);

    /**
    *   @brief Создать короткое представление URL
    *   @param url базовое представление URL
    *   @param short_url короткое представление URL
    *   @param host хост системы
    *   @return объект UrlEntity сохраненный в БД
    */
    UrlEntity createShortUrl(const std::string& url,
                             const std::string& short_url,
                             const std::string& host);

    /**
    *   @brief Получить базовое представление URL по короткому
    *   @param short_url короткое представление URL
    *   @return базовое URL
    */
    std::optional<std::string> getBaseUrl(const std::string& short_url);

private:
        /**
    *   @brief Создать короткое представление URL 
    *   @param url базовое представление URL
    *   @return короткое представление URL
    * 
    *   @details Для создания короткого представления URL используется алгоритм CRC32 из библиотеки Boost
    */
    static std::string makeShortUrl(const std::string& url);

private:
    SQLite::Database db;
    Storage cache;
};

#endif //URL_SHORTENER_SERVICE_INCLUDE_HPP
