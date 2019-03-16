#ifndef StateMachine_hpp
#define StateMachine_hpp

#include "StateOfProgram.h"

#include <stack>
#include <map>
#include <memory>
#include <iostream>

class StateMachine
{
	int nrOfStates = 0;
	bool remove = false;
	bool add = false;
	bool stop = false;
	std::string stateName = "unknown";
	std::map<int, std::string> mapState;

	std::stack<std::unique_ptr<StateOfProgram>> state;
	std::unique_ptr<StateOfProgram> ptrState = nullptr;
	
public:
	StateMachine() = default;
	~StateMachine() = default;

	void NewState(std::unique_ptr<StateOfProgram> newState, std::string stateName = "unknown", bool remove = false);
	std::unique_ptr<StateOfProgram> & GetStateFromStack();
	void ChangeState();
	void PopState();
	void DeleteStack();

	//getters
	int GetNumberOfState() const;
	std::string GetStateName();
};

#endif // !StateMachine_hpp