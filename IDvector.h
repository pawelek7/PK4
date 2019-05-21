#ifndef IDvector_hpp
#define IDvector_hpp

#include <limits>
#include <vector>

typedef std::size_t ID;
constexpr ID UNDEFINED = std::numeric_limits<ID>::max();

template<class T>
class IDvector
{
	std::vector<ID> IDsToIndex;
	std::vector<ID> unusedIDs;
	std::vector<T> objectsWithIDs;
	std::vector<ID> indexToIDs;

public:
	IDvector() = default;
	virtual ~IDvector() = default;

	ID push(T t);
	void PopID(ID id);

	inline void JustPushID(ID id)
	{
		this->IDsToIndex.push_back(id);
	}

	inline bool isIdExists(ID id)
	{
		return (id < this->IDsToIndex.size() && this->IDsToIndex[id] != UNDEFINED);
	}

	inline T& GetElement(ID id)
	{
		return this->objectsWithIDs[IDsToIndex[id]];
	}
	
	inline const T& GetElement(ID id) const
	{
		return this->objectsWithIDs[IDsToIndex[id]];
	}

	inline const std::vector<T>&getObjects() const
	{
		return this->objectsWithIDs;
	}

	inline std::vector<T>&getObjects()
	{
		return this->objectsWithIDs;
	}

	inline std::size_t GetSize() const
	{
		return this->objectsWithIDs.size();
	}
};

template<class T>
ID IDvector<T>::push(T t)
{
	std::size_t tmpSize = this->objectsWithIDs.size();
	this->objectsWithIDs.push_back(std::move(t));

	ID id;

	if (this->unusedIDs.empty())
	{
		id = this->IDsToIndex.size();
		this->IDsToIndex.push_back(tmpSize);
	}
	else
	{
		id = this->unusedIDs.back();
		this->unusedIDs.pop_back();
		this->IDsToIndex[id] = tmpSize;
	}

	this->indexToIDs.push_back(id);

	return id;
}

template<class T>
void IDvector<T>::PopID(ID id)
{
	std::size_t sizeTmp = this->IDsToIndex[id];

	this->objectsWithIDs[sizeTmp] = std::move(this->objectsWithIDs.back());
	ID lastObjectID = this->indexToIDs.back();
	this->IDsToIndex[lastObjectID] = sizeTmp;
	this->indexToIDs[sizeTmp] = lastObjectID;

	this->objectsWithIDs.pop_back();
	this->indexToIDs.pop_back();

	this->IDsToIndex[id] = UNDEFINED;
	this->unusedIDs.push_back(id);
}

#endif // !IDvector