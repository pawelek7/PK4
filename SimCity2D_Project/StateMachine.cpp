#include "StateMachine.h"

#pragma region Class_Methods

#pragma region Description of the method

/*
A method that set new state.

method parameters:
____________________
tmp_state - smart pointer of interface to state
stateName - name of state
pauseState - is state paused

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void StateMachine::NewState(std::unique_ptr<IStateOfProgram> tmp_state, std::string stateName, bool pauseState)
{
	this->addState = true;

	this->pauseState = pauseState;
	this->nameState = stateName;

	this->uniqPtrState = std::move(tmp_state); //move state to smart pointer
}

#pragma region Description of the method

/*
A method that checks if state is going to change
and sets stack of states.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void StateMachine::ChangeState()
{
	if ((this->removeState == true) && !this->state.empty()) //if remove state and stack of states is not empty
	{
		this->state.pop(); //remove state from stack
		this->removeState = false;

		this->mapState[this->nrOfStates] = this->nameState; //update the map of information about state
		this->nrOfStates--;
	}

	if (this->addState == true)
	{
		if (!this->state.empty())
		{
			if (this->pauseState == false)
			{
				this->state.pop(); //remmove state from stackk
				this->mapState[this->nrOfStates] = this->nameState;
				this->nrOfStates--;
			}
		}

		this->state.push(std::move(this->uniqPtrState)); //push new state to stck od states
		this->state.top()->InitializeObject(); //initialize new created object
		this->addState = false;

		this->mapState[this->nrOfStates] = this->nameState; //update map of informations about states
		this->nrOfStates++;

		//section for debugging
		std::cout << "--------------" << std::endl;
		for (int i = 0; i < this->nrOfStates; i++)
		{
			std::cout << "Stack: " << this->mapState[i].c_str() << std::endl;
		}
		std::cout << this->nrOfStates << std::endl;
	}
}

#pragma region Description of the method

/*
A method that remove state from stack.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void StateMachine::PopState()
{
	this->state.pop(); //remove state from stack
	this->mapState[this->nrOfStates] = this->nameState; //update map of informations about states
	this->nrOfStates--;
}

/*
A method that deletes whole stack of states.

method parameters:
____________________
no parameters

the return value:
____________________
no return value

@author
Pawel Salicki
*/

#pragma endregion

void StateMachine::DeleteWholeStack()
{
	while (!this->state.empty()) //while stack of states is not empty, remove state
	{
		this->state.pop();
	}
}

#pragma endregion

#pragma region Getters
//getters

std::unique_ptr<IStateOfProgram> & StateMachine::GetStateFromStack()
{
	return this->state.top();
}

int StateMachine::GetNumberOfState() const
{
	return this->nrOfStates;
}

std::string StateMachine::GetNameState()
{
	return this->mapState[this->nrOfStates].c_str();
}

#pragma endregion