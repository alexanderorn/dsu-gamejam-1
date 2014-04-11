#pragma once

class Game
{

public:

	virtual ~Game( );

	virtual int Run( int argv, char ** argc ) = 0;

};