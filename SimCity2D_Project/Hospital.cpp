#include "Hospital.h"

#pragma region Constructors

Hospital::Hospital(const unsigned int height, const sf::Texture & texture, const TileSpecialise tileSpecialise, const std::vector<Frames> & frames)
	:Structure(height, tileSpecialise, texture, frames)
{
	this->heightBuilding = height;

	this->vehicle1 = new Vehicle(Vehicle::VehicleType::AMBULANCE);
	this->hasVehicle = true;
	this->vehicle1->SetBuildingOwner(this);

	this->BuildHospital();
	this->driveToDestination = new DriveToDestination();
}

Hospital::~Hospital()
{
	try {
		for (int i = 0; i < patients.GetSize(); i++)
		{
			if (this->patients.GetObjects()[i] != nullptr)
			{
				delete this->patients.GetObjects()[i];
				this->patients.GetObjects()[i] = nullptr;
			}
		}
	}
	catch (const std::out_of_range& e) {
	}
}

std::unique_ptr<SmallTile> Hospital::clone() const
{
	return std::make_unique<Hospital>(heightBuilding, texture, tileSpecialise, frames);
}

#pragma endregion

#pragma region Class_Methods

void Hospital::BuildHospital()
{
	if (this->buildDays == 0)
	{
		this->sprite.setTexture(this->textureBuildManager.GetBuildingTexture());
		this->heightBuilding = this->textureBuildManager.GetBuildingProcessHeight();
		this->buildedStructure = false;
	}

	this->buildDays++;

	if (this->buildDays > 5)
	{
		this->sprite.setTexture(this->textureBuildManager.GetAppropriateTexture("hospital"));
		this->heightBuilding = 2;
		this->buildedStructure = true;
	}
}

void Hospital::InitializeHospitalParameters(IDvector<Hospital::Patient*> patients, int hospitalWorkers, int maxHospitalWorkers,
	int maxPatients, int healedPatients, int healthAndWalfareStructure, float healthAndWalfarePercentage)
{
	this->patients = patients;
	this->hospitalWorkers = hospitalWorkers;
	this->maxHospitalWorkers = maxHospitalWorkers;
	this->maxPatients = maxPatients;
	this->healedPatients = healedPatients;
	this->healthAndWalfareStructure = healthAndWalfareStructure;
	this->healthAndWalfatePercentage = healthAndWalfarePercentage;
}

void Hospital::NewDayHospital()
{
	this->healedPatients = 0;
	for (auto & patient : this->patients.GetObjects())
	{
		patient->daysToHeal--;

		if (patient->daysToHeal < 0)
		{
			patient->returnToHome = true;
			this->healedPatients++;
		}
	}

	if (this->healedPatients < 0)
	{
		this->healedPatients = 0;
	}

	if (this->healthAndWalfatePercentage < (this->patients.GetSize() + this->hospitalWorkers))
	{
		this->strike = true;
	}
	else
	{
		this->strike = false;
	}
}

void Hospital::AddPatients(ID houseID)
{
	this->tmpPatient = new Patient;
	tmpPatient->homeID = houseID;
	tmpPatient->patientID = UNDEFINED;
	tmpPatient->daysToHeal = 5;
	tmpPatient->returnToHome = false;

	ID id = this->patients.Push(tmpPatient);
	this->tmpPatient->patientID = id;
}

void Hospital::Update(float elapsedTime)
{
	this->ProcessDriving(elapsedTime);
}

bool Hospital::ReturnPatientToHouse(ID id)
{
	for (auto & patient : this->patients.GetObjects())
	{
		if (patient->homeID == id && patient->returnToHome == true)
		{
			this->patients.PopID(patient->patientID);
			this->healedPatients--;
			return true;
		}
	}
	return false;
}

int Hospital::UpdateWorkersPopulation(int newWorkers)
{
	int overPeople = 0;

	if (this->hospitalWorkers < this->maxHospitalWorkers)
	{
		this->hospitalWorkers += newWorkers;

		if (this->hospitalWorkers > this->maxHospitalWorkers)
		{
			overPeople = this->hospitalWorkers - this->maxHospitalWorkers;
			this->hospitalWorkers -= overPeople;
		}
		return overPeople;
	}
	return newWorkers;
}

#pragma endregion

#pragma region Setters

void Hospital::SetHealthAndWalfare(float healthAndWalfare)
{
	this->healthAndWalfatePercentage = healthAndWalfare;
}

#pragma endregion

#pragma region Getters

IDvector<Hospital::Patient*> & Hospital::GetPatients() 
{
	return this->patients;
}

int Hospital::GetHealthAndWalfareStructure() const
{
	return this->healthAndWalfareStructure * this->healthAndWalfatePercentage / 100.0f;
}

int Hospital::GetMaxPatients() const
{
	return this->maxPatients;
}

int Hospital::GetMaxHospitalWorkers() const
{
	return this->maxHospitalWorkers;
}

bool Hospital::GetIsHospitalWorking() const
{
	if (this->hospitalWorkers > 10)
	{
		return true;
	}
	return false;
}

float Hospital::GetHealthAndWalfarePercentage() const
{
	return this->healthAndWalfatePercentage;
}

bool Hospital::GetIsPatientReady() const
{
	if (this->healedPatients > 0)
	{
		return true;
	}
	return false;
}

int Hospital::GetHospitalWorkersAmount() const
{
	return this->hospitalWorkers;
}

int Hospital::GetPatientsAmount() const
{
	return this->patients.GetSize();
}

int Hospital::GetHealedPatients() const
{
	return this->healedPatients;
}

#pragma endregion