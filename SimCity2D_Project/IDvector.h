#ifndef IDvector_hpp
#define IDvector_hpp

#include <limits>
#include <vector>

/*
A class template that supports operations 
on a vector and makes sure that object IDs are created in a unique way.

@author
Pawel Salicki
*/

typedef std::size_t ID;
constexpr ID UNDEFINED = std::numeric_limits<ID>::max(); //ID as max value as default

template<class T>
class IDvector 
{
	std::vector<ID> IDsToIndex; //canvert ID to index
	std::vector<ID> unusedIDs; //IDs that are unsused
	std::vector<T> objectsWithIDs; //objects that have ID
	std::vector<ID> indexToIDs; //convert index to ID

public:
	IDvector() = default;
	virtual ~IDvector() = default;

	ID Push(T t); //push object to vector and return his ID
	void PopID(ID id); //pop ID

	//getters, setters and simple methods

#pragma region Getters, setters and simple methods

	inline void JustPushID(ID id) //push only ID to vector
	{
		this->IDsToIndex.push_back(id);
	}

	inline void JustPushObject(T t)
	{
		this->objectsWithIDs.push_back(t);
	}

	inline bool isIdExists(ID id) //check if ID is already exist
	{
		return (id < this->IDsToIndex.size() && this->IDsToIndex[id] != UNDEFINED);
	}

	inline T & GetElement(ID id) //get id's element
	{
		return this->objectsWithIDs[this->IDsToIndex[id]];
	}
	
	inline const T& GetElement(ID id) const //get id's element as const
	{
		return this->objectsWithIDs[this->IDsToIndex[id]];
	}

	inline const std::vector<T>&GetObjects() const //get vector of objects with IDs as const
	{
		return this->objectsWithIDs;
	}

	inline std::vector<T>&GetObjects() //get vector of objects with IDs
	{
		return this->objectsWithIDs;
	}

	inline std::size_t GetSize() const //get size of vector of objects with IDs
	{
		return this->objectsWithIDs.size();
	}

	inline std::vector<ID> & GetIdsToIndex()
	{
		return this->IDsToIndex;
	}

	inline std::vector<ID> & GetUnusedIDs()
	{
		return this->unusedIDs;
	}

	inline std::vector<T> & GetObjectsWithIDs()
	{
		return this->objectsWithIDs;
	}

	inline std::vector<ID> & GetIndexToIDs()
	{
		return this->indexToIDs;
	}


#pragma endregion
};

#pragma region Description of the method

/*
A method that pushes object To vector
and set unique ID of it.

method parameters:
____________________
t - object T <template>

the return value:
____________________
id - return created ID of object as integer variable

@author
Pawel Salicki
*/

#pragma endregion

template<class T>
ID IDvector<T>::Push(T t)
{
	std::size_t tmpSize = this->objectsWithIDs.size();
	this->objectsWithIDs.push_back(std::move(t)); //push object to vector

	ID id;

	if (this->unusedIDs.empty()) //if there is't unused ID create the new one
	{
		id = this->IDsToIndex.size();
		this->IDsToIndex.push_back(tmpSize);
	}
	else
	{
		id = this->unusedIDs.back(); //set unused ID to object
		this->unusedIDs.pop_back();
		this->IDsToIndex[id] = tmpSize;
	}

	this->indexToIDs.push_back(id); //push ID to vector of IDs

	return id; //return id of pushed object
}

/*
A methid that deletes object from vector
basing on his ID.

method parameters:
____________________
id - id of object as Integer

the return value:
____________________
no return value

@author
Pawel Salicki
*/

template<class T>
void IDvector<T>::PopID(ID id)
{
	try {
		std::size_t sizeTmp = this->IDsToIndex.at(id);

		this->objectsWithIDs.at(sizeTmp) = std::move(this->objectsWithIDs.back()); //prepare to remove object
		ID lastObjectID = this->indexToIDs.back();
		this->IDsToIndex.at(lastObjectID) = sizeTmp;
		this->indexToIDs.at(sizeTmp) = lastObjectID;

		this->objectsWithIDs.pop_back(); //remove object from vector
		this->indexToIDs.pop_back();

		this->IDsToIndex.at(id) = UNDEFINED;
		this->unusedIDs.push_back(id); //push unused ID to vector
	}
	catch (const std::out_of_range & e)
	{
		std::cout<<e.what() << std::endl;
	}
}

#endif // !IDvector