#ifndef VectorManager_hpp
#define VectorManager_hpp

#include <vector>

#include "NoCopyNoMove.h"

/*
A class template that supports operations
on a vector as 2D array.

@author
Pawel Salicki
*/


template <class Tvector>
class VectorManager : public NoCopyNoMove
{
	int height = 0, width = 0; //size x, size y
	std::vector<Tvector> elements; //vector of elements

public:
	VectorManager(int height = 0, int width = 0);
	VectorManager(int height, int width, const Tvector & elements);
	virtual ~VectorManager() = default;

	//add element to vector on x, y position
	inline void AddElements(int x, int y, Tvector element)
	{
		this->elements[x*this->height + y] = std::move(element);
	}

	//erase element on x, y position
	inline void EraseElement(int x, int y)
	{
		this->elements.erase(this->elements.begin() + (x*this->height + y));
	}

	//resize vector (array 2D)
	inline void ReshapeVector(int height, int width)
	{
		this->height = height;
		this->width = width;

		this->elements.resize(height*width);
	}

	//resize vector (array 2D) and put default value
	inline void ReshapeVectorWithDefaultElement(int height, int width, const Tvector & element)
	{
		this->height = height;
		this->width = width;

		this->elements.resize(height * width, element);
	}

	//getters
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
		return this->elements[x * this->height + y];
	}
};

//constructors
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