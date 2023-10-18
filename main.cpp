#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

struct InfoActor {
    std::string name;
    std::string role;
};

struct InfoFilm {
        std::string title;
        int year;
        std::string country;
        std::string production;
        std::string writings;
        std::string produced;
        std::string directed;
        InfoActor infoActor[4];
};

int main ()
{
    /**
     *  1. Проверка существования файла "config.json"
     *  1.1 ЕСли файл отсутствует - выкинуть исключение, напечатав "config
     *  file is missing"
     *  1.2 Если файл существует - открыть
     *  2. 
     */
    nlohmann::json infoFilmOut = {
        {"Godzilla", {
            {"year", 2014},
            {"country", "USA, Japan"},
            {"production", "Warner Bros."},
            {"writings", "Ishiro Honda, Takeo Murata"},
            {"produced", "Yoshimitsu Banno"},
            {"directed", "Gareth Edwards"},
            {"cast", {
                {{"actor", "Aaron Taylor-Johnson"}, {"role", "Ford Brody"}},
                {{"actor", "Ken Watanabe"}, {"role", "Dr. Ishiro Serizawa"}},
                {{"actor", "Bryan Cranston"}, {"role", "Joe Brody"}},
                {{"actor", "Elizabeth Olsen"}, {"role", "Elle Brody"}}
            }}
        }},
        {"Tenet", {
            {"year", 2020},
            {"country", "USA"},
            {"production", "Warner Bros."},
            {"writings", "Christopher Nolan"},
            {"produced", "Christopher Nolan"},
            {"directed", "Christopher Nolan"},
            {"cast", {
                {{"actor", "John David Washington"}, {"role", "Protagonist"}},
                {{"actor", "Robert Pattinson"}, {"role", "Neil"}},
                {{"actor", "Elizabeth Debicki"}, {"role", "Kat"}},
                {{"actor", "Aaron Taylor-Johnson"}, {"role", "Ives"}}
            }}
        }},
        {"Inception", {
            {"year", 2010},
            {"country", "USA"},
            {"production", "Warner Bros."},
            {"writings", "Christopher Nolan"},
            {"produced", "Christopher Nolan"},
            {"directed", "Christopher Nolan"},
            {"cast", {
                {{"actor", "Leonardo DiCaprio"}, {"role", "Cobb"}},
                {{"actor", "Joseph Gordon-Levitt"}, {"role", "Arthur"}},
                {{"actor", "Tom Hardy"}, {"role", "Eames"}},
                {{"actor", "Ken Watanabe"}, {"role", "Saito"}}
            }}
        }},
        {"The Revenant", {
            {"year", 2015},
            {"country", "USA"},
            {"production", "New Regency Productions"},
            {"writings", "Mark L. Smith"},
            {"produced", "Markus Barmettler"},
            {"directed", "Alejandro G. Inarritu"},
            {"cast", {
                {{"actor", "Leonardo DiCaprio"}, {"role", "Hugh Glass"}},
                {{"actor", "Tom Hardy"}, {"role", "John Fitzgerald"}},
                {{"actor", "Domhnall Gleeson"}, {"role", "Captain Andrew Henry"}},
                {{"actor", "Will Poulter"}, {"role", "Bridger"}}
            }}
        }},
        {"Venom", {
            {"year", 2018},
            {"country", "USA"},
            {"production", "Sony Inc."},
            {"writings", "Jeff Pinkner"},
            {"produced", "Avi Arad"},
            {"directed", "Ruben Fleischer"},
            {"cast", {
                {{"actor", "Tom Hardy"}, {"role", "Eddie Brock / Venom"}},
                {{"actor", "Michelle Williams"}, {"role", "Anne Weying"}},
                {{"actor", "Riz Ahmed"}, {"role", "Carlton Drake / Riot"}},
                {{"actor", "Scott Haze"}, {"role", "Security Chief Roland Treece"}}
            }}
        }}
    };

    std::ofstream filmInfoOut("filmInfo.json");
    filmInfoOut << infoFilmOut;
    filmInfoOut.close();

    std::ifstream filmInfoIn("filmInfo.json");
    nlohmann::json infoFilmIn;// = nlohmann::json::parse(filmInfoIn);
    filmInfoIn >> infoFilmIn;


    InfoFilm infoFilms[5];
    int index1 = 0;
    int index2 = 0;
    
    std::string names[] = {"Godzilla", "Tenet", "Inception", "The Revenant", "Venom"};
    for (auto& film : infoFilmIn) {
        infoFilms[index1].title = names[index1];
        infoFilms[index1].year = film["year"];
        infoFilms[index1].country = film["country"];
        infoFilms[index1].production = film["production"];
        infoFilms[index1].writings = film["writings"];
        infoFilms[index1].produced = film["produced"];
        infoFilms[index1].directed = film["directed"];
        for (auto& cast : film["cast"]) {
            infoFilms[index1].infoActor[index2].name = cast["actor"];
            infoFilms[index1].infoActor[index2].role = cast["role"];
            index2++;
        }
        index2 = 0;
        index1++;
    }
    
    std::string nameActor;
    std::cout << "Enter fist name or last name of actor" << std::endl;
    std::cin >> nameActor;

    for (auto& film : infoFilms) {
        for (auto& actor : film.infoActor) {
            if (actor.name.find(nameActor) != std::string::npos)
                std::cout << actor.name << ": " << "\"" << film.title << "\"" << " - " << actor.role << std::endl;
        }
    }

    return 0;   
}
