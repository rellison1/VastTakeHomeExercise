#pragma once
// This file contains the class and data for a Station representation
#include "Component.h"
#include <queue>
class Station : public Component
{
private:
    // Unique ID of each Station
    tag id{ 0 };

    // Queue of components representing objects in line to enter/visit the Station
    std::queue<Component*> queue{};

    // The current component/truck at the station. Nullptr if no component is at the station.
    Component* currentTruck{nullptr};
public:
    Station()
    {
        static tag ID{ 0 };
        id = ID++;
    }
    ~Station()=default;

    tag getID() const { return id; }

    size_t getQueueLength() const { return queue.size(); }

    void AddComponentToQueue(Component* component);

    virtual void update(minutes currentTimeOfSimulation);

    virtual void print() const;

    // Get/set truck at the station
    Component* getCurrentTruck() { return currentTruck; }
    void setCurrentTruck(Component* truck) { currentTruck = truck; }
};
