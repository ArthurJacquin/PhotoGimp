
// GLEW_STATIC force le linkage statique
// c-a-d que le code de glew est directement injecte dans l'executable
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLShader.h"

#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32s.lib")			// glew32.lib si pas GLEW_STATIC
#pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
#elif defined(__linux__)
#endif

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Input.h"

//Variables globales
GLShader BasicShader;
GLuint VAO;
GLuint VBO;
GLuint IBO;
Input input;
std::vector<Vertex> vertices;

int width, height;


bool Initialise() {

	//Init GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		std::cout << "erreur d'initialisation de GLEW!"
			<< std::endl;
	}

	std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer : " << glGetString(GL_RENDERER) << std::endl;

	//Init shaders
	BasicShader.LoadVertexShader("Basic.vs");
	BasicShader.LoadFragmentShader("Basic.fs");
	BasicShader.Create();

	//Init Program
	GLuint64 BasicProgram = BasicShader.GetProgram();
	glUseProgram(BasicProgram);

	//Vertex array
	const Vertex triangle[] = {
		Vertex(-0.5f, -0.5f, 1.f, 0.f, 0.f),
		Vertex(-0.5f, +0.5f, 0.f, 1.f, 0.f),
		Vertex(+0.5f, +0.5f, 0.f, 0.f, 1.f),
		Vertex(+0.5f, -0.5f, 1.f, 0.f, 0.f)
	};

	//Indices array
	const unsigned short indices[] = {
		0, 1, 2,
		0, 2, 3
	};


#ifdef WIN32 
	wglSwapIntervalEXT(1);
#endif 

	return true;
}

void updateBuffer()
{
	//Cr�ation VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Cr�ation VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	//Cr�ation IBO
	/*glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3 * 2, indices, GL_STATIC_DRAW);
	*/
	//Position
	int loc_position = glGetAttribLocation(BasicShader.GetProgram(), "a_position");
	glVertexAttribPointer(loc_position, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glEnableVertexAttribArray(loc_position);

	//Color
	int loc_color = glGetAttribLocation(BasicShader.GetProgram(), "a_color");
	glVertexAttribPointer(loc_color, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, r));
	glEnableVertexAttribArray(loc_color);
	
	//D�sactivation des buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Terminate() 
{
	BasicShader.Destroy();
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Display(GLFWwindow* window)
{
	glfwGetWindowSize(window, &width, &height);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Desactive le "scissoring"
	glDisable(GL_SCISSOR_TEST);
	// Defini le viewport en pleine fenetre
	glViewport(0, 0, width, height);

	//Active VAO -> Render -> reset VAO
	glBindVertexArray(VAO);

	//glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_SHORT, nullptr);
	glDrawArrays(GL_POINTS, 0, vertices.size());

	glBindVertexArray(0);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// toutes nos initialisations vont ici
	Initialise();

	//Input
	glfwSetMouseButtonCallback(window, &input.mouse_button_callback);
	glfwSetKeyCallback(window, &input.keyboard_button_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwGetFramebufferSize(window, &width, &height);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		if (vertices.size() > 0)
		{
			updateBuffer();
		}
		/* Render here */
		Display(window);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		/*
		for (std::vector<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
			std::cout << *i  << std::endl;*/

	}

	// ne pas oublier de liberer la memoire etc...
	Terminate();

	glfwTerminate();
	return 0;
}