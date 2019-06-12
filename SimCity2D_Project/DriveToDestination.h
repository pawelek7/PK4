#ifndef DriveToDestination_hpp
#define DriveToDestination_hpp

#include <deque>
#include <memory>
#include <iostream>

#include "Structure.h"
#include "Route.h"

class Structure;

class DriveToDestination
{
public:
	enum class DRIVING_PROCESS
	{
		VOID = 0, DRIVING = 1, FREEZE = 2, AT_DESTINATION = 3, DEFEAT = 4
	};

private:
	bool returnToOwner = false;

	static constexpr float ARRIVE_DISTANCE = 10.0f;
	static constexpr float MIN_DISTANCE = 10.0f;

	Structure *destinationTarget = nullptr;
	Structure *buildingOwner = nullptr;
	Route *route = nullptr;

	DRIVING_PROCESS drivingProcess = DRIVING_PROCESS::VOID;
	std::deque<std::unique_ptr<DriveToDestination>> destinationTargetsQueue;

public:
	DriveToDestination() = default;
	DriveToDestination(Structure *buildingOwner, Structure *destinationTarget);
	virtual ~DriveToDestination();

	void ActivateProcedure(Structure *buildingOwner, Structure *destinationTarget);

	void InitializeBehaviour();
	void TryAgain();

	DRIVING_PROCESS AnaliseDrivingProcess();
	DRIVING_PROCESS GetDrivingProcess() const;

	void PriorityPushToQueue(std::unique_ptr<DriveToDestination> && targetAim);
	void NormalPushToQueue(std::unique_ptr<DriveToDestination> && targetAim);
	void EraseQueue();

	DRIVING_PROCESS MakeProgress();
	void KillDrivingBehaviour();
	void BeginDrivingProcess(bool returnToOwner = false);

	//setters
	void SetDrivingProcess(DRIVING_PROCESS drivingProcess);

	//getters
	bool GetIsQueueEmpty() const;
	bool GetIsDriving() const;
	bool GetIsFreezed() const;
	bool GetIsAtDestination() const;
	bool GetIsDefeat() const;
};

#endif // !DriveToDestination_hpp
