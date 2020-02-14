Game: AI.o AssetManager.o Gameloop.o GameState.o InputManager.o main.o MainMenuState.o OptionsState.o SplashState.o StateMachine.o
	g++ AI.o AssetManager.o  Gameloop.o GameState.o InputManager.o main.o MainMenuState.o OptionsState.o SplashState.o StateMachine.o -o Game -lsfml-graphics -lsfml-window -lsfml-system 
AI.o: src/AI.cpp
	g++ -c src/AI.cpp
AssetManager.o: src/AssetManager.cpp
	g++ -c src/AssetManager.cpp
Gameloop.o: src/Gameloop.cpp
	g++ -c src/Gameloop.cpp
GameState.o: src/GameState.cpp
	g++ -c src/GameState.cpp
InputManager.o: src/InputManager.cpp
	g++ -c src/InputManager.cpp
main.o: src/main.cpp
	g++ -c src/main.cpp
MainMenuState.o: src/MainMenuState.cpp
	g++ -c src/MainMenuState.cpp
OptionsState.o: src/OptionsState.cpp
	g++ -c src/OptionsState.cpp
SplashState.o: src/SplashState.cpp
	g++ -c src/SplashState.cpp
StateMachine.o: src/StateMachine.cpp
	g++ -c src/StateMachine.cpp
clean:
	rm *.o Game
 
