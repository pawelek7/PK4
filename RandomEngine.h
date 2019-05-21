#ifndef RandomEngine_hpp
#define RandomEngine_hpp

#include <chrono>
#include <random>

class RandomEngine
{
public:
	RandomEngine() = default;

	float RandomiseEvent(int from, int to);
};


#endif // !RandomEngine
