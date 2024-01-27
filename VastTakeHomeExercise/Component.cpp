#include "Component.h"
// Tell observer(station) to update base. Once a truck is done at a station
// the corresponding station can take action to take the next
// truck in the queue. Observer is cleared.
void Component::notifyObserver(minutes currentTimeOfSimulation)
{
    if (observer)
    {
        observer->update(currentTimeOfSimulation);
        observer = nullptr;
    }
}