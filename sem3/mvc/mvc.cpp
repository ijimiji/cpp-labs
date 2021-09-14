#include "mvc.hpp"

void BaseModel::addObserver(Observer *observer) {
    _observers.push_back(observer);
}
void BaseModel::notifyUpdate() {
    for (auto &observer : _observers) {
        observer->update();
    }
}