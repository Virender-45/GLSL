#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <math.h>

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
	// Initialize GLFW (a library for managing windows and OpenGL contexts)
	// Initialize GLFW
	glfwInit();

	// Set OpenGL version to 3.3 (major version 3, minor version 3)
	// Set OpenGL version to 3.3 (core profile)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Set OpenGL to use the core profile (modern OpenGL without deprecated functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window with width 600, height 600, and title "Rana"
	GLFWwindow* window = glfwCreateWindow(600, 600, "Virender", NULL, NULL);

	// Check if window creation was successful
	// Create a window with GLFW
	GLFWwindow* window = glfwCreateWindow(600, 600, "Rana", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); // Terminate GLFW before exiting
		return -1; // Return an error code
		glfwTerminate();
		return -1;
	}

	// Make the created window the current OpenGL context
	// Make the window the current OpenGL context
	glfwMakeContextCurrent(window);

	// Load OpenGL functions using GLAD
	gladLoadGL();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set the OpenGL viewport to match the window size (0,0 is the bottom-left corner)
	// Set viewport size
	glViewport(0, 0, 600, 600);

	// Set the background color to a dark blue shade
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	// Define the vertices of a triangle
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,  // Bottom-left
		 0.5f, -0.5f, 0.0f,  // Bottom-right
		 0.0f,  0.5f, 0.0f   // Top
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
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Clear the color buffer to apply the background color
	glClear(GL_COLOR_BUFFER_BIT);
	// Bind the VAO
	glBindVertexArray(VAO);

	// Swap buffers to display the cleared color on the window
	glfwSwapBuffers(window);
	// Bind the VBO and copy the vertex data into it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Keep the window open until the user closes it
	// Define how vertex attributes are interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Set the background color
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents(); // Process user inputs and window events
		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the shader program
		glUseProgram(shaderProgram);

		// Bind the VAO
		glBindVertexArray(VAO);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}

	// Destroy the created window and release resources
	// Cleanup: Delete buffers and the shader program
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate(); // Terminate GLFW before exiting
	glfwTerminate();

	return 0; // Return success
	return 0;
}