#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class DataBaseUsersController : public drogon::HttpController<DataBaseUsersController>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(DataBaseUsersController::createNewUser,"/users/add/{1}/{2}", Post);
    METHOD_LIST_END

    void createNewUser(
      const HttpRequestPtr& req,
       std::function<void (const HttpResponsePtr &)> &&callback,
       std::string login,
       std::string password
       );
};

