#include "DataBaseController.h"

void DataBaseController::getUsers(
const HttpRequestPtr &req,
std::function<void (const HttpResponsePtr &)> &&callback
)
{
    std::cout << "[GET]" << "ALL_USERS" << std::endl;
    auto clientPtr = drogon::app().getDbClient();
    try
    {
        
        std::cout << "[GET]" << "ALL_USERS" << "Start getting DbClient pointer"<< std::endl;
        auto result = clientPtr->execSqlSync("select * from users");
        std::cout << "[GET]" << "ALL_USERS" << "Got DbClient pointer"<< std::endl;
        
        Json::Value ret;
        ret["users"]= Json::arrayValue;
        
        int i = 0;
        for (auto row : result)
        {
            ret["users"][i] = row["login"].as<std::string>();
            i++;
        }

        auto resp=HttpResponse::newHttpJsonResponse(ret);
        callback(resp);
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
        std::cerr << "error:" << e.base().what() << std::endl;
    }
} 