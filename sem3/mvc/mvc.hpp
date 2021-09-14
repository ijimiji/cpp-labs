#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

template<typename Model>
class BaseModel {
  public:
    std::vector<std::function<void(Model *)> *> subscribers;
    void subscribe(std::function<void(Model *)> *sub) {
        subscribers.push_back(sub);
    }
    void notify() {
        for (auto sub : subscribers) {
            sub->operator()(this);
        }
    }
};

template<typename Model>
class Controller {
  public:
    Model &model;
    Controller(Model &m) : model(m){};
};

template<typename ModelType, typename ControllerType>
class BaseView {
  public:
    std::string modelAppearance;
    ControllerType &controller;
    BaseView(ControllerType &c) : controller(c) { c.model.subscribe(&updateView); }
    std::function<void(ModelType *)> updateView = [this](ModelType *m) {};
    void showData() { std::cout << modelAppearance << std::endl; }
};
