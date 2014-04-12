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
	virtual e_Type getType();
	DynamicBody* getBody();

private:

	b2World& m_World;

	// helpfunctions
	void keepUpright( );
	void speedlimit( );
	void jump( );
	void shoot( );
	void updateMovement( );
	
	//ninja stuff
	DynamicBody m_Legs;
	sf::Sprite m_Sprite;
	float m_MaxSpeed;
	bool m_Dead;
	bool m_Jumping;
	sf::Clock m_JumpClock;
	float m_JumpCooldown;

	//sword


	//throwstuff
	sf::Clock m_ThrowClock;
	bool m_Shot;
	int m_ThrowCooldown;

	std::vector<ThrowingStar*>& m_ThrowingStars;

};
