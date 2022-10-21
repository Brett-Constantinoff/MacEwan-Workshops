#include "Intro.h"

const char* c_vsSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"}\0";

const char* c_fsSource = "#version 330 core\n"
"out vec4 oColor;\n"
"void main() {\n"
"	oColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\0";

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

	char log[500];
	int32_t status;
	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &c_vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(vs, 500, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}

	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &c_fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fs, 500, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}

	uint32_t shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(fs, 500, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	uint32_t vao;
	glGenVertexArrays(1, &vao);

	float vertexPos[] = {
		-0.5f, 0.0f, 0.0f, 
		0.0f, 0.5f, 0.0f,
		0.5f ,0.0f, 0.0f
	};
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), (void*)vertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec4 screenColor = { 0.25f, 0.35f, 0.60f, 1.0f };
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(screenColor.r, screenColor.g, screenColor.b, screenColor.a);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return 0;
}