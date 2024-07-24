#pragma once

namespace sf {
	class Texture;
}

#include <memory>
#include <map>
#include <string>

class ResourceManager {
	
public:
	ResourceManager(const std::string pathToExecutable);
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	~ResourceManager() = default;


	bool loadTexture(const std::string textureName, const std::string path);
	sf::Texture getTexture(const std::string textureName);


private:
	std::string m_path;

	typedef std::map<std::string,sf::Texture> TexturesMap;
	TexturesMap m_textures;

};