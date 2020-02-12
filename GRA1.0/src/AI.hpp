#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "state.hpp"
#include "Gameloop.hpp"


namespace Bado
{
	class AI
	{
	public:
		AI ( GameDataRef data );

		void PlacePoint( int (Pitch)[14][10] ,int x , int y, bool (isLast)[14][10]);
		bool isAvaiable(int x, int y, int i, int j);

	private:
	
		GameDataRef _data;

		int Search (int Pitch[14][10],int i, int j,int distance, bool isoponent);
		int foponent(int Pitch[14][10],int i, int j,int y,int x);
	};

	
}