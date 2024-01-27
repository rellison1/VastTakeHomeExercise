#include "Station.h"
#include <iostream>

void Station::AddComponentToQueue(Component* component)
{
    // Add to queue and set the station to watch the component
    queue.push(component);
    component->setObserver(this);
}

void Station::update(minutes currentTimeOfSimulation)
{
    // Check that, based truck's status, we should perform an update now
    // This is the case when the truck is moving(left the station)
    bool updated = false;
    if(currentTruck->shouldUpdateObserver())
    {
        // If there are stations in the queue, set top of the queue to 
        // the new current truck, update it, and remove it from the queue.
        if(!queue.empty())
        {
            currentTruck = queue.front();
            currentTruck->subjectUpdate(currentTimeOfSimulation);
            queue.pop();
        }
        else
        {
            // If there are no stations in the queue, then there is no new
            // current truck for the station
            currentTruck = nullptr;
        }
    }
}

void Station::print() const
{
    std::cout << "Station #" << getID() << " has " << queue.size() << " truck(s) in the queue." << std::endl;
}