#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "debug.h"

template<class AssetT>
class AssetManager
{
	std::map<std::string, AssetT> asset;
	std::string error_text = "Failed loading asset: ";

public:
	template<typename AssetT>
	friend std::fstream & operator<<(std::ostream & out, const AssetManager<AssetT> & node);

	void LoadAsset(const std::string & asset_id, const std::string & asset_path);
	AssetT & GetAsset(const std::string & asset_id);
};


template <class AssetT>
void AssetManager<AssetT>::LoadAsset(const std::string & asset_id, const std::string & asset_path)
{
	AssetT as_T;

	if (!as_T.loadFromFile(asset_path))
	{
		std::cout << this << asset_id << std::endl;
	}
	else
	{
		this->asset[asset_id] = as_T;
	}
}

template<class AssetT>
AssetT & AssetManager<AssetT>::GetAsset(const std::string & asset_id)
{
	DEBUG_IF(asset.find(asset_id) == asset.end(), asset_id << " is an invalid asset path.\n");

	return this->asset.at(asset_id);
}

template <class AssetT>
inline std::ostream & operator<<(std::ostream & os, const AssetManager<AssetT> & n)
{
	return os << n.error_text;
}

#endif // !AssetManager_hpp