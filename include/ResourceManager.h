#pragma once
#include <string>
#include <unordered_map>

namespace sf
{
	class Texture;
	class Font;
}

class ResourceManager
{

public:


	// Public functions
	static sf::Texture & GetTexture(const std::string &filename);
	static sf::Texture & GetErrorTexture( );
	static sf::Font & GetFont( const std::string &filename );
	static bool Initialize( );
	static void Unload( );
	static void ClearAllTextures( );
	static void ClearAllFonts( );

private:
	
	// Typedefs
	typedef std::unordered_map<std::string, sf::Texture*> TextureMap;
	typedef std::unordered_map<std::string, sf::Font*> FontMap;

	// Private functions

	// Private variable members
	static TextureMap s_Textures;
	static sf::Texture * s_pErrorTexture;
	static FontMap s_Fonts;
	static sf::Font * s_pErrorFont;

	// Private constructors and assign operator
	ResourceManager( );
	ResourceManager(const ResourceManager&);
	ResourceManager& operator = (const ResourceManager&);

};