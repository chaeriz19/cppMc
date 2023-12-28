#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

bool fullscreen = false;


void ToggleFullscreen(GLFWwindow* window) {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!fullscreen) {
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else {
		const int windowW = 1280;
		const int windowH = 720;
		
		if (glfwGetWindowMonitor(window) != nullptr) {
			glfwSetWindowMonitor(window, nullptr, 150, 150, windowW, windowH, 0);
		}
	}
	fullscreen = !fullscreen;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		ToggleFullscreen(window);
		printf("Toggle fullscreen");
	}
}

int main() {
	if (!glfwInit()) {
		printf("Failed to init glfw");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int windowW = 1280;
	const int windowH = 720;

	const char* windowT = "Dev";

	GLFWwindow* window = glfwCreateWindow(
		windowW,
		windowH,
		windowT,
		NULL,
		NULL
	);
	if (window == nullptr) {
		printf("Failed to create window");
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, KeyCallback);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowW, windowH);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}