#pragma once

#include <vector>

class Observer
{
public:
    virtual void update() = 0;
};

class BaseModel
{
public:
   void addObserver(Observer *observer);
   void notifyUpdate();
private:
   std::vector<Observer*> _observers;
}; 

template<typename Model>
class Controller
{
public:
   Controller(Model *model)
   {
      _model = model;
   }
private:
   Model *_model;
};

template <typename Model> class ConsoleView : public Observer {
  public:
    ConsoleView(Model *model) : _model(model){
        _model->addObserver(this);
    }
    virtual void render() = 0;
  private:
    Model *_model;
};