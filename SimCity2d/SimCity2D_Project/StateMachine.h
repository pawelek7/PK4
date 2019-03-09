#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stack>
#include <map>
#include <memory>
#include <iostream>

#include "StateOfProgram.h"

class StateMachine
{
	int nrOfStates = 0;
	std::string stateName = "unknown";
	std::map<int, std::string> mapState;
	bool remove = false;
	bool add = false;
	bool stop = false;

	std::stack<std::unique_ptr<StateOfProgram>> state;
	std::unique_ptr<StateOfProgram> ptrState = nullptr;
	
public:
	StateMachine() = default;
	~StateMachine() = default;

	void NewState(std::unique_ptr<StateOfProgram> newState, std::string stateName = "unknown");
	std::unique_ptr<StateOfProgram> & GetStateFromStack();
	void ChangeState();
	void PopState();
	void DeleteStack();

	//getters
	int GetNumberOfState() const;
	std::string GetStateName();
};

#endif // !StateMachine_hpp