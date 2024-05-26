// #include "api_Analyze.h"
// #include <./src/modules/analyzer/morphAnalizer.cc>
// #include <./src/modules/windows1251Converter.cc>

// using namespace api;

// char* getChar(std::string string) {
//     char *cstr = new char[string.size() + 3];
//     std::strcpy(cstr, string.c_str());
//     return cstr;
// }


// // Add definition of your processing function here
// void Analyze::runAnalyze(
//       const HttpRequestPtr& req,
//       std::function<void (const HttpResponsePtr &)> &&callback
// ) 
// {
//     auto resp = HttpResponse::newHttpResponse();
//     auto reqData = req->getJsonObject();

//     if (reqData)
//     {
//         std::string text = (*reqData)["text"].asString();
        
//         char convertedText[text.size() + 3];
//         char * convertedTextPointer = convertedText; 

//         utf8_2_win1251(getChar(text), convertedTextPointer);
//         std::cout << "[POST]" << " " << convertedTextPointer << std::endl;
        
//         try {
//             // runMorphAnalyze(convertedTextPointer);
//         } catch (std::exception &e) {
//             std::cout << e.what() << std::endl;
//         }
        
//         resp->setStatusCode(k200OK);
//     } else {
//         resp->setStatusCode(k400BadRequest);
//     }
    
//     callback(resp);
// }