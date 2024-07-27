#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

ResourceManager::ResourceManager(const std::string& pathToExecutable)
{
	size_t index = pathToExecutable.find_last_of("/\\");
	this->m_pathToExecutableFolder = pathToExecutable.substr(0, index);
}

bool ResourceManager::loadTexture(const std::string& textureName,const std::string& path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(m_pathToExecutableFolder + "/" + path)) {
		std::cerr << "Can't load texture " << textureName << "from " << m_pathToExecutableFolder + path;
		return false;
	}

	m_textures.emplace(textureName,texture).first->second;
	return true;
}

bool ResourceManager::loadAllTexturesFromFolder(const std::string& relativePathToFolder) {
	std::string path = this->getPathToExecutableFolder() + "/" + relativePathToFolder;

	if (!fs::exists(path)) {
		std::cerr << "Path " << path << " does not exists!";
		return false;
	}

	bool isLoaded = false;
	for (const auto& entry : fs::directory_iterator(path)) {
		size_t find = entry.path().filename().string().find_last_of(".");
		std::string textureName = entry.path().filename().string().substr(0, find);
		std::string textureFileName = entry.path().filename().string();
		if (!this->loadTexture(textureName, relativePathToFolder + "/" + textureFileName)) {
			std::cerr << "Can't load texture " << relativePathToFolder + "/" + textureFileName << "\n";
			return false;
		}
	}

	return true;
};

sf::Texture ResourceManager::getTexture(const std::string& textureName)  
{
	TexturesMap::iterator it = m_textures.find(textureName);
	return it->second;
}
