#ifndef Hospital_hpp
#define Hospital_hpp

#include "Structure.h"

class Hospital : public Structure
{
public:
	struct Patient
	{
		ID homeID;
		ID patientID;
		int daysToHeal;
		bool returnToHome;
	};

private:
	Patient *tmpPatient = nullptr;

	IDvector<Patient*> patients;

	int hospitalWorkers = 0;
	int maxHospitalWorkers = 15;
	int maxPatients = 20;
	int healedPatients = 0;
	int healthAndWalfareStructure = 10000;
	float healthAndWalfatePercentage = 0.0f;

public:
	Hospital() = default;
	Hospital(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);
	virtual ~Hospital();

	virtual std::unique_ptr<SmallTile> clone() const override;
	
	void InitializeHospitalParameters(IDvector<Patient*> patients, int hospitalWorkers, int maxHospitalWorkers,
		int maxPatients, int healedPatients, int healthAndWalfareStructure, float healthAndWalfarePercentage);
	void AddPatients(ID patientID);
	void BuildHospital();
	bool ReturnPatientToHouse(ID id);
	void NewDayHospital();
	int UpdateWorkersPopulation(int newWorkers);
	virtual void Update(float elapsedTime) override;

	//setters
	void SetHealthAndWalfare(float healthAndWalfare);

	//getters
	float GetHealthAndWalfarePercentage() const;
	int GetHealthAndWalfareStructure() const;
	int GetMaxPatients() const;
	bool GetIsPatientReady() const;
	bool GetIsHospitalWorking() const;
	int GetHospitalWorkersAmount() const;
	int GetMaxHospitalWorkers() const;
	int GetPatientsAmount() const;
	int GetHealedPatients() const;
	IDvector<Patient*> & GetPatients();
};

#endif // !Hospital_hpp

