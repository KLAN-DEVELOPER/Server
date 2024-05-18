// #pragma once

// #include <drogon/HttpController.h>

// using namespace drogon;

// namespace api
// {
// class Analyze : public drogon::HttpController<Analyze>
// {
//   public:
//     METHOD_LIST_BEGIN
//     METHOD_ADD(Analyze::runAnalyze, "/text", Post);

//     METHOD_LIST_END
//     void runAnalyze(
//       const HttpRequestPtr& req,
//       std::function<void (const HttpResponsePtr &)> &&callback
//     );
// };
// }