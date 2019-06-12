#include "PerlinNoise.h"

#pragma region Constructors

PerlinNoise::PerlinNoise(uint64_t seed)
{
	reseed(seed);
}

#pragma endregion

#pragma region Class_Methods

double PerlinNoise::Fade(double t) noexcept
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::Lerp(double t, double a, double b) noexcept
{
	return a + t * (b - a);
}

double PerlinNoise::Grad(uint64_t hash, double x, double y, double z) noexcept
{
	const uint64_t h = hash & 15;
	const double u = h < 8 ? x : y;
	const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

void PerlinNoise::reseed(uint64_t seed)
{
	for (int i = 0; i < 256; ++i)
	{
		p[i] = i;
	}

	std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(seed));

	for (int i = 0; i < 256; ++i)
	{
		p[256 + i] = p[i];
	}
}

double PerlinNoise::noise(double x) const
{
	return noise(x, 0.0, 0.0);
}

double PerlinNoise::noise(double x, double y) const
{
	return noise(x, y, 0.0);
}

double PerlinNoise::noise(double x, double y, double z) const
{
	const std::int64_t X = static_cast<std::int64_t>(std::floor(x)) & 255;
	const std::int64_t Y = static_cast<std::int64_t>(std::floor(y)) & 255;
	const std::int64_t Z = static_cast<std::int64_t>(std::floor(z)) & 255;

	x -= std::floor(x);
	y -= std::floor(y);
	z -= std::floor(z);

	const double u = Fade(x);
	const double v = Fade(y);
	const double w = Fade(z);

	const uint64_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
	const uint64_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z),
		Grad(p[BA], x - 1, y, z)),
		Lerp(u, Grad(p[AB], x, y - 1, z),
			Grad(p[BB], x - 1, y - 1, z))),
		Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),
			Grad(p[BA + 1], x - 1, y, z - 1)),
			Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1),
				Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double PerlinNoise::octaveNoise(double x, std::int32_t octaves) const
{
	double result = 0.0;
	double amp = 1.0;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise(x) * amp;
		x *= 2.0;
		amp *= 0.5;
	}

	return result;
}

double PerlinNoise::octaveNoise(double x, double y, std::int32_t octaves) const
{
	double result = 0.0;
	double amp = 1.0;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise(x, y) * amp;
		x *= 2.0;
		y *= 2.0;
		amp *= 0.5;
	}

	return result;
}

double PerlinNoise::octaveNoise(double x, double y, double z, std::int32_t octaves) const
{
	double result = 0.0;
	double amp = 1.0;

	for (int i = 0; i < octaves; ++i)
	{
		result += noise(x, y, z) * amp;
		x *= 2.0;
		y *= 2.0;
		z *= 2.0;
		amp *= 0.5;
	}

	return result;
}

double PerlinNoise::noise0_1(double x) const
{
	return noise(x) * 0.5 + 0.5;
}

double PerlinNoise::noise0_1(double x, double y) const
{
	return noise(x, y) * 0.5 + 0.5;
}

double PerlinNoise::noise0_1(double x, double y, double z) const
{
	return noise(x, y, z) * 0.5 + 0.5;
}

double PerlinNoise::octaveNoise0_1(double x, std::int32_t octaves) const
{
	return octaveNoise(x, octaves) * 0.5 + 0.5;
}

double PerlinNoise::octaveNoise0_1(double x, double y, std::int32_t octaves) const
{
	return octaveNoise(x, y, octaves) * 0.5 + 0.5;
}

double PerlinNoise::octaveNoise0_1(double x, double y, double z, std::int32_t octaves) const
{
	return octaveNoise(x, y, z, octaves) * 0.5 + 0.5;
}

#pragma endregion