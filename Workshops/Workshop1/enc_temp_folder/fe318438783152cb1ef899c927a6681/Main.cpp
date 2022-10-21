#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

int main()
{
	if (!glfwInit())
		return 1;
	// version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const uint32_t c_windowWidth = 1080;
	const uint32_t c_windowHeight = 1080;
	GLFWwindow* win = glfwCreateWindow(c_windowWidth, c_windowHeight, "Intro Workshop", nullptr, nullptr);
	if (!win)
	{
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(win);
	glViewport(0, 0, c_windowWidth, c_windowHeight);


	while (!glfwWindowShouldClose(win))
	{

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}