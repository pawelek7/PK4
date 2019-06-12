#include "SeedGenerator.h"

#pragma region Constructors

SeedGenerator::SeedGenerator(uint64_t seed) : seed(seed)
{
	this->generator = (std::mt19937_64)seed;
}

#pragma endregion

#pragma region Operators

uint64_t SeedGenerator::operator()()
{
	return this->generator();
}

#pragma endregion

#pragma region Setters
//setters

void SeedGenerator::SetSeed(uint64_t seed)
{
	this->seed = seed;
	this->generator.seed(0);
}

#pragma endregion

#pragma region Getters
//getters

uint64_t SeedGenerator::GetMin() const
{
	return std::mt19937::min();
}

uint64_t SeedGenerator::GetMax() const
{
	return std::mt19937::max();
}

uint64_t SeedGenerator::GetSeed() const
{
	return this->seed;
}

#pragma endregion