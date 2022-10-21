#include "Intro.h"

// vertex shader source, runs once per vertex
const char* c_vsSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"}\0";

// fragment shader source, runs once per pixel
const char* c_fsSource = "#version 330 core\n"
"out vec4 oColor;\n"
"uniform vec4 uColor;\n"
"void main() {\n"
"	oColor = uColor;\n"
"}\0";

int main(int argc, char** argv)
{	
	// init and configure glfw
	if (!glfwInit())
	{
		std::cout << "Failed to init glfw!\n";
		std::cin.get();
		exit(EXIT_FAILURE);
	}
	// use opengl version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// mac users
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// create our window
	const uint32_t c_windowWidth = 1080;
	const uint32_t c_windowHeight = 1080;
	GLFWwindow* win = glfwCreateWindow(c_windowWidth, c_windowHeight, "Hello Intro", nullptr, nullptr);
	if (!win)
	{
		std::cout << "Failed to create win\n";
		std::cin.get();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// tell opengl to render everything to this window
	glfwMakeContextCurrent(win);

	// load opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load glad\n";
		std::cin.get();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// map rendering to screen pixels
	glViewport(0, 0, c_windowWidth, c_windowHeight);

	// shader error variables
	const uint32_t bufferSize = 500;
	char log[bufferSize];
	int32_t status;

	// compile our vertex shader
	uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &c_vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	// check compilation
	if (!status)
	{
		glGetShaderInfoLog(vs, bufferSize, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}
	// compile our fragment shader
	uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &c_fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	// check compilation
	if (!status)
	{
		glGetShaderInfoLog(fs, 500, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}

	// create and link our shader program
	uint32_t shaderProg = glCreateProgram();
	glAttachShader(shaderProg, vs);
	glAttachShader(shaderProg, fs);
	glLinkProgram(shaderProg);
	glGetProgramiv(shaderProg, GL_LINK_STATUS, &status);
	//check linking
	if (!status)
	{
		glGetShaderInfoLog(shaderProg, 500, NULL, log);
		std::cout << log << std::endl;
		std::cin.get();
	}
	// delete intermediate shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	// create out vertex buffer layout
	uint32_t vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// positions in localized device coord
	float vertexPos[] = {
		-0.5f, -0.5f, 0.0f, 
		0.0f, 0.5f, 0.0f, 
		0.5f, -0.5f, 0.0f
	};
	// vertex buffer setup
	uint32_t vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), (void*)vertexPos, GL_STATIC_DRAW);
	// tell opengl how to interpret buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	// render variables
	glm::vec4 screenCol = { 0.25f, 0.45f, 0.65f, 1.0f };
	glm::vec4 triCol = { 1.0f, 0.0f, 0.0f, 1.0f };
	double lastFrame = 0.0f;
	// application loop
	while (!glfwWindowShouldClose(win))
	{
		// tick speed
		double currentFrame = glfwGetTime();
		double dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// clear the screen to the background color
		glClearColor(screenCol.r, screenCol.g, screenCol.b, screenCol.a);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind our vao
		glBindVertexArray(vao);

		// update our triangle
		triCol.r = glm::sin(currentFrame) / 2.0f + 0.5f;
		triCol.g = glm::cos(currentFrame) / 2.0f + 0.5f;

		// update the color uniform
		int32_t location = glGetUniformLocation(shaderProg, "uColor");
		glUniform4fv(location, 1, &triCol[0]);

		// render
		glUseProgram(shaderProg);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// swap front and back buffers
		glfwSwapBuffers(win);
		// see if any input has occured on our window
		glfwPollEvents();
	}
	// memory cleanup
	glDeleteProgram(shaderProg);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glfwTerminate();
	return 0;
}