#include "StateMachine.h"

void StateMachine::NewState(std::unique_ptr<StateOfProgram> tmp_state, std::string stateName, bool remove)
{
	this->remove = remove;
	this->add = true;
	this->stateName = stateName;
	ptrState = std::move(tmp_state);
}

std::unique_ptr<StateOfProgram> & StateMachine::GetStateFromStack()
{
	try
	{
		return this->state.top();
	}
	catch(...)
	{
		throw std::exception(); //upgrade this catching exception in near future... my eyes are burning 0.o
	}
}

void StateMachine::ChangeState()
{

	if ((remove == true) && !state.empty())
	{
		state.pop();
		remove = false;
		mapState[nrOfStates] = stateName;
		nrOfStates--;
	}
	if (add == true)
	{
		if (!state.empty()) 
		{
			state.pop();
			mapState[nrOfStates] = stateName;
			nrOfStates--;
		}
		state.push(std::move(ptrState));
		state.top()->InitializeObject(); //make this thing working!
		add = false;

		mapState[nrOfStates] = stateName;
		nrOfStates++;
	
		//section for debugging
		std::cout << "--------------" << std::endl;
		for (int i = 0; i < nrOfStates; i++)
		{
			std::cout << "Stack: " << mapState[i].c_str() << std::endl;
		}
		std::cout << nrOfStates << std::endl;
	}
}

void StateMachine::PopState()
{
	this->state.pop();
}

void StateMachine::DeleteStack()
{
	while (!state.empty())
	{
		this->state.pop();
	}
}

int StateMachine::GetNumberOfState() const
{
	return this->nrOfStates;
}

std::string StateMachine::GetStateName()
{
	return this->mapState[nrOfStates].c_str();
}