/*
	Author: Shane Coates
	Description: Main Game class
*/

#ifndef _GAME_H_
#define	_GAME_H_

struct GLFWwindow;
class GameStateManager;
class MainState;
class Game
{
public:

	//Constructor
	Game();
	//Destructor
	~Game();

	//Main Game loop
	void Run();

	static Game* Instance();

	GLFWwindow* GetWindow();

protected:
private:

	bool m_fullscreen = false;
	void ToggleFullscreen(bool _fullscreen, int _width = 1024, int _height = 768);

	static Game* m_instance;

	//Function to return DeltaTime
	double GetDeltaTime();

	//Variables to calculate Delta Time
	double currentFrame;
	double deltaTime;
	double lastFrame;
	
	//Window
	GLFWwindow* m_gameWindow;
	
	//Game State Manager
	GameStateManager* m_gameStateManager;

	MainState* m_mainState;
	
};

#endif