#ifndef PerlinNoise_hpp
#define PerlinNoise_hpp

# include <cstdint>
# include <numeric>
# include <algorithm>
# include <random>

class PerlinNoise
{
	uint64_t p[512];
	static double Fade(double t) noexcept;
	static double Lerp(double t, double a, double b) noexcept;
	static double Grad(uint64_t hash, double x, double y, double z) noexcept;

public:
	explicit PerlinNoise(uint64_t seed = std::default_random_engine::default_seed);
	virtual ~PerlinNoise() = default;

	void reseed(uint64_t seed);
	double noise(double x) const;
	double noise(double x, double y) const;
	double noise(double x, double y, double z) const;
	double octaveNoise(double x, std::int32_t octaves) const;
	double octaveNoise(double x, double y, std::int32_t octaves) const;
	double octaveNoise(double x, double y, double z, std::int32_t octaves) const;
	double noise0_1(double x) const;
	double noise0_1(double x, double y) const;
	double noise0_1(double x, double y, double z) const;
	double octaveNoise0_1(double x, std::int32_t octaves) const;
	double octaveNoise0_1(double x, double y, std::int32_t octaves) const;
	double octaveNoise0_1(double x, double y, double z, std::int32_t octaves) const;

	template <class URNG>
	explicit PerlinNoise(URNG& urng)
	{
		reseed(urng);
	}

	template <class URNG>
	void reseed(URNG& urng)
	{
		for (int i = 0; i < 256; ++i)
		{
			p[i] = i;
		}

		std::shuffle(std::begin(p), std::begin(p) + 256, urng);

		for (int i = 0; i < 256; ++i)
		{
			p[256 + i] = p[i];
		}
	}
};

#endif // !PerlinNoise_hpp