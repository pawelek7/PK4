#include "PathFinding.h"

#pragma region Constructors

PathFinding::PathFinding(int sizeMap)
{
	this->sizeMap = sizeMap;

	connection.resize(sizeMap*sizeMap, false);
	closedList.resize(sizeMap*sizeMap, false);
}

#pragma endregion

#pragma region Class_Methods

bool PathFinding::isValid(int i, int j)
{
	return (i >= 0 && i < sizeMap && j >= 0 && j < sizeMap);
}

bool PathFinding::isUnBlocked(int i, int j)
{
	return connection[i*sizeMap + j];
}

bool PathFinding::isDestination(int i, int j, std::pair<int, int> & destination)
{
	if (i == destination.first && j == destination.second)
		return true;

	return false;
}

double PathFinding::calculateHValue(int i, int j, std::pair<int, int> & destination)
{
	return ((double)sqrt((i - destination.first)*(i - destination.first) + (j - destination.second)*(j - destination.second)));
}

std::vector<sf::Vector2i> PathFinding::tracePath()
{
	int i = destination.first;
	int j = destination.second;

	while (!(cellDetails[i * sizeMap + j].parent_i == i
		&& cellDetails[i*sizeMap + j].parent_j == j))
	{
		path.push(std::pair<int, int>(i, j));

		sf::Vector2i position;
		position.x = (j - i) * 32 + sizeMap * 32 + 32;
		position.y = (j + i) * 32 * 0.5f + 16;

		pathAsVector.push_back(position);

		if (rememverDrive == false)
		{
			this->drivingPath.push_back(position);
		}
		else if (rememberReturn == false)
		{
			this->returnPath.push_back(position);
		}

		int tmp_i = cellDetails[i*sizeMap + j].parent_i;
		int tmp_j = cellDetails[i*sizeMap + j].parent_j;
		i = tmp_i;
		j = tmp_j;
	}

	path.push(std::pair<int, int>(i, j));

	sf::Vector2i position;
	position.x = (j - i) * 32 + sizeMap * 32;
	position.y = (j + i) * 32 * 0.5f;

	pathAsVector.push_back(position);

	if (rememverDrive == false)
	{
		this->drivingPath.push_back(position);
		this->rememverDrive = true;
	}
	else if (rememberReturn == false)
	{
		this->returnPath.push_back(position);
		this->rememberReturn = true;
	}

	cellDetails.clear();

	i = 0;
	j = 0;

	return pathAsVector;
}

