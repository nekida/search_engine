#include "ConverterJSON.h"

#include <fstream>
#include <nlohmann/json.hpp>

std::vector<std::string> ConverterJSON::getTextDocuments()
{
    nlohmann::json configContent;
    std::ifstream configFile("../config.json");
    configFile >> configContent;
    configFile.close();

    std::vector<std::string> listWithNameOfFiles;
    for (const auto& nameFile : configContent["files"])
        listWithNameOfFiles.push_back(nameFile);

    return listWithNameOfFiles;
}

int ConverterJSON::getResponsesLimit()
{
    nlohmann::json configContent;
    std::ifstream configFile("../config.json");
    configFile >> configContent;
    configFile.close();

    return configContent["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::getRequests()
{
    nlohmann::json requestContent;
    std::ifstream requestFile("../request.json");
    requestFile >> requestContent;
    requestFile.close();

    std::vector<std::string> listWithRequests;
    for (const auto& request : requestContent["requests"])
        listWithRequests.push_back(request);

    return listWithRequests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    if (std::filesystem::exists("../answers.json")) {
        std::fstream clear_file("../answers.json", std::ios::out);
        clear_file.close();
    }
    // TODO: запись в json
}
