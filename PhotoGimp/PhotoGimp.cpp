#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GLShader.h"

#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32s.lib")	
#pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
#elif defined(__linux__)
#endif

#include <iostream>
#include <vector>
#include "Vertex.h"
#include "Input.h"

#include "imgui.h"
#include "examples\\imgui_impl_opengl3.h"
#include "examples\\imgui_impl_glfw.h"

#include "imgui.cpp"
#include "examples\\imgui_impl_glfw.cpp"
#include "examples\\imgui_impl_opengl3.cpp"
#include "imgui_draw.cpp"
#include "imgui_widgets.cpp"
#include "imgui_demo.cpp"

#include "Color.h"

const char* glsl_version = "#version 150";

//Variables globales
GLShader BasicShader;
GLuint VAO;
GLuint VBO;
Input input;
//tableau de positions du tableau en cours
std::vector<Vertex> vertices;
std::vector<Vertex> verticesToDraw;
std::vector<int> shapesSizes; 
std::vector<Vertex> tabMenuFormeVertices;
std::vector<Vertex> tabMenuFenetreVertices;

//variables pour gui
Color choosedColor(1.f, 1.f, 1.f);
bool clickMenuForme = false;
bool clickMenuFenetre = false;
bool clickMenuRemplissage = false;
bool clickDelete = false;
bool clickMenuEnter = false;

int width = 1024;
int height = 512;

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
	/*
#ifdef WIN32 
	wglSwapIntervalEXT(1);*/
//#endif 

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
	
	//Position
	int loc_position = glGetAttribLocation(BasicShader.GetProgram(), "a_position");
	glVertexAttribPointer(loc_position, 2, GL_DOUBLE, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(loc_position);
	
	//Color
	int loc_color = glGetAttribLocation(BasicShader.GetProgram(), "a_color");
	glVertexAttribPointer(loc_color, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, r));
	glEnableVertexAttribArray(loc_color);
	
	//D�sactivation des buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terminate() 
{
	BasicShader.Destroy();
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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

	glLineWidth(5.f);
	int currentId = 0;
	for (int i = 0; i < shapesSizes.size(); ++i)
	{
		glDrawArrays(GL_LINE_LOOP, currentId, shapesSizes[i]);
		currentId += shapesSizes[i];
	}

	glEnable(GL_PROGRAM_POINT_SIZE);
	glDrawArrays(GL_POINTS, currentId, vertices.size() - currentId);

	glBindVertexArray(0);
}

void InitialiseGUI(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsClassic();
}

void displayGUI()
{
	// feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(220, 550));
	// render your GUI
	ImGui::Begin("PhotoGimp", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::TextColored(ImVec4(0.9, 0.1, 0.1, 1.0), "  Bienvenue dans PhotoGimp ");
	ImGui::Text(" ");
	ImGui::Text("Vous pouvez creer plusieurs");
	ImGui::Text("formes et les decouper avec");
	ImGui::Text("      des fenetres");
	ImGui::Text(" ");
	ImGui::Text(" -------------------------  ");
	ImGui::Text(" ");
	ImGui::Text("Pour ajouter un point : ");
	ImGui::Text("     click gauche ");
	ImGui::Text("Pour supprimer un point : ");
	ImGui::Text("     click droit ");
	ImGui::Text(" ");
	ImGui::Text(" -------------------------  ");
	ImGui::Text("  Choississez une couleur");
	ImGui::Text("  avant de tracer la forme");
	ImGui::Text("       ou la fenetre");
	ImGui::Text(" ");
	static float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (ImGui::ColorEdit3("Color", color))
	{
		std::cerr << color[0] << std::endl;
		choosedColor = color;
	}

	ImGui::Text(" ");
	if (ImGui::Button("Tracer une forme"))
	{
		clickMenuForme = true;
	}

	if (ImGui::Button("Tracer une fenetre"))
	{
		clickMenuFenetre = true;
	}

	if (ImGui::Button("Decouper !"))
	{
		clickMenuEnter = true;
		input.decoupeForme();
	}

	if (ImGui::Button("Remplir !"))
	{
		clickMenuRemplissage = true;
		input.remplirForme();
	}

	ImGui::Text(" ");
	ImGui::Text(" -------------------------  ");
	ImGui::Text(" ");
	if (ImGui::Button("Tout effacer"))
	{
		clickDelete = true;
		input.deleteVertex();
	}
	//choosedColor = color;
	ImGui::End();

	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1024, 600, "PhotoGimp", NULL, NULL);
	InitialiseGUI(window);

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

		displayGUI();
		input.waitForBool();

		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
		/*
		for (std::vector<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); ++i)
		*/
		//std::cout << sizeof(Vertex) * vertices.size() << std::endl;

	}

	// ne pas oublier de liberer la memoire etc...
	Terminate();

	glfwTerminate();
	return 0;
}

