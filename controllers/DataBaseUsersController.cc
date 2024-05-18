#include "DataBaseUsersController.h"

void DataBaseUsersController::createNewUser(
    const HttpRequestPtr& req,
    std::function<void (const HttpResponsePtr &)> &&callback,
    std::string login,
    std::string password
)
{
    auto resp=HttpResponse::newHttpResponse();
    //If not pass parameters then sending 400 error.
    if (!login.empty() && !password.empty())
    {
        resp->setStatusCode(k400BadRequest);
        callback(resp);
    }
    
    
    auto clientPtr = drogon::app().getDbClient();
    try
    {
        clientPtr->execSqlSync("insert into users (login, password) values ($1, $2)", login, password);
        resp->setStatusCode(k200OK);
        callback(resp);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << std::endl;
    }
} 