#pragma once

#include <SFML/Graphics.hpp>
#include "state.hpp"
#include "Gameloop.hpp"
#include "AI.hpp"


namespace Bado
{
	
	class GameState : public State
	{
	public:
		GameState( GameDataRef data);

		void Init();

		void HandleInput( );
		void Update( float dt );
		void Draw( float dt );


		bool isAvaiable(int x, int y, int i, int j);
	private:
		GameDataRef _data;

		void CheckAndPlacePoint(int i, int j);
		bool CheckisWinning(int i, int j);

		sf::Clock _clock;
		sf::CircleShape _circle[14][10];
		sf::CircleShape _cursor;
		int Pitch[15][11]={0};
		bool isLast[15][11]={0};
		bool turn;
		int gamestate=0;

		sf::Text text[6];

		AI *ai;
		

	};
}