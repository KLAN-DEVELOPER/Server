#pragma once
#include <./src/providers/KlanEngineProvider.h>

void runMorphAnalyze(char *text) {
    klanEngine->Run(text, 0, nullptr);
}