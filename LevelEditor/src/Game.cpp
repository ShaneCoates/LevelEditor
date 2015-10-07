#include "Game.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "GameStateManager.h"
#include "MainState.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb-master\stb_image.h>
#include <time.h>

Game* Game::m_instance = nullptr;

Game::Game() {
	m_instance = this;

	srand(time(NULL));
	currentFrame = 0;
	deltaTime = 0;
	lastFrame = 0;
	
	if (glfwInit() == false) {
		printf("Failed to initialise GLFW");
		return;
	}

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	m_gameWindow = glfwCreateWindow(mode->width, mode->height, "Level Editor - Shane Coates", glfwGetPrimaryMonitor(), nullptr);

	if (m_gameWindow == nullptr) {
		printf("Failed to create Game Window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_gameWindow);
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		printf("Failed to load OpenGL Functions");
		glfwDestroyWindow(m_gameWindow);
		glfwTerminate();
		return;
	}

	ImGui_ImplGlfwGL3_Init(m_gameWindow, true);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	m_gameStateManager = new GameStateManager();
	m_mainState = new MainState(m_gameWindow, m_gameStateManager);
	m_gameStateManager->RegisterState("Main", m_mainState);
	m_gameStateManager->Push("Main");

}
Game::~Game() {
	delete m_gameStateManager;
	glfwDestroyWindow(m_gameWindow);
	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();
}

void Game::Run() {
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (glfwWindowShouldClose(m_gameWindow) == false) {
		double dt = GetDeltaTime();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplGlfwGL3_NewFrame();
		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Separator();

		if (glfwGetKey(m_gameWindow, GLFW_KEY_F11))
		{
			ToggleFullscreen(m_fullscreen);
		}

		m_gameStateManager->Update(dt);
		m_gameStateManager->Draw();
		
		ImGui::Render();
		
		glfwSwapBuffers(m_gameWindow);
		glfwPollEvents();
	}
}

double Game::GetDeltaTime(){
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	return deltaTime;
}

Game* Game::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Game();
	}
	return m_instance;
}

GLFWwindow* Game::GetWindow()
{
	return m_gameWindow;
}

void Game::ToggleFullscreen(bool _fullscreen, int _width, int _height)
{
	if (m_gameWindow != nullptr)
	{
		glfwDestroyWindow(m_gameWindow);
	}
	
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	if (_fullscreen)
	{
		m_gameWindow = glfwCreateWindow(mode->width, mode->height, "Level Editor - Shane Coates", glfwGetPrimaryMonitor(), nullptr);
	}
	else
	{
		m_gameWindow = glfwCreateWindow(_width, _height, "Level Editor - Shane Coates", nullptr, nullptr);
	}
	if (m_gameWindow == nullptr) {
		printf("Failed to create Game Window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_gameWindow);
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		printf("Failed to load OpenGL Functions");
		glfwDestroyWindow(m_gameWindow);
		glfwTerminate();
		return;
	}
	ImGui_ImplGlfwGL3_Init(m_gameWindow, true);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_fullscreen = !m_fullscreen;
	if (m_mainState != nullptr)
	{
		m_mainState->RefreshWindow();
	}
	
}
