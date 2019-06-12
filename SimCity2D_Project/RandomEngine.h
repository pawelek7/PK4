#ifndef RandomEngine_hpp
#define RandomEngine_hpp

#include <chrono>
#include <random>

class RandomEngine
{
	float result = 0.0f;

public:
	RandomEngine() = default;
	virtual ~RandomEngine() = default;

	float RandomiseEvent(int from, int to);

	//getters
	float GetResult() const;
};


#endif // !RandomEngine