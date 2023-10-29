#include "ConverterJSON.h"

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <algorithm>

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
    // Создание структур для последующей записи в файл
    struct Relevance {
        int docid;
        double rank;
    };

    struct Request {
        std::string name;
        bool result;
        std::vector<Relevance> relevance;
    };
    int countOfRequests = 1;

    // Заполняем вектор структур
    std::vector<Request> requests;
    for (const auto& request : answers) {
        Request requestInStruct;

        // Создание корректного имени запроса: добавление трехзначного числа в конец
        constexpr int lenEnding = 3;
        std::string endingOfRequetsName = std::to_string(countOfRequests);
        requestInStruct.name = "request" + std::string(lenEnding - endingOfRequetsName.size(), '0').append(endingOfRequetsName);

        if (!request.empty()) {
            requestInStruct.result = true;
            for (const auto& [docId, rank] : request) {
                Relevance relevanceTemp = {
                    .docid = docId,
                    .rank = rank
                };
                requestInStruct.relevance.push_back(relevanceTemp);
            }
        } else
            requestInStruct.result = false;
        requests.push_back(requestInStruct);
        countOfRequests++;
    }

    // Заполняем объект json
    nlohmann::json jsonRequests;
    for (const auto& request : requests) {
        nlohmann::json jsonRequest;
        if (request.result) {
            for (const auto& [docId, rank] : request.relevance)
                if (request.relevance.size() > 1) {
                    jsonRequest[request.name]["result"] = "true";
                    jsonRequest[request.name]["relevance"].push_back({ { "docid", docId }, { "rank", rank } });
                } else if (request.relevance.size() == 1)
                    jsonRequest[request.name] = { { "result", "true" }, { "docid", docId }, { "rank", rank } };
        } else
            jsonRequest[request.name]["result"] = "false";

        jsonRequests["answers"].push_back(jsonRequest);
    }

    std::ofstream answersFile("../answers.json");
    answersFile << jsonRequests.dump(getResponsesLimit());
    answersFile.close();
}
