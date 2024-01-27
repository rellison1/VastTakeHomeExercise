#pragma once
// This file contains the interface for the Component class which is the building block for
// all object representations in this program.
#include "common.h"
class Component
{
private:
    // A component that wants to respond to changes in the component
    Component* observer{ nullptr };
public:
    Component()=default;
    virtual ~Component()=default;
    
    // Print information - overrided by derived classes
    virtual void print() const { }
    
    // All components should be able to update based on the time of the simulation
    virtual void update(minutes currentTimeOfSimulation) { }
    
    // Set/Notify a component that wants to be able to respond to change in this component
    void setObserver(Component* component) { observer = component; }
    
    // Update observer to this component
    virtual void notifyObserver(minutes currentTimeOfSimulation);
    
    // Determines if the observer should be udpated
    virtual bool shouldUpdateObserver() { return false; };
    
    // Update the subject (subject of observer)
    virtual void subjectUpdate(int currentTimeOfSimulation) {};

};
