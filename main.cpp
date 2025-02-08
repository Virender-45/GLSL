#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	// Initialize GLFW (a library for managing windows and OpenGL contexts)
	glfwInit();

	// Set OpenGL version to 3.3 (major version 3, minor version 3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Set OpenGL to use the core profile (modern OpenGL without deprecated functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFW window with width 600, height 600, and title "Rana"
	GLFWwindow* window = glfwCreateWindow(600, 600, "Rana", NULL, NULL);

	// Check if window creation was successful
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); // Terminate GLFW before exiting
		return -1; // Return an error code
	}

	// Make the created window the current OpenGL context
	glfwMakeContextCurrent(window);

	// Load OpenGL functions using GLAD
	gladLoadGL();

	// Set the OpenGL viewport to match the window size (0,0 is the bottom-left corner)
	glViewport(0, 0, 600, 600);

	// Set the background color to a dark blue shade
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

	// Clear the color buffer to apply the background color
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap buffers to display the cleared color on the window
	glfwSwapBuffers(window);

	// Keep the window open until the user closes it
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents(); // Process user inputs and window events
	}

	// Destroy the created window and release resources
	glfwDestroyWindow(window);
	glfwTerminate(); // Terminate GLFW before exiting

	return 0; // Return success
}
