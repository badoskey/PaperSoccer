#include <sstream>
#include <iostream>
#include "definitions.hpp"
#include "MainMenuState.hpp"
#include "AI.hpp"
#include "GameState.hpp"
#include "OptionsState.hpp"
#include <bits/stdc++.h>
using namespace std;


namespace Bado
{
	AI::AI(GameDataRef data  )
	{
		this->_data = data;
	}

	void AI::PlacePoint( int (Pitch)[15][11] ,int i, int j, bool (isLast)[15][11])
	{
		int best_move=-20, best_BIT;
		for(int y=1;y>-2;y--)
			for(int x=1;x>-2;x--)
				if(isAvaiable(x,y,i,j)){
					int actBIT=3*(y+1)+(x+1);//bit ktory w masce ma sie zapalic				
					int nextBIT=3*(-y+1)+(-x+1); //bit z punktu z ktorego przechodzi
						
					if((Pitch[i+y][j+x])&(1<<nextBIT)) 		continue;
					if((Pitch[i][j])&(1<<actBIT))			continue;
					
					int distance, oponent=0;
					if(Pitch[i+y][j+x]==0 ){
						oponent=foponent(Pitch,i,j,y,x);
						distance=y;
					}
					else{
						Pitch[i+y][j+x] = Pitch[i+y][j+x] | (1<<nextBIT); //zapal bity
						Pitch[i][j] 	= Pitch[i][j] | (1<<(actBIT));	

						distance= Search(Pitch,i+y,j+x,y,0,1);
						

						Pitch[i+y][j+x] = Pitch[i+y][j+x] & ~(1<<nextBIT); //zapal bity
						Pitch[i][j] 	= Pitch[i][j] & ~(1<<(actBIT));
						}

					if(best_move<distance+oponent)
					{
						best_move=distance+oponent;
						best_BIT=actBIT;
					}
				}

		///Oficialnie wykonany ruch /////		

		int y=best_BIT/3-1, x=best_BIT%3-1;
		if(Pitch[i+y][j+x]==0)
			this->_data->turn=!this->_data->turn;



		Pitch[i][j] = Pitch[i][j] | (1<<best_BIT); //zapal bity
		Pitch[i+y][j+x] =  Pitch[i+y][j+x] | (1<<(8-best_BIT));
		isLast[i][j]=0, isLast[i+y][j+x]=1;
				
		return;
	
	}


	int AI::Search (int Pitch[15][11],int i, int j, int distance,bool isoponent, int count)
	{
		int best_way=distance;
		bool isloosing=1;

		if(Pitch[13][5]&(1<<1) || Pitch[13][5]&(1<<0) ||Pitch[13][5]&(1<<2) ){
			return 1000;
		}
		
		//jezeli to pole przegywajace
		for(int y=-1;y<2;y++)
				for(int x=-1;x<2;x++)
					if((x!=0 || y!=0) && x+j<=9 && y+i<=13 && x+j>0 && y+i>0 && ( (i+y!=1 && i+y!=13 )||( j+x>3 && j+x<7 ) ) )
					{
						int actBIT=3*(y+1)+(x+1);//bit ktory w masce ma sie zapalic
						int lastBIT=3*(-y+1)+(-x+1); //bit z punkktu z ktorego przechodzi
						if(!(Pitch[i][j]&(1<<actBIT)) && !(Pitch[i+y][j+x]&(1<<lastBIT)))
							isloosing=0;
					}

		for(int y=1;y>-2;y--){
			for(int x=1;x>-2;x--){
				if(isAvaiable(x,y,i,j))
				{	
					int oponent=0;
					int copy_distance=distance;
					int actBIT=3*(y+1)+(x+1);			
					int nextBIT=3*(-y+1)+(-x+1); 
						
					if((Pitch[i+y][j+x])&(1<<nextBIT)) 		continue;
					if((Pitch[i][j])&(1<<actBIT))			continue;

					if(Pitch[i+y][j+x]==0 || count>25){  
						if(isoponent==0){
							if(distance>best_way)
								oponent=foponent(Pitch,i,j,y,x);
							
						}
						copy_distance+= y;

					}
					else{
						
						Pitch[i+y][j+x] = Pitch[i+y][j+x] | (1<<nextBIT); //zapal bity
						Pitch[i][j] 	= Pitch[i][j] | (1<<(actBIT));

						copy_distance=Search(Pitch,i+y,j+x,distance + y,isoponent,count+1);
						
						Pitch[i+y][j+x] = Pitch[i+y][j+x] & ~(1<<nextBIT); //zapal bity
						Pitch[i][j] 	= Pitch[i][j] & ~(1<<(actBIT));

						}
					
					if(isoponent==1)
					{
					 	if(best_way>copy_distance && copy_distance>-50)
					 	{
					 	best_way=copy_distance;
						}
					}
					else if(best_way<copy_distance+oponent)
					{
						best_way=copy_distance+oponent;
					}

				}
			}
		}
			if(isloosing){
				return -100;
			}
			return best_way;
	}

	bool AI::isAvaiable(int x, int y, int i, int j)
	{
		if( (x!=0 || y!=0) && x+j<=9 && y+i<=13 && x+j>0 && y+i>0 && ( (i+y!=1 && i+y!=13 )||( j+x>3 && j+x<7 ) ) &&
		(i+y!=1 || j+x>4 ) && (i+y!=1 || j+x<6 ) && (i+y!=13 || j+x>4 ) && (i+y!=13 || j+x<6 ) ) 
			return true;
		return false;

	}

	int AI::foponent(int Pitch[15][11],int i,int j,int y,int x)
	{
		int actBIT=3*(y+1)+(x+1);//bit ktory w masce ma sie zapalic				
		int nextBIT=3*(-y+1)+(-x+1); //bit z punktu z ktorego przechodzi
		
		Pitch[i+y][j+x] = Pitch[i+y][j+x] | (1<<nextBIT); //zapal bity
		Pitch[i][j] 	= Pitch[i][j] | (1<<(actBIT));

		int oponent=Search(Pitch,i+y,j+x,y,1,1);
						
		Pitch[i+y][j+x] = Pitch[i+y][j+x] & ~(1<<nextBIT); //zapal bity
		Pitch[i][j] 	= Pitch[i][j] & ~(1<<(actBIT));

		return oponent;
	}



}