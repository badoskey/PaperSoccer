#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "Gameloop.hpp"


namespace Bado
{
	
	class OptionsState : public State
	{
	public:
		OptionsState( GameDataRef data);

		void Init();

		void HandleInput( );
		void Update( float dt );
		void Draw( float dt );

		
		
		sf::String players[2];
	private:
		int gametype;
		GameDataRef _data;

		sf::Clock _clock;
		sf::Text options[7];
		int pick=-1;

	
	};
}