#include "url_shortener_service.hpp"
#include <boost/crc.hpp>

constexpr char create_table[] = "CREATE TABLE IF NOT EXISTS urls ( "
                                "id INTEGER PRIMARY KEY, "
                                "base_url TEXT NOT NULL, "
                                "short_url TEXT NOT NULL UNIQUE );";

constexpr char insert_data[]     = "INSERT INTO urls VALUES (NULL, ?, ?)";
constexpr char select_by_url[]   = "SELECT * FROM urls WHERE short_url = ?";
constexpr char select_base_url[] = "SELECT base_url FROM urls WHERE short_url = ?";

UrlShortenerService::UrlShortenerService(const std::string &path)
        : db (path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    db.exec(create_table);
}

UrlEntity UrlShortenerService::createShortUrl(const std::string& url,
                                              const std::string& host)
{
    std::string prefix {"http://" + host + "/"};

    auto short_url = prefix + makeShortUrl(url);

    SQLite::Statement q1 (db, insert_data);
    q1.bind(1, url);
    q1.bind(2, short_url);
    q1.exec();

    cache.emplace(std::pair{ short_url, url });

    SQLite::Statement q2 {db, select_by_url};
    q2.bind(1, short_url);

    if (!q2.executeStep()) return {};

    return { .id = q2.getColumn(0).getInt(),
             .base_url = q2.getColumn(1).getString(),
             .short_url =  q2.getColumn(2).getString() };
}

UrlEntity UrlShortenerService::createShortUrl(const std::string& url,
                                              const std::string& short_url,
                                              const std::string& host)
{
    SQLite::Statement q1 (db, insert_data);
    q1.bind(1, url);
    q1.bind(2, short_url);
    q1.exec();

    cache.emplace(std::pair{ short_url, url });

    SQLite::Statement q2 {db, select_by_url};
    q2.bind(1, short_url);

    if (!q2.executeStep()) return {};

    return { .id = q2.getColumn(0).getInt(),
             .base_url = q2.getColumn(1).getString(),
             .short_url =  q2.getColumn(2).getString() };
}

std::optional<std::string> UrlShortenerService::getBaseUrl(const std::string &short_url)
{
    if (cache.count(short_url))
    {
        return cache.at(short_url);
    }

    SQLite::Statement q1 {db, select_base_url};
    q1.bind(1, short_url);

    if (!q1.executeStep()) return {};

    return q1.getColumn(0).getString();
}

std::string UrlShortenerService::makeShortUrl(const std::string &url)
{
    boost::crc_32_type result;
    result.process_bytes(url.data(), url.length());
    return std::to_string(result.checksum());
}