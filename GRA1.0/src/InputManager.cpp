#include "InputManager.hpp"

namespace Bado
{
	bool InputManager::IsSpriteClicked( sf::Sprite object, 
		sf::Mouse::Button button, sf:: RenderWindow &window)
	{
		if( sf::Mouse::isButtonPressed ( button ))
		{
			sf::IntRect ButtonRect( object.getPosition( ).x, object.getPosition( ).y,
				object.getGlobalBounds( ).width, object.getGlobalBounds( ).height );
			if( ButtonRect.contains( sf::Mouse::getPosition(window) ) )
			{
				return true;
			}
		}
	
		return false;

	}

	bool InputManager::IsPointClicked( sf::CircleShape point,
		sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if( sf::Mouse::isButtonPressed (button))
		{
			sf::IntRect ButtonRect( point.getPosition( ).x, point.getPosition( ).y,
				point.getGlobalBounds( ).width*3, point.getGlobalBounds( ).height*3);
			if(ButtonRect.contains( sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsTextClicked( sf::Text text,
		sf::Mouse::Button button, sf::RenderWindow &window)
	{
		if( sf::Mouse::isButtonPressed (button))
		{
			sf::IntRect ButtonRect( text.getPosition( ).x, text.getPosition( ).y,
				text.getGlobalBounds( ).width*1.5, text.getGlobalBounds( ).height*1.5);
			if(ButtonRect.contains( sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsMouseThere( sf::CircleShape point,
		 sf::RenderWindow &window)
	{
			sf::IntRect ButtonRect( point.getPosition( ).x, point.getPosition( ).y,
				point.getGlobalBounds( ).width*3, point.getGlobalBounds( ).height*3);
			if(ButtonRect.contains( sf::Mouse::getPosition(window)))
			{
				return true;
			}
			return false;
	}
	bool InputManager::IsMouseThere_Sprite( sf::Sprite object,
		 sf::RenderWindow &window)
	{
			sf::IntRect ButtonRect( object.getPosition( ).x, object.getPosition( ).y,
				object.getGlobalBounds( ).width, object.getGlobalBounds( ).height);
			if(ButtonRect.contains( sf::Mouse::getPosition(window)))
			{
				return true;
			}
			return false;
	}

	bool InputManager::IsMouseThere_Text( sf::Text text,
		 sf::RenderWindow &window)
	{
			sf::IntRect ButtonRect( text.getPosition( ).x, text.getPosition( ).y,
				text.getGlobalBounds( ).width, text.getGlobalBounds( ).height);
			if(ButtonRect.contains( sf::Mouse::getPosition(window)))
			{
				return true;
			}
			return false;
	}


	


	sf::Vector2i GetMousePosition( sf::RenderWindow &window)
	{
			return sf::Mouse::getPosition( window );
	}



}