#include <drogon/drogon.h>
#include <iostream>
// #include <../libs/klanHeaders/IKNManager.h>
// #include <../libs/klanHeaders/KNKernel.h>
// #include <../libs/klanHeaders/IKNEngine.h>
#include <../libs/klanHeaders/KNMacros.h>

#include <cstdio>
#include <memory>
#include <unicode/ucnv.h>
#include <unicode/ustream.h>




char* convertToCP1251(const char* utf8)
{
    UErrorCode status = U_ZERO_ERROR;
    UConverter *conv = ucnv_open("cp1251", &status);
    if (status)
    {
	printf("Failed to obtain char set converter: %d\r\n", status);
	return nullptr;
    }
    icu::UnicodeString unicode_buffer(utf8);
    unsigned int ulen = unicode_buffer.length();
    char* cp1251 = new char[ulen + 1];
    unicode_buffer.extract(cp1251, ulen, conv, status);
    ucnv_close(conv);
    return cp1251;
}


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
    drogon::app().run();
    return 0;
}