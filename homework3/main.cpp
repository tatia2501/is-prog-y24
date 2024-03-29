#include <fstream>
#include <iostream>
#include "pugixml.hpp"
#include <vector>
#include <math.h>
#include <set>
#include <string>
#pragma execution_character_set("utf-8")

struct Stopping {
    std::string name;
    std::string type_of_vehicle;
    std::vector <std::string> location;
    std::vector <std::string> routes;
    double coor1, coor2;
};

//fixed functions from small letter
void most_stops_route(const std::vector<Stopping>& vec) {
    std::multiset<std::string> routes;
    for (const auto& i : vec) {
        for (const auto& j : i.routes) {
            routes.insert(j);
        }
    }
    int max = 0;
    std::string max_route;
    //fixed use range-based for
    for (const auto& index : routes) {
        int num = routes.count(index);
        if (max < num) {
            max = num;
            max_route = index;
        }
    }

    std::cout << "маршрут " << max_route << " (" << max << " ост.)" << std::endl;
}

void longest_route(const std::vector<Stopping>& vec) {
    std::set<std::string> routes;
    //fixed const auto& is better
    for (const auto& i : vec) {
        for (const auto& j : i.routes) {
            routes.insert(j);
        }
    }
    std::string max_route;
    std::vector<std::string> routes1;
    //fixed range-based for
    //fixed nope, it's still not range-based
    for (const auto& index : routes) {
        routes1.push_back(index);
    }

    double coor1_n = 0, coor2_n = 0;
    std::vector<double> distance(routes1.size(), 0);
    //fixed consts
    //fixed dont use ,
    //fixed const CAPS
    const double DEG_TO_KM1 = 111.357;
    const double DEG_TO_KM2 = 55.8;

    for (int q = 0; q < routes1.size(); q++) {
        for (const auto& i : vec) {
            for (const auto& j : i.routes) {
                if (j == routes1[q]) {
                    if (coor1_n != 0) {
                        distance[q] += sqrt(pow((i.coor1 - coor1_n) * DEG_TO_KM1, 2) + pow((i.coor2 - coor2_n) * DEG_TO_KM2, 2));
                    }
                    coor1_n = i.coor1;
                    coor2_n = i.coor2;
                }
            }
        }
        coor1_n = 0;
        coor2_n = 0;
    }

    int max = 0;
    for (int q = 0; q < distance.size(); q++) {
        if (distance[max] < distance[q])
            max = q;
    }
    std::cout << "маршрут " << routes1[max] << " (расстояние: " << distance[max] << "км)" << std::endl;
}

std::multiset<std::string> streets;
void down_with_copypaste(const std::vector<Stopping>& vec) {
    for (const auto& i : vec) {
        for (const auto& j : i.location) {
            if (j.length() > 1) streets.insert(j);
        }
    }
}

void most_stops_street(const std::vector<Stopping>& vec1, const std::vector<Stopping>& vec2, const std::vector<Stopping>& vec3) {
    //fixed copy-paste
    down_with_copypaste(vec1);
    down_with_copypaste(vec2);
    down_with_copypaste(vec3);

    int max = 0;
    std::string max_st;
    for (std::multiset<std::string> ::iterator index = streets.begin(); index != streets.end(); index++) {
        int num = streets.count(*index);
        if (max < num) {
            max = num;
            max_st = *index;
        }
    }

    std::cout << max_st << " (" << max << " ост.)" << std::endl;
}

int main() {
    system("chcp 65001");

    pugi::xml_document doc;
    std::ifstream stream("info.xml");
    pugi::xml_parse_result result = doc.load(stream);
    pugi::xml_node data = doc.child("dataset").child("transport_station");

    std::vector <Stopping> tram_stoppings;
    std::vector <Stopping> trolley_stoppings;
    std::vector <Stopping> bus_stoppings;

    while (data) {
        std::string one_str;
        std::vector <std::string> location;
        std::string location1 = data.child_value("location");
        bool check = 1;

        for (char c : location1) {
            if (check) {
                if (c == ',') {
                    location.push_back(one_str);
                    one_str.clear();
                    check = 0;
                }
                else one_str.append(1, c);
            }
            else check = 1;
        }
        location.push_back(one_str);
        one_str.clear();

        std::vector <std::string> routes;
        std::string routes1 = data.child_value("routes");

        for (char c : routes1) {
            if (c == ',' || c == '.') {
                routes.push_back(one_str);
                one_str.clear();
            }
            else one_str.append(1, c);
        }
        routes.push_back(one_str);
        one_str.clear();

        std::string coor = data.child_value("coordinates");
        double coor1 = atof(coor.substr(0, 9).c_str());
        double coor2 = atof(coor.substr(10, 9).c_str());

        Stopping one_stopping = {
            data.child_value("the_official_name"),
            data.child_value("type_of_vehicle"),
            location,
            routes,
            coor1,
            coor2
        };

        if (one_stopping.type_of_vehicle == "Автобус") {
            bus_stoppings.push_back(one_stopping);
        }
        if (one_stopping.type_of_vehicle == "Трамвай") {
            tram_stoppings.push_back(one_stopping);
        }
        if (one_stopping.type_of_vehicle == "Троллейбус") {
            trolley_stoppings.push_back(one_stopping);
        }
        data = data.next_sibling();
    }
    std::cout << "1. Маршрут с наибольшим количеством остановок" << std::endl;
    std::cout << "Трамвай: ";
    most_stops_route(tram_stoppings);
    std::cout << "Троллейбус: ";
    most_stops_route(trolley_stoppings);
    std::cout << "Автобус: ";
    most_stops_route(bus_stoppings);

    std::cout << std::endl;

    std::cout << "2. Наиболее длинный маршрут" << std::endl;
    std::cout << "Трамвай: ";
    longest_route(tram_stoppings);
    std::cout << "Троллейбус: ";
    longest_route(trolley_stoppings);
    std::cout << "Автобус: ";
    longest_route(bus_stoppings);

    std::cout << std::endl;

    std::cout << "3. Улица с наибольшим количеством остановок" << std::endl;
    most_stops_street(tram_stoppings, trolley_stoppings, bus_stoppings);

    return 0;
}