bool PathFinding::aStarSearch(std::pair<int, int> & start, std::pair<int, int> & end)
{
	if (this->isValid(start.first, start.second) == false)
	{
		return false;
	}

	if (this->isValid(end.first, end.second) == false)
	{
		return false;
	}

	if (this->isUnBlocked(start.first, start.second) == false ||
		this->isUnBlocked(end.first, end.second) == false)
	{
		return false;
	}

	if (this->isDestination(start.first, start.second, end) == true)
	{
		return false;
	}

	cellDetails.clear();
	cellDetails.resize(sizeMap*sizeMap);
	pathAsVector.clear();
	closedList.clear();
	closedList.resize(sizeMap * sizeMap);

	int i, j;

	for (i = 0; i < this->sizeMap; i++)
	{
		for (j = 0; j < this->sizeMap; j++)
		{
			cellDetails[i*sizeMap + j].f = FLT_MAX;
			cellDetails[i*sizeMap + j].g = FLT_MAX;
			cellDetails[i*sizeMap + j].h = FLT_MAX;
			cellDetails[i*sizeMap + j].parent_i = -1;
			cellDetails[i*sizeMap + j].parent_j = -1;
		}
	}

	this->destination = end; //...

	i = start.first, j = start.second;
	cellDetails[i*sizeMap + j].f = 0.0f;
	cellDetails[i*sizeMap + j].g = 0.0f;
	cellDetails[i*sizeMap + j].h = 0.0f;
	cellDetails[i*sizeMap + j].parent_i = i;
	cellDetails[i*sizeMap + j].parent_j = j;

	std::set<std::pair<double, std::pair<int, int>>> openList;

	openList.insert(std::make_pair(0.0f, std::pair<int, int>(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		std::pair<double, std::pair<int, int>> p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i*sizeMap + j] = true;

		double gNew, hNew, fNew;

		if (this->isValid(i - 1, j) == true)
		{
			if (this->isDestination(i - 1, j, end) == true)
			{
				cellDetails[(i - 1) * sizeMap + j].parent_i = i;
				cellDetails[(i - 1) * sizeMap + j].parent_j = j;

				foundDest = true;
				return foundDest;
			}
			else if (closedList[(i - 1)*sizeMap + j] == false &&
				this->isUnBlocked(i - 1, j) == true)
			{
				gNew = cellDetails[i*sizeMap + j].g + 1.0f;
				hNew = calculateHValue(i - 1, j, end);
				fNew = gNew + hNew;

				if (cellDetails[(i - 1)*sizeMap + j].f == FLT_MAX ||
					cellDetails[(i - 1) * sizeMap + j].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::pair<int, int>(i - 1, j)));

					cellDetails[(i - 1)*sizeMap + j].f = fNew;
					cellDetails[(i - 1)*sizeMap + j].g = gNew;
					cellDetails[(i - 1)*sizeMap + j].h = hNew;
					cellDetails[(i - 1)*sizeMap + j].parent_i = i;
					cellDetails[(i - 1)*sizeMap + j].parent_j = j;
				}
			}
		}

		if (this->isValid(i + 1, j) == true)
		{
			if (this->isDestination(i + 1, j, end) == true)
			{
				cellDetails[(i + 1)*sizeMap + j].parent_i = i;
				cellDetails[(i + 1)*sizeMap + j].parent_j = j;

				foundDest = true;
				return foundDest;
			}
			else if (closedList[(i + 1)*sizeMap + j] == false
				&& this->isUnBlocked(i + 1, j) == true)
			{
				gNew = cellDetails[i*sizeMap + j].g + 1.0f;
				hNew = this->calculateHValue(i + 1, j, end);
				fNew = gNew + hNew;


				if (cellDetails[(i + 1)*sizeMap + j].f == FLT_MAX ||
					cellDetails[(i + 1)*sizeMap + j].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::pair<int, int>(i + 1, j)));

					cellDetails[(i + 1)*sizeMap + j].f = fNew;
					cellDetails[(i + 1)*sizeMap + j].g = gNew;
					cellDetails[(i + 1)*sizeMap + j].h = hNew;
					cellDetails[(i + 1)*sizeMap + j].parent_i = i;
					cellDetails[(i + 1)*sizeMap + j].parent_j = j;
				}
			}
		}

		if (this->isValid(i, j + 1) == true)
		{
			if (this->isDestination(i, j + 1, end) == true)
			{
				cellDetails[i * sizeMap + (j + 1)].parent_i = i;
				cellDetails[i*sizeMap + (j + 1)].parent_j = j;

				foundDest = true;
				return foundDest;
			}
			else if (closedList[i*sizeMap + (j + 1)] == false &&
				this->isUnBlocked(i, j + 1) == true)
			{
				gNew = cellDetails[i*sizeMap + j].g + 1.0f;
				hNew = calculateHValue(i, j + 1, end);
				fNew = gNew + hNew;

				if (cellDetails[i*sizeMap + (j + 1)].f == FLT_MAX ||
					cellDetails[i*sizeMap + (j + 1)].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::pair<int, int>(i, j + 1)));

					cellDetails[i*sizeMap + (j + 1)].f = fNew;
					cellDetails[i*sizeMap + (j + 1)].g = gNew;
					cellDetails[i*sizeMap + (j + 1)].h = hNew;
					cellDetails[i*sizeMap + (j + 1)].parent_i = i;
					cellDetails[i*sizeMap + (j + 1)].parent_j = j;
				}
			}
		}

		if (this->isValid(i, j - 1) == true)
		{
			if (this->isDestination(i, j - 1, end) == true)
			{
				cellDetails[i * sizeMap + (j - 1)].parent_i = i;
				cellDetails[i*sizeMap + (j - 1)].parent_j = j;

				foundDest = true;
				return foundDest;
			}
			else if (closedList[i*sizeMap + (j - 1)] == false &&
				this->isUnBlocked(i, j - 1) == true)
			{
				gNew = cellDetails[i*sizeMap + j].g + 1.0f;
				hNew = calculateHValue(i, j - 1, end);
				fNew = gNew + hNew;

				if (cellDetails[i*sizeMap + (j - 1)].f == FLT_MAX ||
					cellDetails[i*sizeMap + (j - 1)].f > fNew)
				{
					openList.insert(std::make_pair(fNew, std::pair<int, int>(i, j - 1)));

					cellDetails[i*sizeMap + (j - 1)].f = fNew;
					cellDetails[i*sizeMap + (j - 1)].g = gNew;
					cellDetails[i*sizeMap + (j - 1)].h = hNew;
					cellDetails[i*sizeMap + (j - 1)].parent_i = i;
					cellDetails[i*sizeMap + (j - 1)].parent_j = j;
				}
			}
		}
	}
	if (foundDest == false)
	{
		i = 0;
		j = 0;
	}

	return foundDest;
}

void PathFinding::AddConnection(int i, int j)
{
	if (i > sizeMap || i < 0 || j > sizeMap || j < 0)
		return;

	connection[i * sizeMap + j] = std::move(true);
}

void PathFinding::RemoveConnection(int i, int j)
{
	if (i > sizeMap || i < 0 || j > sizeMap || j < 0)
		return;

	connection[i*sizeMap + j] = std::move(false);
}

std::vector<bool> & PathFinding::GetConnection()
{
	return this->connection;
}

void PathFinding::SetConnection(std::vector<bool> & connection)
{
	this->connection = connection;
}


#pragma endregion