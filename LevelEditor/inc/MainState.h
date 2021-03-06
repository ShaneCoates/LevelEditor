/*
Author: Shane Coates
Description: Main State
*/

#ifndef _MAIN_STATE_H_
#define	_MAIN_STATE_H_

#include "GameStateManager.h"
#include "glm.hpp"
#include <vector>
#include <list>
struct GLFWwindow;
class FlyCamera;
class Skybox;
class Tile;
class Cube;
class MainState : public IGameState
{
public:
	//Constructor inherits from IGameState and calls the Init function
	MainState(GLFWwindow* _window, GameStateManager* _gameStateManager) : IGameState()
	{
		Init(_window, _gameStateManager);
	}
	//Destructor
	~MainState();

	//Initialise the gamestate
	void Init(GLFWwindow* _window, GameStateManager* _gameStateManager);

	//Update/Draw functions
	void Update(double _dt);
	void Draw();

	void RefreshWindow();

private:

	void DrawGUI();

	void CreateTiles(int _size[2]);
	void CreateTiles(int _size1, int _size2);

	GLFWwindow* m_window;
	GameStateManager* m_gameStateManager;

	FlyCamera* m_camera;
	Skybox* m_skybox;

	glm::vec2 mousePos;
	std::vector<Tile*> m_tiles;
	std::list<Cube*> m_cubes;

	int m_newTiles[2];

};

#endif