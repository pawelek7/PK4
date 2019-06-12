#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "debug.h"

/*
AssetManager class template. 
The class reads the SFML library assets from the file.

@author
Pawel Salicki
*/

template<class AssetT>
class AssetManager
{
	std::map<std::string, AssetT> asset; //container that stores the path and asset
	std::string error_text = "Failed loading asset: ";

public:
	//Streaming operator writing error information on the console.
	template<typename AssetT>
	friend std::fstream & operator<<(std::ostream & out, const AssetManager<AssetT> & node); 

	//A method that puts the graphic asset into the container of assets.
	void LoadAsset(const std::string & asset_id, const std::string & asset_path);

	//A method that returns graphic asset.
	AssetT & GetAsset(const std::string & asset_id);
};


template <class AssetT>
void AssetManager<AssetT>::LoadAsset(const std::string & asset_id, const std::string & asset_path)
{
	if (asset.find(asset_id) != asset.end())
		return;

	AssetT as_T;

	if (!as_T.loadFromFile(asset_path)) //read asset from file
	{
		std::cout << this << asset_id << std::endl; //error message
	}
	else
	{
		this->asset[asset_id] = as_T; //put asset into container of assets
	}
}

template<class AssetT>
AssetT & AssetManager<AssetT>::GetAsset(const std::string & asset_id)
{
	DEBUG_IF(asset.find(asset_id) == asset.end(), asset_id << " is an invalid asset path.\n"); //error message

	return this->asset.at(asset_id); //get asset from container of assets
}

template <class AssetT>
inline std::ostream & operator<<(std::ostream & os, const AssetManager<AssetT> & n)
{
	return os << n.error_text; //print error message
}

#endif // !AssetManager_hpp