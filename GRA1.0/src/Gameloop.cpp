#include "Gameloop.hpp"
#include "SplashState.hpp"

namespace Bado
{
	Gameloop::Gameloop( int width, int height, std:: string title)
	{
		
		_data->window.create( sf::VideoMode( width, height),
			title, sf::Style::Default);
		_data->machine.AddState( StateRef( new SplashState( this->_data ) ) ) ;  


		this->Run( );
	}

	void Gameloop::Run()
	{
		float newTime, frameTime, interpolation;
		//obecny czas
		float currentTime = this->_clock.getElapsedTime().asSeconds( );
		//czas akumulatora
		float accumulator =0.0f;

		while (this->_data->window.isOpen() )
		{
			this->_data->machine.ProcessStateChanges( ); //init
			//aktualny czas
			newTime = this->_clock.getElapsedTime( ).asSeconds();
			//okres miedzy czasem pobranych
			frameTime = newTime - currentTime;

			if( frameTime > 0.1f)
			{
				frameTime = 0.1f;
			}
		
			currentTime = newTime;
			accumulator +=frameTime;

			//działania w State'cie

			while(accumulator >= dt)
			{
				this->_data->machine.GetActiveState()->HandleInput( );
				this->_data->machine.GetActiveState( )->Update( dt );
			
				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState( )->Draw(interpolation);
		}
	}

}