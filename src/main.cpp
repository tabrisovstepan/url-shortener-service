
#include "controller/url_shortener_controller.hpp"
#include "service/url_shortener_service.hpp"
#include <http_server.hpp>

#include <iostream>
#include <memory>
#include <boost/program_options.hpp>

namespace options = boost::program_options;

int main(int argc, char** argv)
{
    options::options_description description{"Allowed options"};
    description.add_options()
            ("help", "produce help message")
            ("host", "setup host address")              // use default ip address [options::value<std::string>(ip)->default_value("127.0.0.1")]
            ("port", "setup port");     // use default port [options::value<uint32_t>(port)->default_value(8080)]

    options::variables_map values{};

    std::string ip {"127.0.0.1"};
    int port {8989};
    std::string db_path {"url_storage.db"};

    try {
        options::store(options::parse_command_line(argc, argv, description), values);
        options::notify(values);

        if (values.count("help"))
        {
            std::cout << description << std::endl;
            return 1;
        }

        auto service    = std::make_unique<UrlShortenerService>(db_path);
        auto controller = std::make_unique<UrlShortenerController>(std::move(service));

        std::cout << "Start url-shortener-service\n";
        std::cout << "Host : " << ip << '\n';
        std::cout << "Port : " << port << '\n';
        std::cout << "DB   : " << db_path << "\n\n";

        hs::HttpServer server(ip.c_str(), port);
        server.addController(std::move(controller));
        server.run();

    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
