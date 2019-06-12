#ifndef  PathFinding_hpp
#define PathFinding_hpp

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <stack>
#include <set>
#include <string>

class PathFinding
{
	struct cell
	{
		int parent_i, parent_j;
		double f, g, h;
	};

	int sizeMap = 0;
	std::vector<bool> connection;
	std::stack<std::pair<int, int>> path;
	std::vector<sf::Vector2i> pathAsVector;
	std::vector<sf::Vector2i> drivingPath;
	std::vector<sf::Vector2i> returnPath;

	std::vector<cell> cellDetails;
	std::vector<bool> closedList;
	std::pair<int, int>destination;

	bool rememverDrive = false;
	bool rememberReturn = false;

	double calculateHValue(int i, int j, std::pair<int, int> & destination);

	bool isValid(int i, int j);
	bool isUnBlocked(int i, int j);
	bool isDestination(int i, int j, std::pair<int, int> & destination);

public:
	PathFinding() = default;
	PathFinding(int sizeMap);
	virtual ~PathFinding() = default;

	bool aStarSearch(std::pair<int, int> & start, std::pair<int, int> & end);
	std::vector<sf::Vector2i> tracePath();

	std::vector<sf::Vector2i> GetDrivingPath()
	{
		return this->drivingPath;
	}

	std::vector<sf::Vector2i> GetReturnPath()
	{
		return this->returnPath;
	}

	void ForgetPaths()
	{
		this->returnPath.clear();
		this->drivingPath.clear();
		this->rememverDrive = false;
		this->rememberReturn = false;
	}

	void AddConnection(int i, int j);
	void RemoveConnection(int i, int j);

	std::vector<bool> & GetConnection();
	void SetConnection(std::vector<bool> & connection);

	inline std::stack<std::pair<int, int>> GetPath()
	{
		return this->path;
	}
};

#endif // ! PathFinding_hpp