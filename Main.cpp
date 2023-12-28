#include"libs.cpp"

bool fullscreen = false;

bool loadShaders(GLuint &program) 
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;
	
	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	// vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + "\n";
		}
	}
	else 
		printf("Error: Could not load vertex shaders, line 24");
	

	in_file.close();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();

	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR" << "\n";
		std::cout << infoLog;
		loadSuccess = false;
		printf("Error: Could not compile vertex shader, line 33");
	}


	temp = "";
	src = "";

	// frag

	in_file.open("fragment_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp)) {
			src += temp + "\n";
		}
	}
	else {
		loadSuccess = false;
		printf("Error: Could not load fragment shader, line 52");
	}


	in_file.close();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		loadSuccess = false;
		printf("Error: Could not compile fragment shader, line 63");
	}

	// program


	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		loadSuccess = false;
		printf("Error: Could not link program, line 84");
	}
	// end

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return loadSuccess;
}

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
			glfwSetWindowMonitor(window, nullptr, 10.0f , 50.0f, windowW, windowH, 0);
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


	GLuint core_program;
	if (!loadShaders(core_program))
		glfwTerminate();


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}