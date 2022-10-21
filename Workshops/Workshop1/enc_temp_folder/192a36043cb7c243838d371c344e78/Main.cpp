#include "Intro.h"

int main(int argc, char** argv)
{
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw\n";
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	// version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	const uint32_t c_windowHeight = 1080;
	const uint32_t c_windowWidth = 1080;
	GLFWwindow* window = glfwCreateWindow(c_windowWidth, c_windowHeight, "Hello Intro OpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create glfw window\n";
		std::cin.get();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init glad!";
		std::cin.get();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glViewport(0, 0, c_windowHeight, c_windowHeight);



	while (!glfwWindowShouldClose(window))
	{

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}