#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stack>
#include <map>
#include <memory>
#include <iostream>

#include "StateOfProgram.h"

class StateMachine
{
	unsigned int nrOfStates = 0;

	bool removeState = false;
	bool addState = false;
	bool pauseState = false;

	std::string nameState = "unknown";

	std::map<int, std::string> mapState;
	std::stack<std::unique_ptr<StateOfProgram>> state;

	std::unique_ptr<StateOfProgram> uniqPtrState = nullptr;

public:
	StateMachine() = default;
	virtual ~StateMachine() = default;

	void NewState(std::unique_ptr<StateOfProgram> newState, std::string nameState = "unknown", bool pauseState = false);
	void ChangeState();
	void PopState();
	void DeleteWholeStack();

	int GetNumberOfState() const;
	std::unique_ptr<StateOfProgram> & GetStateFromStack();
	std::string GetNameState();
};

#endif // !StateMachine_hpp