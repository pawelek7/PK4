#pragma once

class StateOfProgram //virtual functions
{
public:
	virtual void UpdateObject(float elapsedTime) = 0;
	virtual void DrawObject(float elapsedTime) = 0;
	virtual void InitializeObject() = 0;
	virtual void HoldInput() = 0;
	//... anything else?
};