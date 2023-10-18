#include <vector>
#include <string>

/**
 * Класс для работы с JSON-файлами
 */
class ConverterJSON {
public:
    ConverterJSON() = default;

    /**
     * @brief Член-функция получения содержимого файлов
     * @return Возвращает список с содержимым файлов, перечисленных в config.json
     */
    std::vector<std::string> getTextDocuments();

    /**
     * @brief Член-функция считывает поле max_responses для определения предельного количества
     * ответов на один запрос
     * @return Значения предельного количества ответов
     */
    int getResponsesLimit();

    /**
     * @brief Член-функция получения запросов из файла requests.json
     * @return Список запросов из файла requests.json
     */
    std::vector<std::string> getRequests();

    /**
     * Положить в файл answers.json результаты поисковых запросов
     */
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};