#include "StateMachine.h"

#pragma region Class_Methods

void StateMachine::NewState(std::unique_ptr<StateOfProgram> tmp_state, std::string stateName, bool pauseState)
{
	this->addState = true;

	this->pauseState = pauseState;
	this->nameState = stateName;

	this->uniqPtrState = std::move(tmp_state);
}

void StateMachine::ChangeState()
{
	if ((this->removeState == true) && !this->state.empty())
	{
		this->state.pop();
		this->removeState = false;

		this->mapState[nrOfStates] = this->nameState;
		this->nrOfStates--;
	}

	if (this->addState == true)
	{
		if (!this->state.empty())
		{
			if (this->pauseState == false)
			{
				this->state.pop();
				this->mapState[nrOfStates] = this->nameState;
				this->nrOfStates--;
			}
		}

		this->state.push(std::move(this->uniqPtrState));
		this->state.top()->InitializeObject();
		this->addState = false;

		this->mapState[nrOfStates] = this->nameState;
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

void StateMachine::PopState()
{
	this->state.pop();
	this->mapState[nrOfStates] = this->nameState;
	this->nrOfStates--;
}

void StateMachine::DeleteWholeStack()
{
	while (!this->state.empty())
	{
		this->state.pop();
	}
}

#pragma endregion

#pragma region Getters

std::unique_ptr<StateOfProgram> & StateMachine::GetStateFromStack()
{
	return this->state.top();
}

int StateMachine::GetNumberOfState() const
{
	return this->nrOfStates;
}

std::string StateMachine::GetNameState()
{
	return this->mapState[nrOfStates].c_str();
}

#pragma endregion