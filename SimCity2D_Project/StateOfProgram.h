#ifndef StateOfProgram_hpp
#define StateOfProgram_hpp

/*
Interface - Strategy

@author
Pawel Salicki
*/

class IStateOfProgram
{
public:
	virtual void UpdateObject(const float elapsedTime) = 0; //update object
	virtual void DrawObject(const float elapsedTime) = 0; //draw object
	virtual void InitializeObject() = 0; //initialize assets of object
	virtual void HoldInput() = 0; //hold keyboard and mouse input
};

#endif // !StateOfProgram_hpp