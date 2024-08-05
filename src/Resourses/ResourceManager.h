#pragma once

namespace sf {
	class Texture;
}

#include <memory>
#include <map>
#include <string>

class ResourceManager {
	
public:
	ResourceManager(const std::string& pathToExecutable);
	ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	~ResourceManager() = default;


	bool loadTexture(const std::string& textureName, const std::string& path);
	bool loadAllTexturesFromFolder(const std::string& pathToFolder);
	sf::Texture& getTexture(const std::string& textureName);
	std::string getPathToExecutableFolder() const { return m_pathToExecutableFolder; }


private:
	std::string m_pathToExecutableFolder;
	typedef std::map<std::string,sf::Texture> TexturesMap;
	TexturesMap m_textures;

};