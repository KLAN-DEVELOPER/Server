#include "api_analyzer.h"

using namespace api;

IKNManager * klanManager = GenerateAPIManager();
IKNEngine* klanEngine    = klanManager->GetEngine();


struct WordData {
    const char *form;  //Нормальная форма слова
    char stemma;       //Основа слова
    const  char *partOfSpeech;
    char morphProperty;

};



// void AddTerminToDataBase(WordData *data) {
//     auto clientPtr = drogon::app().getDbClient();
//     try {
//         auto result = clientPtr->execSqlSync("select * from users");
//     } catch (const drogon::orm::DrogonDbException &e)
//     {
//         std::cerr << "error:" << e.base().what() << std::endl;
//     }
// }


/**
 * Геттер основых параметров термина.
 * @param shell интерфейс термина.
 * @return WordData - объект, содержащий 
 * номральную форму, основу слова, часть речи и морфологические параметры.
 */
WordData* getWordData(IKNWordShell *shell ) {
    if (!shell) {
        std::cout << "word shell is undefined " << std::endl;
        return nullptr;
    }

    WordData wordData;
    
    IKNWord *word = shell->GetWord();
    word->GetStem(&wordData.stemma);
    shell->GetPropertyAsString(&wordData.morphProperty);
    
    wordData.form         =  shell->GetForm();
    wordData.partOfSpeech =  word->GetPartSpeech();
    
    WordData* ptr = &wordData;
    return ptr;
}

/**
 * Геттер парадигмы термина. 
 * @param shell интерфейс термина.
 * @return WordParadigm - объект, содержащий.
 */
void getWordParadigm(IKNWordShell *shell) {
    IKNWord *word = shell->GetWord();
    IKNParadigm* wordParadigm = word->GetParadigm();

    std::cout << "Word paradigm count: " << wordParadigm->GetCount() << std::endl;

    for(int i = 0; i < wordParadigm->GetCount(); i++) {
        std::cout << "Word ending: " << wordParadigm->GetFlex(i) << std::endl;
    }

    // Количество приставок всегда равно 0. Не понятно ошибка это или просто текст не подходящий. 
    // std::cout << "Word paradigm with prefix count: " << wordParadigm->GetCountPref() << std::endl;
    // for(int i = 0; i < wordParadigm->GetCountPref(); i++) {
    //     std::cout << "Word ending with prefix: " << wordParadigm->GetFlexPref(i) << std::endl;
    // }
}



void runKlanMorphAnalyzer(char* text) {
    uint len = 0;
    t_errno err = klanEngine->Run(text, 0, &len);

    IKNResultList* res = klanEngine->GetResultList();
    auto count = res->GetCount(0);

    res->InitWordsList();
    int wordCount = res->GetCount(0);
    
    if (wordCount == 0) {
        std::cout << "wordCount is 0. No one word have been analyzed" << std::endl;
        return;
    }
    
    for (size_t i = 1; i < wordCount; i++)
    {
        IKNWordShell *shell = res->GetNextWordShell();
        getWordData(shell);
        getWordParadigm(shell);
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
