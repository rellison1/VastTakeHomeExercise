#pragma once
// This file contains the class and data for the representation of an Operation
#include "Station.h"
#include "Truck.h"
#include <vector>
#include <queue>
#include <string>

// Configuration/Input for Operation
struct OperationConfig
{
    int numStations{0};
    int numTrucks{0};
};

// Simple class created to enable comparison of Stations for priority queue sorting
class StationCompare
{
    public:
        bool operator()(Station* stat1, Station* stat2);
};

// Class to model an operation which
class Operation
{
    public:
        Operation(const OperationConfig& config);
        Operation() = delete;
        ~Operation();
        // Start the process of the simulation
        void RunSimulation();
        const std::vector<Truck*>& getTrucks() { return trucks; }
        const std::priority_queue<Station*,std::vector<Station*>,StationCompare>& getStations() { return stations; }
    private:
        // Collection of trucks
        // Other container might be more performant since, at initialization time, we would know
        // the size of the collection
        std::vector<Truck*> trucks;

        // Stations for this operation stored in a priority queue. Since stations should be
        // picked by first available station or smallest queue, priority queue should sort
        // and keep the available or smallest queue stations at the top of the queue.
        std::priority_queue<Station*,std::vector<Station*>,StationCompare> stations;
    private:
        
        // Update operation based on time of the simulation run
        void update(int currentTimeOfSimulation);
        
        // Print information for all stations
        void printStations();

        // The station queue needs refreshing to ensure
        // priority is maintained as underlying stations could be
        // modified and the queue itself does not always self adjust unless
        // manually refreshed
        void refreshStationQueue();
};