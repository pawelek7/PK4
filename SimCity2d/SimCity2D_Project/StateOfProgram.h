#pragma once

class StateOfProgram //virtual functions
{
public:
	virtual void UpdateObject(float elapsedTime) = 0;
	virtual void DrawObject() = 0;
	virtual void InitializeObject() = 0;
	//... anything else?
};