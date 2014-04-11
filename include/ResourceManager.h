#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>

class ResourceManager
{

public:


	// Public functions
	static sf::Texture & GetTexture(const std::string &filename);
	static sf::Texture & GetErrorTexture( );
	static bool Initialize( );
	static void Unload( );
	static void ClearAllTextures( );

private:
	
	// Typedefs
	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;

	// Private functions

	// Private variable members
	static TextureMap s_Textures;
	static sf::Texture * s_pErrorTexture;

	// Private constructors and assign operator
	ResourceManager( );
	ResourceManager(const ResourceManager&);
	ResourceManager& operator = (const ResourceManager&);

};