#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "/Programming/GLSL/Header Files/EBO.h"
#include "/Programming/GLSL/Header Files/shaderClass.h"
#include "/Programming/GLSL/Header Files/VBO.h"
#include "/Programming/GLSL/Header Files/VAO.h"


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

	Shader shaderProgram("default.vert", "default.frag");

	// Define the vertices of a triangle
	GLfloat vertices[] = {
		//for single triangle
		/*
		-0.5f, -0.5f, 0.0f,  // Bottom-left
		 0.5f, -0.5f, 0.0f,  // Bottom-right
		 0.0f,  0.5f, 0.0f   // Top
		 */

		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower left corner
		 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower right corner
		 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	//upper corner
		 - 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner left
		 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //inner right
		 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f	//inner down
	};

	GLfloat indices[] = {
		0, 3, 5, //lower left triangle
		3, 2, 4, //lower right triangle	
		5 ,4, 1	//upper triangle
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Set the background color to a dark blue shade
		glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

		// Clear the color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		VAO1.Bind();

		// Draw the triangle
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);

		// Poll for events
		glfwPollEvents();
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	// Destroy the window and terminate GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
