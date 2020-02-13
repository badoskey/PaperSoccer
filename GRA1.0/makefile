Game: src/AI.o src/AssetManager.o src/Gameloop.o src/GameState.o src/InputManager.o src/main.o src/MainMenuState.o src/OptionsState.o src/SplashState.o src/StateMachine.o
	g++ AI.o AssetManager.o  Gameloop.o GameState.o InputManager.o main.o MainMenuState.o OptionsState.o SplashState.o StateMachine.o -o Game -lsfml-graphics -lsfml-window -lsfml-system 
src/AI.o: src/AI.cpp
	g++ -c src/AI.cpp
src/AssetManager.o: src/AssetManager.cpp
	g++ -c src/AssetManager.cpp
src/Gameloop.o: src/Gameloop.cpp
	g++ -c src/Gameloop.cpp
src/GameState.o: src/GameState.cpp
	g++ -c src/GameState.cpp
src/InputManager.o: src/InputManager.cpp
	g++ -c src/InputManager.cpp
src/main.o: src/main.cpp
	g++ -c src/main.cpp
src/MainMenuState.o: src/MainMenuState.cpp
	g++ -c src/MainMenuState.cpp
src/OptionsState.o: src/OptionsState.cpp
	g++ -c src/OptionsState.cpp
src/SplashState.o: src/SplashState.cpp
	g++ -c src/SplashState.cpp
src/StateMachine.o: src/StateMachine.cpp
	g++ -c src/StateMachine.cpp
clean:
	rm *.o Game
 
