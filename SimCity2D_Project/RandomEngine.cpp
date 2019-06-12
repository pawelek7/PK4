#include "RandomEngine.h"

#pragma region Class_Methods

float RandomEngine::RandomiseEvent(int from, int to)
{
	std::default_random_engine engine;
	std::uniform_real_distribution<float> distribution(from, to);

	auto time = std::chrono::system_clock::now();
	auto interwal = time.time_since_epoch();
	engine.seed(interwal.count());

	this->result = distribution(engine);;

	return this->result;
}

#pragma endregion

#pragma region Getters
//getters

float RandomEngine::GetResult() const
{
	return this->result;
}

#pragma endregion