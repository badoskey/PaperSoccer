#include <sstream>
#include "MainMenuState.hpp"
#include "definitions.hpp"
#include "SplashState.hpp"
#include "state.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"

#include <iostream>

namespace Bado
{
	MainMenuState::MainMenuState(GameDataRef data ) : _data( data )
	{


	}


	void MainMenuState::Init( )
	{
		this->_data->assets.LoadTexture( "Background",
			MAIN_MENU_BACKGROUND_FILEPATH);
		this->_background.setTexture( this->_data->assets.GetTexture( "Background"));

		this->_background.setScale(0.75f,0.75f);

		this->_data->assets.LoadTexture( "Buttons", MAIN_MENU_BUTTONS_FILEPATH);

	

		this->_playButton.setTexture( this->_data->assets.GetTexture("Buttons") );
		float width=this->_playButton.getGlobalBounds( ).width; 
		float height=this->_playButton.getGlobalBounds( ).height; //26
		this->_playButton.setTextureRect(sf::IntRect(0,0,width,height*4 /26));
		this->_playButton.setScale(0.5f,0.5f);
		this->_playButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_playButton.getGlobalBounds( ).width /2 ), 
			( SCREEN_HEIGHT * 2 / 7 ) - ( this->_playButton.getGlobalBounds( ).height /2 ));

		this->_optionsButton.setTexture( this->_data->assets.GetTexture("Buttons") );
		this->_optionsButton.setTextureRect(sf::IntRect(0, height*4 /26, width, height*4 /26));
		this->_optionsButton.setScale(0.5f,0.5f);
		this->_optionsButton.setPosition( ( SCREEN_WIDTH / 2 ) - (this->_optionsButton.getGlobalBounds( ).width / 2 ), 
			( SCREEN_HEIGHT / 2  ) - ( this->_optionsButton.getGlobalBounds( ).height ) /2 );
		
		this->_exitButton.setTexture( this->_data->assets.GetTexture("Buttons") );
		this->_exitButton.setTextureRect(sf::IntRect(0, height*8 /26, width, height*4 /26));
		this->_exitButton.setScale(0.5f,0.5f);
		this->_exitButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->_exitButton.getGlobalBounds( ).width / 2 ), 
			( SCREEN_HEIGHT *5 /7 ) - ( this->_exitButton.getGlobalBounds( ).height / 2 ));
	
	}

	void MainMenuState::HandleInput( )
	{
		sf::Event event;
		

		while( this->_data->window.pollEvent( event ))
		{	
			if( event.type==sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0,0,event.size.width, event.size.height);
				this->_data->window.setView(sf:: View(visibleArea));
			;
			}

			if(this->_data->input.IsSpriteClicked( this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				if(this->_data->gametype==0){
					this->_optionsButton.setColor(sf::Color::Black);
				}
				else
				{
					this->_data->machine.AddState( StateRef( new GameState( _data )), true);
				}
			}
			
			if( this->_data->input.IsSpriteClicked( this->_exitButton, sf::Mouse::Left, this->_data->window) )
			{	
				this->_data->window.close( );
			}
				
			if(this->_data->input.IsSpriteClicked( this->_optionsButton, sf::Mouse::Left, this->_data->window))
			{	
				this->_data->machine.AddState( StateRef( new OptionsState( _data )), true);
					
			}
			


		}


	}
	void MainMenuState::Update( float dt )
	{
		
		this->_optionsButton.setColor(sf::Color::White);
		this->_playButton.setColor(sf::Color::White);
		this->_exitButton.setColor(sf::Color::White);
		if( this->_data->input.IsMouseThere_Sprite( this->_optionsButton,this->_data->window) )
		{
			this->_optionsButton.setColor(sf::Color(10,120,0));
		}
		if( this->_data->input.IsMouseThere_Sprite( this->_exitButton, this->_data->window) )
		{
			this->_exitButton.setColor(sf::Color(10,120,0));
		}
		if( this->_data->input.IsMouseThere_Sprite( this->_playButton, this->_data->window) )
		{		
			if(this->_data->gametype==0){
					this->_optionsButton.setColor(sf::Color::Red);
			}
			else
				this->_playButton.setColor(sf::Color(10,120,0));
		}
	

	}

	void MainMenuState::Draw( float dt)
	{
		this->_data->window.clear( );

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_optionsButton);
		this->_data->window.draw(this->_exitButton);
		
		this->_data->window.display( );
	}
}
