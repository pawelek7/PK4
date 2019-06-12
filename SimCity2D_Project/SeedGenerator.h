#ifndef NoiseGenerator_hpp
#define NoiseGenerator_hpp

#include <chrono>
#include <random>

class SeedGenerator
{
	uint64_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937_64 generator;

public:
	SeedGenerator(uint64_t seed = 0);
	virtual ~SeedGenerator() = default;

	uint64_t operator()();

	//setters
	void SetSeed(uint64_t seed);

	//getters
	uint64_t GetSeed() const;
	uint64_t GetMin() const;
	uint64_t GetMax() const;
};

#endif // !NoiseGenerator_hpp