#include <sstream>
#include <iostream>
#include "definitions.hpp"
#include "MainMenuState.hpp"
#include "SplashState.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"
#include <bits/stdc++.h>

namespace Bado
{
	GameState::GameState( GameDataRef data ) : _data( data )
	{
	}
	void GameState::Init( )
	{	
		turn=0;
		gamestate=0;

		this->ai= new AI(this->_data);
		
		if(this->_data->players[0].getSize()==0)
			this->_data->players[0]="Player 1";
		if(this->_data->players[1].getSize()==0)
			this->_data->players[1]="Player 2";
		this->_data->window.setSize(sf::Vector2u(SCREEN_WIDTH*1.75f,SCREEN_HEIGHT*1.1f));
	
		for(int i=1;i<=13;i++){
			for(int j=1;j<=9;j++){
				if((i!=1&&i!=13)||(j>3&&j<7)){
					Pitch[i][j]=0;
					if( (i==2 || i==12) && j!=4  && j!=5 && j!=9 )
						 Pitch[i][j] = Pitch[i][j] | (1<<5); 
					if( (j==1 || j==9) && i!=12 )
						 Pitch[i][j] = Pitch[i][j] | (1<<7); 
				}
				else
				Pitch[i][j]=-2;
				isLast[i][j]=0;
			}
		}
		isLast[7][5]=1;
		
		//gora
		Pitch[1][4] = Pitch[1][4] | (1<<5); 
		Pitch[1][5] = Pitch[1][5] | (1<<5);
		Pitch[1][6] = Pitch[1][6] | (1<<7);
		Pitch[2][4] = Pitch[2][4] | (1<<1); 
		
		//dol
		Pitch[12][4] = Pitch[12][4] | (1<<7);
		Pitch[13][4] = Pitch[13][4] | (1<<5);
		Pitch[13][5] = Pitch[13][5] | (1<<5);
		Pitch[13][6] = Pitch[13][6] | (1<<1);
		Pitch[12][9] = Pitch[12][9] | (1<<1);

		this->_data->assets.LoadFont( "font", FONT_PATH);
		
		text[0].setFont(this->_data->assets.GetFont( "font"));
		text[0].setFillColor(sf::Color::White);
		text[0].setCharacterSize(24);
		text[0].setString(this->_data->players[turn]+"Has a ball");
		text[0].setPosition(550,100);

		text[1].setFont(this->_data->assets.GetFont( "font"));
		text[1].setFillColor(sf::Color::White);
		text[1].setCharacterSize(24);
		text[1].setString("RETRY");
		text[1].setPosition(550,550);
	
		text[2].setFont(this->_data->assets.GetFont( "font"));
		text[2].setFillColor(sf::Color::White);
		text[2].setCharacterSize(24);
		text[2].setString("EXIT");
		text[2].setPosition(550,600);

		_cursor.setPosition(sf::Vector2f(40+50*5-5.0f,70+50*7-5.0f));
		this->_data->assets.LoadTexture( "Ball",BALL);

	}

	void GameState::HandleInput( )
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
			default:

