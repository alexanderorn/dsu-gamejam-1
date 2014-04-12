#pragma once
#include <Entity.h>
#include <DynamicBody.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <ThrowingStar.h>
#include <vector>



class Ninja : public Entity
{
public:
	Ninja(b2World& world, std::vector<ThrowingStar*>&);
	~Ninja();

	virtual void update( );
	virtual void draw( sf::RenderTarget& target );
	
	DynamicBody* getBody();

private:

	b2World& m_World;

	// helpfunctions
	void keepUpright( );
	void speedlimit( );
	
	//ninja stuff
	DynamicBody m_Legs;
	sf::Sprite m_Sprite;
	int m_MaxSpeed;

	bool m_Jumping;
	sf::Clock m_JumpClock;
	int m_JumpCooldown;

	//throwstuff
	sf::Clock m_ThrowClock;
	bool m_Shot;
	int m_ThrowCooldown;

	std::vector<ThrowingStar*>& m_ThrowingStars;

};
