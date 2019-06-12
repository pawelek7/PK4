#ifndef Statistics_hpp
#define Statistics_hpp

#include "TableBase.h"
#include "TextButton.h"

#include <map>

class Statistics : public TableBase
{
	TextButton *closeButton = nullptr;

	sf::Text populationText, workingText, homelessText,
		happinessText, attractivnessText, moneyText, dateText,
		cityNameText, incomeThisMonthText, incomePreviousMonthText;

	virtual void InitializeFont() override;
	virtual void InitializeButtons() override;
	virtual void InitializeText() override;
	virtual void InitializeBackground() override;

public:
	Statistics() = default;
	Statistics(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap = 0);
	virtual ~Statistics();

	virtual void UpdateTable(float elapsedTime) override;
	virtual void DrawTable() override;

	//setters
	void SetPopulationText(const std::string & text);
	void SetWorkingText(const std::string & text);
	void SetHomelessText(const std::string & text);
	void SetHappinessText(const std::string & text);
	void SetAttractivnessText(const std::string & text);
	void SetMoneyText(const std::string & text);
	void SetDateText(const std::string & text);
	void SetCityNameText(const std::string & text);
	void SetIncomeThisMonthText(const std::string & text);
	void SetIncomePreviousMonth(const std::string & text);
};

#endif // !Statistics_hpp
