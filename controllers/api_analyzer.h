#pragma once

#include <drogon/HttpController.h>
#include <../../libs/klanHeaders/IKNManager.h>
#include <../../libs/klanHeaders/KNKernel.h>
#include <../../libs/klanHeaders/IKNEngine.h>


using namespace drogon;

namespace api
{
class analyzer : public drogon::HttpController<analyzer>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(analyzer::responsePing, "/text", Get);
    METHOD_ADD(analyzer::runMorphAnalyze, "/text", Post);

    METHOD_LIST_END

    void responsePing(
      const HttpRequestPtr& req,
      std::function<void (const HttpResponsePtr &)> &&callback
    );

    void runMorphAnalyze(
      const HttpRequestPtr& req,
      std::function<void (const HttpResponsePtr &)> &&callback
    );
};
}
