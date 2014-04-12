#include <ResourceManager.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <MemoryLeak.h>

ResourceManager::TextureMap ResourceManager::s_Textures;
sf::Texture * ResourceManager::s_pErrorTexture = NULL;
ResourceManager::FontMap ResourceManager::s_Fonts;
sf::Font * ResourceManager::s_pErrorFont = NULL;

sf::Texture & ResourceManager::GetTexture(const std::string &filename)
{
	// Find the texture
	TextureMap::iterator it = s_Textures.find( filename );

	// Found the texture
	if( it != s_Textures.end( ) )
	{
		return *(it->second);
	}

	// Create a new texture
	sf::Texture * pTexture = new sf::Texture;
	if( pTexture->loadFromFile( filename ) == false)
	{
		std::cout << "[ResourceManager::GetTexture] Can not load the texture." << std::endl;
		return *s_pErrorTexture;
	}

	// Add and return the texture
	s_Textures[filename] = pTexture;
	return *pTexture;
}

sf::Texture & ResourceManager::GetErrorTexture( )
{
	return *s_pErrorTexture;
}

sf::Font & ResourceManager::GetFont( const std::string &filename )
{
	// Find the font
	FontMap::iterator it = s_Fonts.find( filename );

	// Found the font
	if( it != s_Fonts.end( ) )
	{
		return *(it->second);
	}

	// Create a new font
	sf::Font * pFont = new sf::Font;
	if( pFont->loadFromFile( filename ) == false)
	{
		std::cout << "[ResourceManager::GetTexture] Can not load the texture." << std::endl;
		return *s_pErrorFont;
	}

	// Add and return the font
	s_Fonts[filename] = pFont;
	return *pFont;
}

bool ResourceManager::Initialize( )
{
	// Load the default texture
	const sf::Uint8 data[ 16 ] = 
	{
		0, 0, 0, 255,			255, 0, 255, 255,
		255, 0, 255, 255,		0, 0, 0, 255
	};

	// Create a new texture if it already is allocated.
	if( s_pErrorTexture )
	{
		delete s_pErrorTexture;
	}
	s_pErrorTexture = new sf::Texture;

	// Create an image
	sf::Image image;
	image.create( 2, 2, data );
	
	// Load the texture from the image.
	if( s_pErrorTexture->loadFromImage( image, sf::IntRect( 0, 0, 2, 2 ) ) == false )
	{
		std::cout << "[ResourceManager::Initialize] Can not load the default texture." << std::endl;
		delete s_pErrorTexture;
		return false;
	}

	// Load the error font
	if( s_pErrorFont == NULL )
	{
		s_pErrorFont = new sf::Font;
	}

	// Succeeded.
	return true;
}

void ResourceManager::Unload( )
{
	ClearAllTextures( );
	ClearAllFonts( );

	if( s_pErrorTexture )
	{
		delete s_pErrorTexture;
		s_pErrorTexture = NULL;
	}

	if( s_pErrorFont )
	{
		delete s_pErrorFont;
		s_pErrorFont = NULL;
	}
}

void ResourceManager::ClearAllTextures()
{
	for( TextureMap::iterator it = s_Textures.begin( ); it != s_Textures.end( ); it++ )
	{
		delete it->second;
	}
	s_Textures.clear( );
}

void ResourceManager::ClearAllFonts()
{
	for( FontMap::iterator it = s_Fonts.begin( ); it != s_Fonts.end( ); it++ )
	{
		delete it->second;
	}
	s_Fonts.clear( );
}