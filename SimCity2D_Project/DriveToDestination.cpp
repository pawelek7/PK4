#include "DriveToDestination.h"

#pragma region Constructors

DriveToDestination::DriveToDestination(Structure *buildingOwner, Structure *destinationTarget)
{
	this->buildingOwner = buildingOwner;
	this->destinationTarget = destinationTarget;
}

DriveToDestination::~DriveToDestination()
{
	if (this->route != nullptr)
	{
		delete this->route;
		this->route = nullptr;
	}
}

#pragma endregion

#pragma region Class_Metods

void DriveToDestination::ActivateProcedure(Structure *buildingOwner, Structure *destinationTarget)
{
	this->buildingOwner = buildingOwner;
	this->destinationTarget = destinationTarget;
}

void DriveToDestination::InitializeBehaviour()
{
	if (this->GetIsFreezed())
	{
		this->BeginDrivingProcess();
	}
}

void DriveToDestination::TryAgain()
{
	if (this->GetIsDefeat())
	{
		this->drivingProcess = DRIVING_PROCESS::VOID;
	}
}

DriveToDestination::DRIVING_PROCESS DriveToDestination::AnaliseDrivingProcess()
{
	while (!this->destinationTargetsQueue.empty() && this->destinationTargetsQueue.front()->MakeProgress() == DRIVING_PROCESS::AT_DESTINATION)
	{
		this->destinationTargetsQueue.front()->KillDrivingBehaviour();
		this->destinationTargetsQueue.pop_front();
	}
	return this->destinationTargetsQueue.empty() ? DRIVING_PROCESS::AT_DESTINATION : this->destinationTargetsQueue.front()->GetDrivingProcess();
}

void DriveToDestination::BeginDrivingProcess(bool returnToOwner)
{
	this->returnToOwner = returnToOwner;

	this->drivingProcess = DRIVING_PROCESS::DRIVING;

	sf::Vector2i start = this->buildingOwner->GetPosition();
	sf::Vector2i targetCoords = this->destinationTarget->GetPosition();

	std::pair<int, int> A;
	std::pair<int, int> B;


	if (returnToOwner == false)
	{
		A = std::make_pair(start.x, start.y);
		B = std::make_pair(targetCoords.x, targetCoords.y);
		this->buildingOwner->GetVehicle()->GetVehiclePhysics().SetPosition((sf::Vector2f(this->buildingOwner->GetSpritePosition().x + TILE_SIZE, this->buildingOwner->GetSpritePosition().y + TILE_SIZE / 2)));
	}
	else
	{
		B = std::make_pair(start.x, start.y);
		A = std::make_pair(targetCoords.x, targetCoords.y);
	}

	buildingOwner->GetPatchRoad()->AddConnection(A.first, A.second);
	destinationTarget->GetPatchRoad()->AddConnection(B.first, B.second);

	if (buildingOwner->GetPatchRoad()->aStarSearch(B, A))
	{
		route = new Route(buildingOwner->GetPatchRoad()->tracePath());
		buildingOwner->SetVehicleInUse(true);

		if (route->GetIsEmpty())
		{
			this->drivingProcess = DRIVING_PROCESS::DEFEAT;

			buildingOwner->SetVehicleInUse(false);
		}
		else
		{
			if (this->buildingOwner->GetHasVehicle() == true)
				this->buildingOwner->GetVehicle()->GetVehicleProcedure().SetRoute(*route);

			buildingOwner->SetVehicleInUse(true);

			sf::Vector2f tmpCalculations = this->buildingOwner->GetVehicle()->GetVehiclePhysics().GetPosition() -
				(sf::Vector2f)this->buildingOwner->GetVehicle()->GetVehicleProcedure().GetRoute().GetPreviousPosition();

			float distanceToFinish = tmpCalculations.x * tmpCalculations.x + tmpCalculations.y + tmpCalculations.y;

			if (distanceToFinish < MIN_DISTANCE)
			{
				this->drivingProcess = DRIVING_PROCESS::AT_DESTINATION;
				buildingOwner->SetVehicleInUse(false);
			}
		}
	}
	else
	{
		buildingOwner->SetVehicleInUse(false);
	}
	buildingOwner->GetPatchRoad()->RemoveConnection(A.first, A.second);
	destinationTarget->GetPatchRoad()->RemoveConnection(B.first, B.second);
}

DriveToDestination::DRIVING_PROCESS DriveToDestination::MakeProgress()
{
	this->InitializeBehaviour();

	Vehicle *vehicle = this->buildingOwner->GetVehicle();

	sf::Vector2f tmpCalculations = vehicle->GetVehiclePhysics().GetPosition() -
		(sf::Vector2f)vehicle->GetVehicleProcedure().GetRoute().GetPreviousPosition();

	float distanceToFinish = tmpCalculations.x * tmpCalculations.x + tmpCalculations.y + tmpCalculations.y;

	if (this->drivingProcess != DRIVING_PROCESS::DEFEAT && distanceToFinish < this->ARRIVE_DISTANCE)
	{
		this->drivingProcess = DRIVING_PROCESS::AT_DESTINATION;
		buildingOwner->SetVehicleInUse(false);
	}

	return this->drivingProcess;
}

void DriveToDestination::KillDrivingBehaviour()
{
	this->buildingOwner->SetHasVehicle(false);
}

void DriveToDestination::PriorityPushToQueue(std::unique_ptr<DriveToDestination> && targetAim)
{
	this->destinationTargetsQueue.emplace_back(std::move(targetAim));
}

void DriveToDestination::NormalPushToQueue(std::unique_ptr<DriveToDestination> && targetAim)
{
	this->destinationTargetsQueue.emplace_front(std::move(targetAim));
}

void DriveToDestination::EraseQueue()
{
	this->destinationTargetsQueue.clear();
}

#pragma endregion

#pragma region Setters

void DriveToDestination::SetDrivingProcess(DRIVING_PROCESS drivingProcess)
{
	this->drivingProcess = drivingProcess;
}

#pragma endregion

#pragma region Getters

DriveToDestination::DRIVING_PROCESS DriveToDestination::GetDrivingProcess() const
{
	return this->drivingProcess;
}

bool DriveToDestination::GetIsDriving() const
{
	return this->drivingProcess == DRIVING_PROCESS::DRIVING;
}

bool DriveToDestination::GetIsFreezed() const
{
	return this->drivingProcess == DRIVING_PROCESS::FREEZE;
}

bool DriveToDestination::GetIsAtDestination() const
{
	return this->drivingProcess == DRIVING_PROCESS::DRIVING;
}

bool DriveToDestination::GetIsDefeat() const
{
	return this->drivingProcess == DRIVING_PROCESS::DEFEAT;
}

bool DriveToDestination::GetIsQueueEmpty() const
{
	return !this->destinationTargetsQueue.empty();
}

#pragma endregion