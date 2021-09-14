#include "bus.hpp" 
void Routes::RemoveRoute(Bus bus) {
routes.erase(bus);
}
void Routes::AddRoute(Bus bus, vector<Street> streets) {
    routes[bus] = streets;
}
void Streets::AddBus(Street street) { streets.push_back(street); }
void Streets::RemoveStreet(Street street) {
    streets.erase(std::find(streets.begin(), streets.end(), street));
}
void Buses::RemoveBus(Bus bus) {
    buses.erase(std::find(buses.begin(), buses.end(), bus));
}
void Buses::AddBus(Bus bus) { buses.push_back(bus); }
