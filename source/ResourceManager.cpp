#include <ResourceManager.h>
#include <iostream>
/*
sf::Texture& ResourceManager::GetTexture(const std::string &filename)
{
	TextureMap::iterator & it = mTextureMap.find( filename );

	return *(it->second);
}

bool ResourceManager::LoadTextures( const std::string &filename ) 
{
	TextureMap::iterator it = mTextureMap.find( filename );

	if( it != mTextureMap.end( ) )
	{
		return true;
	}

	sf::Texture * texture = new sf::Texture;
	if(texture->loadFromFile( filename ) == false)
	{
		std::cout << "[ResourceManager.cpp]Failed to load sound file." << std::endl;
		delete texture;
		return false;
	}
	std::cout << "ok: " << filename << std::endl;
	mTextureMap[filename] = texture;
	return true;
}

*/
