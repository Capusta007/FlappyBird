#include "ResourceManager.h"

#include <SFML/Graphics.hpp>

#include <iostream>

ResourceManager::ResourceManager(const std::string pathToExecutable)
{
	size_t index = pathToExecutable.find_last_of("/\\");
	this->m_path = pathToExecutable.substr(0, index);
}

bool ResourceManager::loadTexture(const std::string textureName,const std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(m_path + "/" + path)) {
		std::cerr << "Can't load texture " << textureName << "from " << m_path + path;
		return false;
	}

	m_textures.emplace(textureName,texture).first->second;
	return true;
}

sf::Texture ResourceManager::getTexture(const std::string textureName)
{
	TexturesMap::iterator it = m_textures.find(textureName);
	return it->second;
}
