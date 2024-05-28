#include <drogon/drogon.h>
#include <iostream>


int main() {

    // const char* text = "TEST"; 

    // // IKNManager * klanManager = GenerateAPIManager();
    // // IKNEngine* klanEngine = klanManager->GetEngine();

    // char *testEngChar = convertToCP1251(text);
    // std::cout << testEngChar << std::endl;

    // uint len = 0;
    // t_errno err = klanEngine->Run(testEngChar, 0, &len);

    // IKNResultList* res = klanEngine->GetResultList();
    // auto count = res->GetCount(1);

    // printf("Results count: %d\n", count);

    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().loadConfigFile("../models/model.json");
    drogon::app().areAllDbClientsAvailable();
    drogon::app().run();
    return 0;
}