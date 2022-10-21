#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

const char* c_vsSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"		gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* c_fsSource = "#version 330 core\n"
"uniform vec4 uColor;\n"
"out vec4 oFragColor;\n"
"void main() {\n"
"		oFragColor = vec4(uColor);\n"
"}\0";

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
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return 3;
	}
	glViewport(0, 0, c_windowWidth, c_windowHeight);

	char log[500];
	int32_t success;

	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &c_vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, sizeof(log), NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
		return 4;
	}

	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &c_fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, sizeof(log), NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
		return 5;
	}

	uint32_t shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vs);
	glAttachShader(shaderProg, fs);
	glLinkProgram(shaderProg);
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, sizeof(log), NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
		return 6;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertexPos[] = {
		-0.5f, -0.5f, 0.0f, 
		0.0f, 0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f
	};
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec4 screenColor = { 0.25f, 0.30f, 0.60f, 1.0f };
	glm::vec4 triColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	double lastFrame = 0.0f;
	while (!glfwWindowShouldClose(win))
	{
		double currentFrame = glfwGetTime();
		double dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(screenColor.r, screenColor.g, screenColor.b, screenColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(shaderProg);

		double rVal = glm::sin(currentFrame) / 2.0f + 0.5f;
		triColor.r = rVal;

		int32_t result = glGetUniformLocation(shaderProg, "uColor");
		glUniform4f(result, triColor.r, triColor.g, triColor.b, triColor.a);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProg);
	glfwTerminate();
	return 0;
}