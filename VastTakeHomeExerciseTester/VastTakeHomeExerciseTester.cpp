// File for testing the Operation project/class
#include "pch.h"
#include "CppUnitTest.h"

// For MSVS Test Framework to work/link, needed to manually include these files
#include "../VastTakeHomeExercise/Operation.h"
#include "../VastTakeHomeExercise/Operation.cpp"
#include "../VastTakeHomeExercise/Component.cpp"
#include "../VastTakeHomeExercise/Truck.cpp"
#include "../VastTakeHomeExercise/Station.cpp"
#include "../VastTakeHomeExercise/common.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Since the simulation is a constant time
// the time a truck spent in each state should
// add up to the total time of the simulation always
void validateTotalTimeCounts(Operation& op)
{
	auto trucksAfterSimulationRun = op.getTrucks();
	for (const auto& truck : trucksAfterSimulationRun)
	{
		// Iterate through all trucks and make sure that, for each truck
		// the sum of the time of each state equals the time of the simulation run
		int timeCount = 0;
		auto truckStatistics = truck->getTotalStatistics();
		for (const auto& stat : truckStatistics)
		{
			timeCount += stat.second;
		}
		// Ensure times match
		Assert::AreEqual(timeCount, simulationTotalRuntime);
	}
}

// Ensure truck logs after simulation match expected/required pattern
void validateTruckLogs(Operation& op)
{
	auto trucksAfterSimulationRun = op.getTrucks();
	for (const auto& truck : trucksAfterSimulationRun)
	{
		auto truckLog = truck->getLog();
		for (int i = 0; i < truckLog.size() - 1; i++)
		{
			const auto& currLog = truckLog[i];
			const auto& nextLog = truckLog[i + 1];
			// Based on current state, only certain state will/can follow. e.g. after a truck unloads,
			//  it has to move to a next station
			if (currLog.truckState == TruckStatus::unset && nextLog.truckState != TruckStatus::moving)
				Assert::Fail();
			if (currLog.truckState == TruckStatus::moving && (nextLog.truckState != TruckStatus::queuing &&
				nextLog.truckState != TruckStatus::mining))
				Assert::Fail();
			if (currLog.truckState == TruckStatus::mining && nextLog.truckState != TruckStatus::unloading)
				Assert::Fail();
			if (currLog.truckState == TruckStatus::unloading && nextLog.truckState != TruckStatus::moving)
				Assert::Fail();
			if (currLog.truckState == TruckStatus::queuing && nextLog.truckState != TruckStatus::mining)
				Assert::Fail();
		}
	}
}

// Run all validations on the Operation
void runAllValidations(Operation& op)
{
	validateTotalTimeCounts(op);
	validateTruckLogs(op);
}

namespace VastTKeHomeExerciseTester
{
	// Operations can vary, due to randomness of mining time. Some things must always be
	// true and can be tested for to verify expected behavior. Tests are run on varying 
	// numbers of trucks and stations to ensure these expected behaviors remain true.
	// Additional tests can be created to test additional conditions like time duration of each status
	// as well as tests about number of stations and what trucks are there and in their queue.
	TEST_CLASS(OperationTests)
	{
	public:
		TEST_METHOD(OneStation_OneTruck)
		{
			OperationConfig opConfig{ 1,1 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(ThreeStation_ThreeTruck)
		{
			OperationConfig opConfig{ 3,3 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(TenStation_TenTruck)
		{
			OperationConfig opConfig{ 10,10 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(TwoStation_FourTruck)
		{
			OperationConfig opConfig{ 2,4 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(FourStation_TwoTruck)
		{
			OperationConfig opConfig{ 4,2 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(SevenStation_TenTruck)
		{
			OperationConfig opConfig{ 7,10 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
		TEST_METHOD(TenStation_SevenTruck)
		{
			OperationConfig opConfig{ 10,7 };
			Operation op{ opConfig };
			op.RunSimulation();
			runAllValidations(op);
		}
	};
}
