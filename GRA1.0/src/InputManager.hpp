#pragma once 

#include <SFML/Graphics.hpp>

namespace Bado
{
	class InputManager
	{
	public:
		InputManager( ){ }
		~InputManager( ){ }

		bool IsSpriteClicked( sf::Sprite object,
		sf::Mouse::Button button, sf:: RenderWindow &window);

		sf::Vector2i GetMousePosition( sf::RenderWindow &window);

		bool IsPointClicked( sf::CircleShape point,
		sf::Mouse::Button button, sf::RenderWindow &window);

		bool IsMouseThere( sf::CircleShape point,
		 sf::RenderWindow &window);

		bool IsMouseThere_Sprite( sf::Sprite object,
		 sf::RenderWindow &window);

		bool IsMouseThere_Text( sf::Text text,
		 sf::RenderWindow &window);

		bool IsTextClicked( sf::Text text,
		sf::Mouse::Button button, sf::RenderWindow &window);

	};
}