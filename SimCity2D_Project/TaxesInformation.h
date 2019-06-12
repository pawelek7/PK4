#ifndef TaxesInformation_hpp
#define TaxesInformation_hpp

#include <map>

#include "TextButton.h"
#include "TableBase.h"

class TaxesInformation : public TableBase
{
	bool alreadyInitializedVariables = false;
	bool makeChanges = false;

	int propertyTaxesIterator = 0, cityOrdiancesIterator = 0,
		policeDepartmentIterator = 0,  fireDepartmentIterator = 0, healthWelfareIterator = 0;
	int currentTreasury = 0;

	std::map<std::string, TextButton*> mapButtons;

	sf::Font font;
	sf::Text cityNameInfo, monthInfo, yearInfo;
	sf::Text propertyTaxesText, cityOrdiancesText, policeDepartmentText, 
		fireDepartmentText, healthWelfareText, currentTreasuryText;

	virtual void InitializeFont() override;
	virtual void InitializeButtons() override;
	virtual void InitializeText() override;
	virtual void InitializeBackground() override;

public:
	TaxesInformation() = default;
	TaxesInformation(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap);
	virtual ~TaxesInformation();

	virtual void UpdateTable(float elapsedTime) override;
	virtual void DrawTable() override;

	//setters
	void SetVariables(int propertyTaxesIterator, int cityOrdiancesIterator, int policeDepartmentIterator,
		int fireDepartmentIterator, int healthWelfareIterator, int currentTreasury);
	void SetAlreadyInitializedVariables(bool alreadyInitializedVariables);
	void SetMakeChanges(bool makeChanges);

	//getters
	bool GetAlreadyInitializedVariables() const;
	bool GetMakeChanges() const;
	
	int GetPropertyTaxesIterator() const;
	int GetCityOrdiancesIterator() const;
	int GetPoliceDepartmentIterator() const;
	int GetFireDepartmentIterator() const;
	int GetHealthWelfareIterator() const;
};

#endif