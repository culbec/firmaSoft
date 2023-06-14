#pragma once

#include "Observer.h"
#include <memory>
#include <vector>

using std::make_unique;
using std::unique_ptr;
using std::vector;

class Observable{
private:
    vector<Observer*> observers;

public:
    /*
     * Adauga un observer in lista
     * @param observer: observer-ul de adaugat in lista
     */
    virtual void addObserver(Observer* observer) {
        this->observers.push_back(observer);
    }

    /*
     * notifica toti observerii din lista
     */
    virtual void notify() {
        for(const auto& observer: this->observers) {
            observer->update();
        }
    }

    virtual ~Observable() = default;
};