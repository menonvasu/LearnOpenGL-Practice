#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// glfw: executes on window size change
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// process all input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.533, 0.431, 0.012, 1.0);\n"
"}\n\0";
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.659, 0.043, 0.267, 1.0);\n"
"}\n\0";

int main() {
	//initialize glfw and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//GLAD:load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//build and compile shader program
	//--------------------------------
	//vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//fragment shader 
	unsigned int fragmentShaderHouse = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderHouse, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShaderHouse);
	//check for errors
	glGetShaderiv(fragmentShaderHouse, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderHouse, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	unsigned int fragmentShaderRoof = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRoof, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShaderRoof);
	//check for errors
	glGetShaderiv(fragmentShaderRoof, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderRoof, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//link shaders
	unsigned int shaderProgramHouse = glCreateProgram();
	glAttachShader(shaderProgramHouse, vertexShader);
	glAttachShader(shaderProgramHouse, fragmentShaderHouse);
	glLinkProgram(shaderProgramHouse);
	// check for linking errors
	glGetProgramiv(shaderProgramHouse, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramHouse, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(fragmentShaderHouse);

	unsigned int shaderProgramRoof = glCreateProgram();
	glAttachShader(shaderProgramRoof, vertexShader);
	glAttachShader(shaderProgramRoof, fragmentShaderRoof);
	glLinkProgram(shaderProgramRoof);
	glGetProgramiv(shaderProgramRoof, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramRoof, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderRoof);

	//set up vertex data (and buffer(s)) and configure vertex attributes
	float houseBase[] = {
		0.5f, 0.5f, 0.0f, //top right
		0.5f, -0.5f, 0.0f, //bottom right
		-0.5f, -0.5f, 0.0f, //bottom left
		-0.5f, 0.5f, 0.0f //top left
	};
	unsigned int houseIndices[] = {
		0, 1, 3,
		1, 2, 3
	};

	float roof[] = {
		-0.5f, 0.5f, 0.0f, //left
		0.5f, 0.5f, 0.0f, //right
		0.0f, 0.8f, 0.0f //top
	};

	unsigned int VBOs[2], VAOs[2], EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(1, &EBO);

	// House base setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(houseBase), houseBase, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(houseIndices), houseIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Roof setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(roof), roof, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//basic render loop
	while (!glfwWindowShouldClose(window)) {
		//input
		processInput(window);
		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw house base
		glUseProgram(shaderProgramHouse);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//draw second triangle
		glUseProgram(shaderProgramRoof);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//de-allocate resources
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgramHouse);
	glDeleteProgram(shaderProgramRoof);
	
	//termination
	glfwTerminate();
	return 0;
}