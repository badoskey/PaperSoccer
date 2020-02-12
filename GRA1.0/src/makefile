Game: AI.o AssetManager.o Gameloop.o GameState.o InputManager.o main.o MainMenuState.o OptionsState.o SplashState.o StateMachine.o
	g++ AI.o AssetManager.o Gameloop.o GameState.o InputManager.o main.o MainMenuState.o OptionsState.o SplashState.o StateMachine.o -o ../Game -lsfml-graphics -lsfml-window -lsfml-system 
AI.o: AI.cpp
	g++ -c AI.cpp
AssetManager.o: AssetManager.cpp
	g++ -c AssetManager.cpp
Gameloop.o: Gameloop.cpp
	g++ -c Gameloop.cpp
GameState.o: GameState.cpp
	g++ -c GameState.cpp
InputManager.o: InputManager.cpp
	g++ -c InputManager.cpp
main.o: main.cpp
	g++ -c main.cpp
MainMenuState.o: MainMenuState.cpp
	g++ -c MainMenuState.cpp
OptionsState.o: OptionsState.cpp
	g++ -c OptionsState.cpp
SplashState.o: SplashState.cpp
	g++ -c SplashState.cpp
StateMachine.o: StateMachine.cpp
	g++ -c StateMachine.cpp
clean:
	rm *.o Game
 
