#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	static sf::Texture& GetTexture(const std::string &filename);
	static bool LoadTextures(const std::string &filename);

	static bool Load();
	static void Unload();

private:
	ResourceManager();
	
//	static bool LoadTextures(const std::string &filename);	
	
	static void UnloadTextures();

	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;
	static TextureMap mTextureMap;

	ResourceManager(const ResourceManager&);
	ResourceManager& operator = (const ResourceManager&);
};
