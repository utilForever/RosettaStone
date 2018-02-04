/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ GUI program.
> Created Time: 2018/02/04
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include <cstdlib>

void Setup(GLFWwindow* window);
void Render(ImDrawData* drawData);

int main()
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	static GLFWwindow* window{ glfwCreateWindow(800, 600, "Hearthstone++ simple GUI", nullptr, nullptr };

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// Close window on pressing ESC
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});

	return 0;
}