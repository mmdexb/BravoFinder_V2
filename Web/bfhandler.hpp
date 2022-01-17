#ifndef BF_HANDLER_H
#define BF_HANDLER_H

#include "oatpp/web/server/HttpRequestHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include <bfinder/bfinder.h>
#include "BfDataset.hpp"

class BfHandler : public oatpp::web::server::HttpRequestHandler {
public:
    std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest> &request) override {

        oatpp::String tail = request->getPathTail();
        auto const &queryParams = oatpp::network::Url::Parser::parseQueryParams(tail);

        std::string arr;
        std::string dep;

        for (const auto &p: queryParams.getAll()) {
            if ((std::string) p.first.toString() == (std::string) "dep") {
                dep = (std::string) p.second.toString();
            }

            if ((std::string) p.first.toString() == (std::string) "arr") {
                arr = (std::string) p.second.toString();
            }
        }
        OATPP_LOGI("BfFinder", "%s %s", dep.c_str(), arr.c_str());

        try {
            if (dep == arr) {
                throw "404";
            }
            auto const &dataset = BfDataset::getInstance();
            auto const &result = dataset.dataset->FindRoute(dep, arr);
            return ResponseFactory::createResponse(Status::CODE_200,
                                                   "{\"result\": \"" + result.get()->route + "\"}");
        }
        catch (...) {
            return ResponseFactory::createResponse(Status::CODE_404, "{\"error\": \"cannot calculate a route\"}");
        }
    }
};

#endif // BF_HANDLER_H
