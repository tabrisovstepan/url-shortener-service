#ifndef URL_SHORTENER_SERVICE_INCLUDE_HPP
#define URL_SHORTENER_SERVICE_INCLUDE_HPP

#include <optional>
#include <unordered_map>
#include <SQLiteCpp/SQLiteCpp.h>

struct UrlEntity
{
    int32_t id {};
    std::string base_url;
    std::string short_url;

    explicit operator std::string () const
    {
        return "{ \"id\":\"" + std::to_string(id) + "\""
               "  \"base_url\":\"" + base_url + "\": "
               "  \"short_url\":\"" + short_url + "\": }";
    }
};

class UrlShortenerService final
{
    using Storage = std::unordered_map<std::string, std::string>;
public:
    explicit UrlShortenerService(const std::string& path);

    UrlEntity createShortUrl(const std::string& url,
                             const std::string& host);

    UrlEntity createShortUrl(const std::string& url,
                             const std::string& short_url,
                             const std::string& host);

    std::optional<std::string> getBaseUrl(const std::string& short_url);

private:
    static std::string makeShortUrl(const std::string& url);

private:
    SQLite::Database db;
    Storage cache;
};

#endif //URL_SHORTENER_SERVICE_INCLUDE_HPP
