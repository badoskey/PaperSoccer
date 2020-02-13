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

		void PlacePoint( int (Pitch)[15][11] ,int x , int y, bool (isLast)[15][11]);
		bool isAvaiable(int x, int y, int i, int j);

	private:
	
		GameDataRef _data;

		int Search (int Pitch[15][11],int i, int j,int distance, bool isoponent, int count);
		int foponent(int Pitch[15][11],int i, int j,int y,int x);
	};

	
}