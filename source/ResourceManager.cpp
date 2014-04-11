#include <ResourceManager.h>
#include <iostream>

ResourceManager::TextureMap ResourceManager::s_Textures;
sf::Texture * ResourceManager::s_pErrorTexture = NULL;

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

	sf::Image image;
	image.create( 2, 2, data );
	
	// Load the file from memory
	if( s_pErrorTexture->loadFromImage( image, sf::IntRect( 0, 0, 2, 2 ) ) == false )
	{
		std::cout << "[ResourceManager::Initialize] Can not load the default texture." << std::endl;
		delete s_pErrorTexture;
		return false;
	}

	// Succeeded.
	return true;
}

void ResourceManager::Unload( )
{
	if( s_pErrorTexture )
	{
		delete s_pErrorTexture;
		s_pErrorTexture = NULL;
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