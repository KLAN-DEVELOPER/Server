#include "api_analyzer.h"

using namespace api;

IKNManager * klanManager = GenerateAPIManager();
IKNEngine* klanEngine = klanManager->GetEngine();




void getWordData(IKNWordShell *shell ) {
    std::cout << "=====WORD=====" << std::endl;
    
    if (!shell) {
        std::cout << "word shell is undefined " << std::endl;
        return;
    }
    
    std::cout << "word position " << shell->GetPosId() << std::endl;
    std::cout << "word form " << shell->GetForm() << std::endl;
    IKNWord *word = shell->GetWord();
    char wordStem[500];
    char * wordStemPointer = wordStem;
    word->GetStem(wordStemPointer);
    std::cout << "word value " << wordStem << std::endl;
    std::cout << "word part speach " << word->GetPartSpeech() << std::endl;
}



void runKlanMorphAnalyzer(char* text) {
    uint len = 0;
    t_errno err = klanEngine->Run(text, 0, &len);

    IKNResultList* res = klanEngine->GetResultList();
    auto count = res->GetCount(0);

    IKNResultList *analyzeResult = klanEngine->GetResultList();
    analyzeResult->InitWordsList();
    int wordCount = analyzeResult->GetCount(0);
    
    if (wordCount == 0) {
        std::cout << "wordCount is 0. No one word have been analyzed" << std::endl;
        return;
    }
    
    for (size_t i = 1; i < wordCount; i++)
    {
        getWordData(analyzeResult->GetNextWordShell());
    }
}


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
    
    if (!reqData)
    {
        resp->setStatusCode(k400BadRequest);
        resp->setBody("no provided text");
        callback(resp);
        return;
    }

    const char *text = (*reqData)["text"].asCString();
    std::cout << *text << std::endl;
    
    char *convertedText = convertToCP1251(text);
    
    std::cout << *convertedText << std::endl;

    runKlanMorphAnalyzer(convertedText);

    resp->setStatusCode(k200OK);
    callback(resp);
}
