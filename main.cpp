#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader Source Code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos, 1.0);\n"
"}\0";

// Fragment Shader Source Code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main() {
	// Initialize GLFW
	glfwInit();


	// Set OpenGL version to 3.3 (core profile)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window with GLFW
	GLFWwindow* window = glfwCreateWindow(600, 600, "Rana", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window the current OpenGL context
	glfwMakeContextCurrent(window);

	// Load OpenGL functions using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set viewport size
	glViewport(0, 0, 600, 600);

	// Define the vertices of a triangle
	GLfloat vertices[] = {
		//for single triangle
		
		 // -0.5f, -0.5f, 0.0f,  // Bottom-left
		 // 0.5f, -0.5f, 0.0f,  // Bottom-right
		 // 0.0f,  0.5f, 0.0f   // Top
		 

		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower left corner
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower right corner
		 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	//upper corner
		 -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
		 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner right
		 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f	//inner down
	};

	GLuint indices[] = {
		0, 3, 5, //lower left triangle
		3, 2, 4, //lower right triangle	
		5 ,4, 1	//upper triangle 
	};

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Link shaders into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete shaders after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create VAO (Vertex Array Object) and VBO (Vertex Buffer Object)
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the VAO
	glBindVertexArray(VAO);

	// Bind the VBO and copy the vertex data into it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Define how vertex attributes are interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Set the background color
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program
		glUseProgram(shaderProgram);

		// Bind the VAO
		glBindVertexArray(VAO);

		// Draw the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Cleanup: Delete buffers and the shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// Destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}