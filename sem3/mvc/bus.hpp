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

class Buses : public BaseModel<Buses> {
    public:
    vector<Bus> buses;
    void RemoveBus(Bus bus) {
        buses.erase(std::find(buses.begin(), buses.end(), bus));
        notify();
    }
    void AddBus(Bus bus) {
        buses.push_back(bus);
        notify();
    }
};

class Streets : public BaseModel<Streets> {
    public:
    vector<Street> streets;
    void AddStreet(Street street) {
        streets.push_back(street);
        notify();
    }
    void RemoveStreet(Street street) {
        streets.erase(std::find(streets.begin(), streets.end(), street));
        notify();
    }
};

class Routes : public BaseModel<Routes> {
    public:
    map<Bus, vector<Street>> routes;
    void RemoveRoute(Bus bus) {
        routes.erase(bus);
        notify();
    }
    void AddRoute(Bus bus, vector<Street> streets) {
        routes[bus] = streets;
        notify();
    }
};

class BusesController : Controller<Buses> {
    public:
    void AddBus(Bus bus){
        model.AddBus(bus);
    }
    void RemoveBus(Bus bus){
        model.RemoveBus(bus);
    }
};

class StreetsController : Controller<Streets> {
    public:
    void AddStreet(Street street){
        model.AddStreet(street);
    }
    void RemoveStreet(Street street){
        model.RemoveStreet(street);
    }
};

class RoutesController : Controller<Routes> {
    public:
    void AddRoute(Bus bus, vector<Street> streets){
        model.AddRoute(bus, streets);
    }
    void RemoveRoute(Bus bus){
        model.RemoveRoute(bus);
    }
};

class StreetsView : public BaseView<Streets, StreetsController> {
    public:
    void AddRoute(Street street){
        controller.AddStreet(street);
    }
    void RemoveRoute(Street street){
        controller.RemoveStreet(street);
    }
};
class BusesView : public BaseView<Buses, BusesController> {
    public:
    void AddBus(Bus bus){
        controller.AddBus(bus);
    }
    void RemoveBus(Bus bus){
        controller.RemoveBus(bus);
    }
};
class RoutesView : public BaseView<Routes, RoutesController> {
    public:
    void AddRoute(Bus bus, vector<Street> streets){
        controller.AddRoute(bus, streets);
    }
    void RemoveRoute(Bus bus){
        controller.RemoveRoute(bus);
    }
};
