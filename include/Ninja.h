#pragma once
#include <Entity.h>
#include <DynamicBody.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

class Ninja : public Entity
{
public:
	Ninja(b2World& world);
	~Ninja();

	virtual void update( );
	virtual void draw( sf::RenderTarget& target );
	void setPosition(float32 x, float32 y);

private:
	//ninja stuff
	DynamicBody m_Body;
	sf::Sprite m_Sprite;


};
