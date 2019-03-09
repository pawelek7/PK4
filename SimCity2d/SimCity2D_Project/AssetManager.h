#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

template <class AssetT>
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
void AssetManager<AssetT>::LoadAsset(const std::string& asset_id, const std::string& asset_path)
{
	AssetT as_T;

	if (!as_T.loadFromFile(asset_path))
	{
		std::cerr << this << asset_id << std::endl;
	}
	else
	{
		this->asset[asset_id] = as_T;
	}
}

template<class AssetT>
AssetT & AssetManager<AssetT>::GetAsset(const std::string & asset_id)
{
	return this->asset.at(asset_id);
}

template <class AssetT>
inline std::ostream& operator<<(std::ostream & os, const AssetManager<AssetT> & n)
{
	return os << n.error_text;
}
