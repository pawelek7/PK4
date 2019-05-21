#ifndef Hospital_hpp
#define Hospital_hpp

#include "Structure.h"

class Hospital : public Structure
{
	int hospitalWorkers = 0;
	int patients = 0;



public:
	Hospital() = default;
	Hospital(const unsigned int height, const sf::Texture & texture, const TileSpecialise, const std::vector<Frames> & frames);

	virtual std::unique_ptr<SmallTile> clone() const override;
	
	void AddPatients(int patients);
	void BuildHospital();
	virtual void Update(float elapsedTime) override;
	virtual void Destroy() override;
	virtual void UpdateInformation() override;
};

#endif // !Hospital_hpp

