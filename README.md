Step-by-Step Dependencies
glfwInit();

Must be the first step because it initializes the GLFW library.
If you try to create a window before calling this, it will fail.
Setting OpenGL Version and Profile (glfwWindowHint)

These hints must be set before creating the window.
If set afterward, they won't take effect.
GLFWwindow* window = glfwCreateWindow(...)

Must come after glfwInit() and the window hints.
If window creation fails, there is no point in continuing.
glfwMakeContextCurrent(window);

The OpenGL context must be made current before loading OpenGL functions (next step).
gladLoadGL();

Loads OpenGL functions dynamically.
If you call OpenGL functions before loading them, the program will crash.
glViewport(0, 0, 600, 600);

Defines the rendering area.
If omitted, OpenGL might use a default value, but it’s good practice to specify it.
Setting and Clearing Background (glClearColor, glClear)

Must be done after OpenGL has been initialized.
Otherwise, the commands won't affect the rendering.
glfwSwapBuffers(window);

Swaps the color buffers to display the rendered frame.
If you skip this, you might not see any rendering output.
Render Loop (while (!glfwWindowShouldClose(window)))

Needed to keep the window open and responsive.
If skipped, the window will close immediately.
Cleanup (glfwDestroyWindow, glfwTerminate)

Done after the loop to properly release resources.
If skipped, memory leaks might occur.
Conclusion
Yes, the order matters because each step depends on previous ones. Changing the order might lead to:

Crashes (e.g., calling OpenGL functions before initializing GLAD).
Unresponsive window (e.g., missing event polling in the loop).
Incorrect rendering (e.g., setting the viewport at the wrong time).