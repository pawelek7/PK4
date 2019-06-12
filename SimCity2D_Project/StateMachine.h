#ifndef StateMachine_hpp
#define StateMachine_hpp

#include <stack>
#include <map>
#include <memory>
#include <iostream>

#include "StateOfProgram.h"
#include "NoCopyNoMove.h"

/*
A class that supports the state machine. 
Changes the states of the application.

@author
Pawel Salicki
*/

class StateMachine : public NoCopyNoMove
{
	unsigned int nrOfStates = 0; //number of all states in stack

	bool removeState = false; // is state removed
	bool addState = false; //is state added
	bool pauseState = false; //is state paused

	std::string nameState = "unknown"; //name od state

	std::map<int, std::string> mapState; //map that stores nnumber of state and his name
	std::stack<std::unique_ptr<IStateOfProgram>> state; //stack of states

	std::unique_ptr<IStateOfProgram> uniqPtrState = nullptr; //smart pointer to state

public:
	StateMachine() = default;
	virtual ~StateMachine() = default;

	//add new state to stacl
	void NewState(std::unique_ptr<IStateOfProgram> newState, std::string nameState = "unknown", bool pauseState = false);

	void ChangeState(); //chceck if state is changed
	void PopState(); //pop state from stack
	void DeleteWholeStack(); //remove whole stack

	//getters
	int GetNumberOfState() const;
	std::unique_ptr<IStateOfProgram> & GetStateFromStack();
	std::string GetNameState();
};

#endif // !StateMachine_hpp