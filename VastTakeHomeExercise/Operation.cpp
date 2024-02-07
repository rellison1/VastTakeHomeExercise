#include "Operation.h"
#include <iostream>

// Comparison function for priority queue usage to sort stations
// by priority where highest priority are the stations with the lowest
// number of trucks at the station
bool StationCompare::operator()(Station* station1, Station* station2)
{
    // # of trucks in queue is equivalent to length of the queue + if there is a truck at the station
    size_t trucksInQueueAtStation1 = station1->getQueueLength();
    if(station1->getCurrentTruck())
        trucksInQueueAtStation1++;

    size_t trucksInQueueAtStation2 = station2->getQueueLength();
    if(station2->getCurrentTruck())
        trucksInQueueAtStation2++;

    return trucksInQueueAtStation1 > trucksInQueueAtStation2;
}

Operation::Operation(const OperationConfig& config)
{
    // Create and collect (in corresponding containers) all the
    // trucks and stations for this operation
    // Using raw pointers but smart pointers would be good alternative
    // to more likely protect from memory leaks
    for (int i = 0; i < config.numTrucks; i++)
        trucks.push_back(new Truck());
    for (int i = 0; i < config.numStations; i++)
        stations.push(new Station());
}

Operation::~Operation()
{
    // Iterate through containers and ensure created trucks and stations are deleted
    for (auto x : trucks)
        delete x;
    while (!stations.empty())
    {
        delete stations.top();
        stations.pop();
    }
}

void Operation::update(int currentTimeOfSimulation)
{
    bool updatedAtCurrentTime = false;
    for (auto& x : trucks)
    {
        minutes lastUpdatedTime = x->getLastUpdatedTime();

        switch(x->getCurrentStatus())
        {
            // If the truck does not have a set status (start of operation)
            // then set truck's to moving (heading to station)
            case TruckStatus::unset:
                x->setStatus(currentTimeOfSimulation,TruckStatus::moving);
                updatedAtCurrentTime = true;
                break;
            case TruckStatus::moving:
                // The last update time was when this truck started moving. If the current
                // time of the simulation equals when the truck started moving and the time it takes
                // for the truck to move, then moving has finished.
                if (currentTimeOfSimulation >= lastUpdatedTime + truckTransitionTime)
                {
                    Station* currTop = stations.top();
                    if(stations.top()->getCurrentTruck() != nullptr)
                    {
                        // If the most available station is not available/open, then 
                        // set this truck to queuing (as it has to wait for a station to be available)
                        x->setStatus(currentTimeOfSimulation,TruckStatus::queuing);
                        currTop->AddComponentToQueue(x);
                    }
                    else
                    {
                        // If a station is available, the truck can start mining as the station is open
                        currTop->setCurrentTruck(x);
                        x->setStatus(currentTimeOfSimulation,TruckStatus::mining);
                        x->setObserver(currTop);
                    }
                    // Ensure station queue is refreshed
                    refreshStationQueue();
                    updatedAtCurrentTime = true;
                }
                break;
            case TruckStatus::mining:
                // If the truck has finished mining, then set the truck to start unloading
                if (currentTimeOfSimulation >= lastUpdatedTime + x->getCurrentMiningSessionDuration())
                {
                    x->setStatus(currentTimeOfSimulation,TruckStatus::unloading);
                    updatedAtCurrentTime = true;
                }
                break;
            case TruckStatus::unloading:
                // If the truck has finished unloading, then set it to start moving
                if (currentTimeOfSimulation >= lastUpdatedTime + truckUnloadTime)
                {
                    x->setStatus(currentTimeOfSimulation,TruckStatus::moving);
                    refreshStationQueue();
                    updatedAtCurrentTime = true;
                }
                break;
            case TruckStatus::queuing:
                // No action needed when a truck is queueing. It will be moved out of queue by the station
                break;
            default:
                break;
        }
        // Update statistic for every time update
        x->updateStatistics();
    }
    // If there was a change made, print to console
    if(updatedAtCurrentTime)
    {
        std::cout << "@ Minute '" << currentTimeOfSimulation << "' of simulation: " << std::endl;
        for (auto& x : trucks)
        {
            std::cout << "\t";
            x->print();
        }
        printStations();
        std::cout << std::endl;
    }
}

// A priority queue of stations does not automatically detect
// and update when underlying stations queues are changed. 
// To force refresh, pop and push a station to resort
void Operation::refreshStationQueue()
{
    Station* currTop = stations.top();
    stations.pop();
    stations.push(currTop);
}

// Print info for each station. As a priority queue cannot be
// iterated over, all items must be popped off(printed) and then
// added back into the priority queue
void Operation::printStations()
{
    std::vector<Station*> stationHolder{};
    while (!stations.empty())
    {
        stationHolder.push_back(stations.top());
        std::cout << "\t";
        stations.top()->print();
        stations.pop();
    }
    for(auto& x : stationHolder)
        stations.push(x);

}

// Main function where simulation occurs
void Operation::RunSimulation()
{
    // Simulation starts when time is 0
    minutes currentTimeOfSimulation = 0;
    
    // Until the simulation time exceeds the intended duration of the simulation
    // keep incrementing the time of the simulation and updating the operation model
    while (currentTimeOfSimulation < simulationTotalRuntime)
    {
        try
        {
            update(++currentTimeOfSimulation);
        }
        catch (...)
        {
            std::cout << "Error in RunSimulation. Error occurred at minute " << currentTimeOfSimulation << " of simulation run." << std::endl;
            try
            {
                std::cout << "States at time of error:" << std::endl;
                for (auto& x : trucks)
                {
                    std::cout << "\t";
                    x->print();
                }
                printStations();
                break;
            }
            catch (...)
            {
                std::cout << "Error in printing current information at time of error." << std::endl;
                break;
            }
        }
    }

    std::cout << "Simulation Finished. Printing Staistics. " << std::endl;
    for (const auto& x : trucks)
    {
        x->printTotalStatistics();
    }
}
