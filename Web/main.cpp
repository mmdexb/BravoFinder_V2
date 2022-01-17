#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/network/Server.hpp"
#include "bfhandler.hpp"

void run()
{

    auto router = oatpp::web::server::HttpRouter::createShared();

    router->route("GET", "/routes/*", std::make_shared<BfHandler>());

    auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

    auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 8000, oatpp::network::Address::IP_4});

    oatpp::network::Server server(connectionProvider, connectionHandler);

    OATPP_LOGI("BfFinder", "Server running on port %s", connectionProvider->getProperty("port").getData());

    server.run();
}

int main()
{
    oatpp::base::Environment::init();

    run();

    oatpp::base::Environment::destroy();

    return 0;
}