#include "MainState.h"
#include <gl_core_4_4.h>
#include "GLFW\glfw3.h"
#include "Skybox.h"
#include "FlyCamera.h"
#include "aieutilities\Gizmos.h"
#include "Game.h"
void MainState::Init(GLFWwindow* _window, GameStateManager* _gameStateManager) {
	m_window = Game::Instance()->GetWindow();
	m_gameStateManager = _gameStateManager;
	m_skybox = new Skybox();
	m_camera = new FlyCamera(10.0f);
	m_camera->SetInputWindow(m_window);
	m_camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera->SetLookAt(glm::vec3(4, 10, 14), glm::vec3(4, 0, 4), glm::vec3(0, 1, 0));
	Gizmos::create();
}
void MainState::Update(double _dt) {
	m_camera->Update(_dt);
	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);
	glm::vec3 pos = m_camera->PickAgainstPlane((float)xpos, (float)ypos, glm::vec4(0, 1, 0, 0));
	mousePos = glm::vec2((int)pos.x, (int)pos.z);
	
}
void MainState::Draw()
{
	glClearColor(1, 1, 1, 1);
	Gizmos::clear();

	m_skybox->Draw(m_camera);

	glm::vec4 colour = glm::vec4(1, 1, 1, 1);
	glm::vec3 pos1 = glm::vec3(0, 0, 0);
	glm::vec3 pos2 = glm::vec3(0, 0, 0.95f);
	glm::vec3 pos3 = glm::vec3(0.95f, 0, 0);
	glm::vec3 pos4 = glm::vec3(0.95f, 0, 0.95f);


	Gizmos::addLine(pos1, glm::vec3(5, 0, 0), glm::vec4(0, 0, 1, 1));
	Gizmos::addLine(pos1, glm::vec3(0, 5, 0), glm::vec4(1, 0, 0, 1));
	Gizmos::addLine(pos1, glm::vec3(0, 0, 5), glm::vec4(0, 1, 0, 1));

	for (int x = 0; x < 10; x++)
	{
		pos1.x = 0.05f + x;
		pos2.x = 0.05f + x;
		pos3.x = 0.95f + x;
		pos4.x = 0.95f + x;
		for (int z = 0; z < 10; z++)
		{
			if (mousePos.x == x && mousePos.y == z)
			{
				colour.r = 0;
				colour.b = 0;
				Gizmos::addAABBFilled(glm::vec3(x + 0.5f, 0.5f, z + 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec4(0.3f));
			}
			else
			{
				colour.r = 1;
				colour.b = 1;
			}
			pos1.z = 0.05f + z;
			pos2.z = 0.95f + z;
			pos3.z = 0.05f + z;
			pos4.z = 0.95f + z;

			Gizmos::addLine(pos1, pos2, colour);
			Gizmos::addLine(pos1, pos3, colour);
			Gizmos::addLine(pos4, pos2, colour);
			Gizmos::addLine(pos4, pos3, colour);
		}
	}

	Gizmos::draw(m_camera->GetProjectionView());
}
void MainState::RefreshWindow()
{
	m_window = Game::Instance()->GetWindow();
	m_camera->SetInputWindow(m_window);
}
