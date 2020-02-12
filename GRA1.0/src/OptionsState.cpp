#include <sstream>
#include <iostream>
#include "definitions.hpp"
#include "MainMenuState.hpp"
#include "OptionsState.hpp"
#include "GameState.hpp"
#include <bits/stdc++.h>

namespace Bado
{
	OptionsState::OptionsState( GameDataRef data ) : _data( data )
	{
	}
	void OptionsState::Init( )
	{	
		if(this->_data->players[0].getSize()==0)
			this->_data->players[0]="Player 1";
		if(this->_data->players[1].getSize()==0)
			this->_data->players[1]="Player 2";

		this->_data->assets.LoadFont( "font", FONT_PATH);
		options[0].setFont(this->_data->assets.GetFont( "font"));
		options[0].setCharacterSize(40);
		options[0].setString("Singleplayer");
		options[0].setPosition(SCREEN_WIDTH/2.f-options[0].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*2.f/8.f-options[0].getGlobalBounds( ).height/2);

		options[1].setFont(this->_data->assets.GetFont( "font"));
		options[1].setCharacterSize(40);
		options[1].setString("Multiplayer");
		options[1].setPosition(SCREEN_WIDTH/2.f-options[1].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*4.f/8.f-options[1].getGlobalBounds( ).height/2);
	
	
		options[2].setFont(this->_data->assets.GetFont( "font"));
		options[2].setFillColor(sf::Color::White);
		options[2].setCharacterSize(40);
		options[2].setString("Back");
		options[2].setPosition(SCREEN_WIDTH/2.f-options[2].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*6.f/8.f-options[2].getGlobalBounds( ).height/2);

	}


	void OptionsState::HandleInput( )
	{
		sf::Event event;

		while ( this->_data->window.pollEvent( event ) )
		{
			switch( event.type )
			{
				case sf::Event::Closed:
				{
					this->_data->window.close( );
					break;
				}
				case sf::Event::Resized:
				{
					sf::FloatRect visibleArea(0,0,event.size.width, event.size.height);
					this->_data->window.setView(sf:: View(visibleArea));
					break;
				}
				case sf::Event::TextEntered:
				{
					if(pick>2 && pick <5 ){
						if(event.text.unicode >= 32 && event.text.unicode<=126)
							this->_data->players[pick-3] +=(char)event.text.unicode;
						else if(event.text.unicode==8 && this->_data->players[pick-3].getSize()>0)
							this->_data->players[pick-3].erase(this->_data->players[pick-3].getSize() - 1, 
																this->_data->players[pick-3].getSize( ));

						options[pick].setString(this->_data->players[pick-3]);
					}	
					break;
				}
				default:
					break;
			}
		}
			if(pick<0){
				for(int i=0; i<3;i++)
					if(this->_data->input.IsTextClicked(options[i], sf::Mouse::Left,  this->_data->window))
						if( this->_clock.getElapsedTime( ).asSeconds( ) >SPLASH_STATE_SHOW_TIME/2.f){
							switch( i )
							{
								case 0:
								{
								pick=0;	
								this->_data->gametype=SINGLEPLAYER;
								this->_data->players[1]="Mohamed Salah";
						
								break;
								}	
								case 1:
								{
								pick=1;
								this->_data->gametype=MULTIPLAYER;
								std::cout<<this->_data->gametype<<std::flush;
								break;
								}
								case 2:
								{
								this->_data->machine.AddState( StateRef( new MainMenuState(_data )), true);
								break;
								}
							}
						}
			}
			else{
				for(int i=3; i<6;i++)
					if(this->_data->input.IsTextClicked(options[i], sf::Mouse::Left,  this->_data->window))
						if( this->_clock.getElapsedTime( ).asSeconds( ) >SPLASH_STATE_SHOW_TIME/2.f){
							switch( i )
							{
								case 3:
								{	
								pick=3; //PLAYER ONE
								break;
								}	
								case 4:
								{
								pick=4;	//PLAYER TWO
								break;
								}
								case 5:
								{
								this->_data->machine.AddState( StateRef( new OptionsState(_data )), false);
								pick=-1;
								break;
								}
								
								default:
								break;
							}
						}	
				}
	}

	void OptionsState::Update( float dt)
	{
		if(this->_data->gametype==SINGLEPLAYER){
			options[0].setFillColor(sf::Color(10,120,0));
			options[1].setFillColor(sf::Color::White);
		}	
		if(this->_data->gametype==MULTIPLAYER)
		{
			options[1].setFillColor(sf::Color(10,120,0));
			options[0].setFillColor(sf::Color::White);
		}

		if(pick>-1){
		options[3].setFont(this->_data->assets.GetFont( "font"));
		options[3].setFillColor(sf::Color::White);
		options[3].setCharacterSize(40);
		options[3].setString(this->_data->players[0]);
		options[3].setPosition(SCREEN_WIDTH/2.f-options[3].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*2.f/8.f-options[3].getGlobalBounds( ).height/2);

		options[4].setFont(this->_data->assets.GetFont( "font"));
		options[4].setFillColor(sf::Color::White);
		options[4].setCharacterSize(40);
		options[4].setString(this->_data->players[1]);
		options[4].setPosition(SCREEN_WIDTH/2.f-options[4].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*4.f/8.f-options[4].getGlobalBounds( ).height/2);
	
	
		options[5].setFont(this->_data->assets.GetFont( "font"));
		options[5].setFillColor(sf::Color::White);
		options[5].setCharacterSize(40);
		options[5].setString("Back");
		options[5].setPosition(SCREEN_WIDTH/2.f-options[5].getGlobalBounds( ).width/2,
			SCREEN_HEIGHT*6.f/8.f-options[5].getGlobalBounds( ).height/2);
		}
	}
	void OptionsState::Draw( float dt)
	{
		this->_data->window.clear( sf::Color(75,162,47,1));
		
		if(pick<0){
			for(int i=0;i<3;i++)
				_data->window.draw(options[i]);
		}
		else{
			for(int i=3;i<6;i++)
				_data->window.draw(options[i]);
		}
		
		this->_data->window.display( );
	}
		
}