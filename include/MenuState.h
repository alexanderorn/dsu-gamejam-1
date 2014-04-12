#pragma once
#include <State.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <vector>

// Forward declaraction
class Game;

class MenuState : public State
{

public:

	// Constructors/destructors
	MenuState( Game * pGame );
	~MenuState( );

	// Public functions
	virtual bool Update( );
	virtual void Render( );
	virtual bool Enter( );
	virtual void Leave( );
	virtual bool HandleEvent( const sf::Event & p_Event );

	// Get functions
	virtual bool IsLoaded( ) const;

private:

	// Private structs
	struct Button
	{
		Button(		const std::string p_Label,
					const std::string p_LevelPath,
					const sf::Vector2f p_Position ) :
			Label( p_Label ),
			LevelPath( p_LevelPath ),
			Position( p_Position  )
		{
		}

		std::string Label;
		std::string LevelPath;
		sf::Vector2f Position;
	};

	// Private functions
	bool ReadLevelFile( const std::string & filename );
	bool ReadSaveFile( const std::string & filename );

	// Private variables
	bool m_Loaded;
	Game * m_pGame;
	sf::Text m_HeaderText;
	sf::Text m_ButtonText;
	sf::Sprite m_ButtonFrameSprite;
	std::vector<Button> m_Buttons;
	unsigned int m_FinishedLevels;

};