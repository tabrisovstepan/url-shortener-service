#include "http_server.hpp"
#include "url_shortener_controller.hpp"

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

    try {
        options::store(options::parse_command_line(argc, argv, description), values);
        options::notify(values);

        if (values.count("help"))
        {
            std::cout << description << std::endl;
            return 1;
        }

        hs::HttpServer server("127.0.0.1", 8989);
        server.addController(std::make_unique<UrlShortenerController>());
        server.run();

    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
