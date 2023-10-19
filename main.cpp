#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "ConverterJSON.h"

int main ()
{
    try {
        if (!std::filesystem::exists("../config.json"))
            throw "config file is missing";
    } catch (const char *errorMsg) {
        std::cout << errorMsg << std::endl;
        return 1;
    }

    nlohmann::json configContent;
    std::ifstream configFile("../config.json");
    configFile >> configContent;
    try {
        if (!configContent.count("config"))
            throw "config file is empty";
    } catch (const char *errorMsg) {
        std::cout << errorMsg << std::endl;
        return 1;
    }
    configFile.close();

    ConverterJSON converterJSON;
    std::vector<std::string> base1 = converterJSON.getTextDocuments();
    std::vector<std::string> base2 = converterJSON.getRequests();
    std::cout << converterJSON.getResponsesLimit() << std::endl;
    std::vector<std::vector<std::pair<int, float>>> answers({{{1, 0.2}, {1, 0.2}}});
    converterJSON.putAnswers(answers);

    return 0;
}
