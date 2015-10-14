#include "MainState.h"
#include <gl_core_4_4.h>
#include "GLFW\glfw3.h"
#include "Skybox.h"
#include "FlyCamera.h"
#include "aieutilities\Gizmos.h"
#include "Game.h"
#include "Tile.h"
#include "Cube.h"
#include "imgui.h"
void MainState::Init(GLFWwindow* _window, GameStateManager* _gameStateManager) {
	m_window = Game::Instance()->GetWindow();
	m_gameStateManager = _gameStateManager;
	m_skybox = new Skybox();
	m_camera = new FlyCamera(10.0f);
	m_camera->SetInputWindow(m_window);
	m_camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera->SetLookAt(glm::vec3(4, 10, 14), glm::vec3(4, 0, 4), glm::vec3(0, 1, 0));
	CreateTiles(10, 10);
	m_newTiles[0] = 10;
	m_newTiles[1] = 10;

	Gizmos::create();
}
void MainState::Update(double _dt) {
	m_camera->Update(_dt);
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	glm::vec3 pos = m_camera->PickAgainstPlane((float)xpos, (float)ypos, glm::vec4(0, 1, 0, 0));
	mousePos = glm::vec2((int)pos.x, (int)pos.z);
	bool found = false;
	for (auto tile : m_tiles)
	{
		tile->Update(_dt);
		if (tile->ComparePos(mousePos))
		{
			tile->Hover();
			if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1))
			{
				m_cubes.push_back(new Cube(mousePos));
			}
		}
	}
	for (auto cube : m_cubes)
	{
		cube->Update(_dt);
		if (cube->ComparePos(mousePos))
		{
			if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_2))
			{
				m_cubes.remove(cube);
				break;
			}
		}
	}
}
void MainState::Draw()
{
	glClearColor(1, 1, 1, 1);
	Gizmos::clear();

	m_skybox->Draw(m_camera);

	for (auto tile : m_tiles)
	{
		tile->Draw();
	}
	for (auto cube : m_cubes)
	{
		cube->Draw();
	}

	Gizmos::draw(m_camera->GetProjectionView());
	MainState::DrawGUI();
}

void MainState::DrawGUI()
{
	if (ImGui::CollapsingHeader("New Map"))
	{
		ImGui::SliderInt2("Map Size", m_newTiles, 1, 100);
		if (ImGui::Button("Create New Map"))
		{
			CreateTiles(m_newTiles);
		}
	}
}

void MainState::CreateTiles(int _size[2])
{
	CreateTiles(_size[0], _size[1]);
}
void MainState::CreateTiles(int _size1, int _size2)
{
	m_cubes.clear();
	m_tiles.clear();
	for (int x = 0; x < _size1; x++)
	{
		for (int z = 0; z < _size2; z++)
		{
			m_tiles.push_back(new Tile(glm::vec2(x, z)));
		}
	}
}
void MainState::RefreshWindow()
{
	m_window = Game::Instance()->GetWindow();
	m_camera->SetInputWindow(m_window);
}

