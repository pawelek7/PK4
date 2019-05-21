#ifndef VectorManager_hpp
#define VectorManager_hpp

#include <vector>

template <class Tvector>
class VectorManager
{
	int height = 0, width = 0;
	std::vector<Tvector> elements;

public:
	VectorManager(int height = 0, int width = 0);
	VectorManager(int height, int width, const Tvector& elements);

	inline void AddElements(int x, int y, Tvector element)
	{
		this->elements[x*height + y] = std::move(element);
	}

	inline void EraseElement(int x, int y)
	{
		this->elements.erase(elements.begin() + (x*height + y));
	}

	inline void ReshapeVector(int height, int width)
	{
		this->height = height;
		this->width = width;
		
		this->elements.resize(height*width);
	}

	inline void ReshapeVectorWithDefaultElement(int height, int width, const Tvector & element)
	{
		this->height = height;
		this->width = width;

		this->elements.resize(height * width, element);
	}

	inline int GetVectorSize() const
	{
		return this->elements.size();
	}

	inline int GetHeight() const
	{
		return this->height;
	}

	inline int GetWidth() const
	{
		return this->width;
	}

	inline std::vector<Tvector> & GetVector()
	{
		return this->elements;
	}

	inline Tvector & GetElements(int x, int y)
	{
		return this->elements[x * height + y];
	}
};

template<class Tvector>
VectorManager<Tvector>::VectorManager(int height, int width)
	:height(height), width(width)
{
	this->ReshapeVector(height, width);
}

template<class Tvector>
VectorManager<Tvector>::VectorManager(int height, int width, const Tvector& elements)
	:height(height), width(width)
{
	this->ReshapeVectorWithDefaultElement(height, width, elements);
}

#endif // !VectorManager_hpp
