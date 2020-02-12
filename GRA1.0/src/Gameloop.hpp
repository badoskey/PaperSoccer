#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "StateMachine.hpp"

namespace Bado
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
		sf::String players[2];
		int gametype;
		bool turn;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Gameloop
	{
	public:
		Gameloop( int width, int height, std::string title);
	
	private:
		const float dt = 1.0f/ 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData> ( );

		void Run( );
	};



}