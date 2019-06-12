#ifndef Tornado_hpp
#define Tornado_hpp

#include "MovableDisaster.h"

/*
The tornado class inherits from the Disaster class in public.
It supports a fire disaster.

@author
Pawel Salicki
*/

class Tornado : public MovableDisaster
{
public:
	Tornado() = default; //non-parametric constructor
	Tornado(const sf::Texture & texture, const std::vector<Frames> & frames); //multi-parameter constructor
	virtual ~Tornado() = default; //destructor

	virtual void UpdateTornado(const float elapsedTime); //update disaster

	void ThornadoIntelligence(const float elapsedTime); //tornado behaviour
	void InitializeTornado(); //start tornado event
};

#endif // !Tornado_hpp