				break;
			}
			
			for(int i=0; i<3;i++)
				if(this->_data->input.IsTextClicked(text[i], sf::Mouse::Left,  this->_data->window))
				{
					switch( i )
					{
						case 1:
						{
						this->_data->machine.AddState( StateRef( new GameState( _data )), true);
						break;
						}	
						case 2:
						{
						this->_data->machine.AddState( StateRef( new MainMenuState( _data )), true);
						this->_data->window.setSize(sf::Vector2u(SCREEN_WIDTH,SCREEN_HEIGHT));
						break;
						}
						default:
						break;
					}
				}
		
			for(int i=1; i<=13;i++)
				for(int j=1; j<=9;j++)
					if(!CheckisWinning(i,j))
					{	
						if(this->_data->gametype==SINGLEPLAYER && this->_data->turn==1)
						{
							if(isLast[i][j])
							{
								ai->PlacePoint(Pitch, i, j, isLast);
								float posy =70+50*i, posx=40+50*j ;
								_cursor.setRadius(5.0f);
								_cursor.setPosition(sf::Vector2f(posx-5.0f,posy-5.0f));
								return;
							}
						}
						else if(this->_data->input.IsMouseThere( _circle[i][j], this->_data->window))
							{
								CheckAndPlacePoint ( i , j );	
							}
					}
		}		
		
	}

	void GameState::Update( float dt )
	{

		text[3].setFont(this->_data->assets.GetFont( "font"));
		text[3].setFillColor(sf::Color::White);
		text[3].setCharacterSize(24);
		text[3].setString(this->_data->players[1]);
		text[3].setPosition(_circle[1][5].getPosition( ).x - text[3].getGlobalBounds().width/2,
			_circle[1][5].getPosition( ).y-text[3].getGlobalBounds( ).height*2);
	
		text[4].setFont(this->_data->assets.GetFont( "font"));
		text[4].setFillColor(sf::Color::White);
		text[4].setCharacterSize(24);
		text[4].setString(this->_data->players[0]);
		text[4].setPosition(_circle[13][5].getPosition( ).x - text[4].getGlobalBounds( ).width/2,
			_circle[13][5].getPosition( ).y + text[4].getGlobalBounds().height);

		text[0].setString(this->_data->players[this->_data->turn]+" has a ball");

		if(gamestate>=PLAYER1WON){
			text[5].setFont(this->_data->assets.GetFont( "font"));
			text[5].setFillColor(sf::Color::White);
			text[5].setCharacterSize(40);
			text[5].setString(this->_data->players[gamestate-91]+" has Won!");
			text[5].setPosition(550,SCREEN_HEIGHT/2.f-text[5].getGlobalBounds( ).height/2);
		}
	}
	void GameState::Draw( float dt)
	{
		this->_data->window.clear( sf::Color(75,162,47,1));

		for(int i=1; i<=13;i++){
			for(int j=1; j<=9;j++){	
				if((i!=1&&i!=13)||(j>3&&j<7)){
					float y =70+50*i, x=40+50*j ;
					if(Pitch[i][j]>0 || (i==7 && j==5)) {
						_circle[i][j].setFillColor(sf::Color::White);
						if(isLast[i][j]){
						  	_circle[i][j].setRadius(10.0f);
						  	_circle[i][j].setTexture(&this->_data->assets.GetTexture( "Ball"));
							_circle[i][j].setPosition(sf::Vector2f(x-10.0f,y-10.0f));
						}
						else
						{
							_circle[i][j].setTexture(NULL);
							_circle[i][j].setRadius(5.0f);
							_circle[i][j].setPosition(sf::Vector2f(x-5.0f,y-5.0f));
						}
					}
					else{
							_circle[i][j].setTexture(NULL);
							_circle[i][j].setRadius(3.0f);
							_circle[i][j].setFillColor(sf::Color::White);
							_circle[i][j].setPosition(sf::Vector2f(x-3.0f,y-3.0f));
					}			

					//sprawdz ktore kreski mozesz narysować
					for(int ly=-1;ly<2;ly++)
						for(int lx=-1;lx<2;lx++){
							int actBIT=(lx+1)+3*(ly+1);//bit ktory w masce ma sie zapalic
							if(Pitch[i][j]&(1<<actBIT)){
								sf::Vertex line[] =	{sf::Vertex(sf::Vector2f(x, y)),
	    						sf::Vertex(sf::Vector2f(x + 50*lx, y + 50*ly))} ;
								_data->window.draw(line, 2, sf::Lines);
						}
					}
					_data->window.draw(_circle[i][j]);
					//_data->window.draw(_cursor);
					
					//kreski kursora
					if(isLast[i][j]){
						sf::Vertex line[] =	{sf::Vertex(sf::Vector2f(x, y),sf::Color::Black),
	    					sf::Vertex(sf::Vector2f(_cursor.getPosition().x +5.0f,
	    					_cursor.getPosition().y +5.0f),sf::Color::White)} ;
							_data->window.draw(line, 2, sf::Lines);
					}
				}
			}
		}	
		switch( gamestate )
		{
			case PLAYER1WON:
			_data->window.draw(text[5]);
			break;
			case PLAYER2WON:
			_data->window.draw(text[5]);
			break;
			default:
			break;
		}

		for(int i=0;i<5;i++)
			_data->window.draw(text[i]);
		
		this->_data->window.display( );
	}
		

	void GameState::CheckAndPlacePoint (int i, int j)
	{	

		for(int y=-1;y<2;y++)
			for(int x=-1;x<2;x++){
				if(isLast[i+y][j+x] && (x!=0 || y!=0) && x+j<=9 && y+i<=13 && x+j>0 && y+i>0 && 
					(i!=1 || j!=4 ) && (i!=1 || j!=6 ) && (i!=13 || j!=4 ) && (i!=13 || j!=6 ))
				{
					int actBIT=3*(y+1)+(x+1);//bit ktory w masce ma sie zapalic
					int lastBIT=3*(-y+1)+(-x+1); //bit z punkktu z ktorego przechodzi
						
					if(Pitch[i][j]&(1<<actBIT)) 		return;
					if(Pitch[i+y][j+x]&(1<<lastBIT))	return;


					float posy =70+50*i, posx=40+50*j ;
					_cursor.setRadius(5.0f);
					_cursor.setPosition(sf::Vector2f(posx-5.0f,posy-5.0f));

					//jesli prawidlowy punkt to sprawdz czy zostal klikniety
					if(this->_data->input.IsPointClicked(_circle[i][j], sf::Mouse::Left,  this->_data->window))
					{
						if(Pitch[i][j]==0){
							this->_data->turn = !this->_data->turn;
						}

						Pitch[i][j] = Pitch[i][j] | (1<<actBIT); //zapal bity
						Pitch[i+y][j+x] =  Pitch[i+y][j+x] | (1<<lastBIT);

						isLast[i+y][j+x]=0, isLast[i][j]=1; //zmien aktualnie ostatniego
						//sprawdz czy nie zablokowałes
					}
				}
			}		
	}

	bool GameState::CheckisWinning(int i, int j) 
	{
		if(Pitch[1][5]&(1<<7)|| Pitch[1][5]&(1<<6) || Pitch[1][5]&(1<<8)){
			gamestate=PLAYER1WON;
			return true;
		}
		if(Pitch[13][5]&(1<<1) || Pitch[13][5]&(1<<0) ||Pitch[13][5]&(1<<2) ){
			gamestate=PLAYER2WON;
			return true;
		}

		if(isLast[i][j]){
			for(int y=-1;y<2;y++)
				for(int x=-1;x<2;x++){
					if((x!=0 || y!=0) && x+j<=9 && y+i<=13 && x+j>0 && y+i>0 && ( (i+y!=1 && i+y!=13 )||( j+x>3 && j+x<7 ) ) )
					{
						int actBIT=3*(y+1)+(x+1);//bit ktory w masce ma sie zapalic
						int lastBIT=3*(-y+1)+(-x+1); //bit z punkktu z ktorego przechodzi
						if(!(Pitch[i][j]&(1<<actBIT)) && !(Pitch[i+y][j+x]&(1<<lastBIT)))
							return false;		
					}	
				}	
			gamestate=PLAYER1WON+!this->_data->turn;
			return true;
		}
		return false;
	}

	bool GameState::isAvaiable(int x, int y, int i, int j)
	{
	if( (x!=0 || y!=0) && x+j<=9 && y+i<=13 && x+j>0 && y+i>0 && ( (i+y!=1 && i+y!=13 )||( j+x>3 && j+x<7 ) ) &&
				(i+y!=1 || j+x!=4 ) && (i+y!=1 || j+x!=6 ) && (i+y!=13 || j+x!=4 ) && (i+y!=13 || j+x!=6 ) ) 
			return true;
		return false;
	}

}
