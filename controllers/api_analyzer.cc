#include "api_analyzer.h"

using namespace api;

IKNManager * klanManager = GenerateAPIManager();
IKNEngine* klanEngine = klanManager->GetEngine();


// Add definition of your processing function here
void analyzer::responsePing(
    const HttpRequestPtr& req,
    std::function<void (const HttpResponsePtr &)> &&callback
)
{
    auto res = HttpResponse::newHttpResponse();
    res->setStatusCode(k200OK);
    callback(res);
};

void analyzer::runMorphAnalyze(
    const HttpRequestPtr& req,
    std::function<void (const HttpResponsePtr &)> &&callback
)
{
    auto resp = HttpResponse::newHttpResponse();
    auto reqData = req->getJsonObject();
    std::cout << *reqData << std::endl;
    if (!reqData)
    {
        resp->setStatusCode(k400BadRequest);
        resp->setBody("no provided text");
        callback(resp);
        return;
    }
    
    resp->setStatusCode(k200OK);
    callback(resp);
}
