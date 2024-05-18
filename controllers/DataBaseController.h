#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DataBaseController : public drogon::HttpController<DataBaseController>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(DataBaseController::getUsers,"/users", Get);

    METHOD_LIST_END
    void getUsers(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);
};
