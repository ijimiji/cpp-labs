#pragma once
#include "mvc.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <map>

using std::string;
using std::map;
using std::tuple;
using std::vector;
enum Color { Red, Blue, Green };
enum Size { Small, Big, Huge };
typedef tuple<int, string> Street;
typedef tuple<int, Color, Size> Bus;

class Buses : public BaseModel {
    vector<Bus> buses;
    void AddBus(Bus bus);
    void RemoveBus(Bus bus);
};

class Streets : public BaseModel {
    vector<Street> streets;
    void AddBus(Street street);
    void RemoveStreet(Street street);
};

class Routes : public BaseModel {
    map <Bus, vector<Street>> routes;
    void AddRoute(Bus bus, vector<Street> streets);
    void RemoveRoute(Bus bus);
};

