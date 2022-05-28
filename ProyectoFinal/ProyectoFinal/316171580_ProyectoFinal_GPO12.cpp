#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

//Variables a ocupar para movimientos de los objetos
float rot = 0.0f;
float rotPuertaFachada = 0.0f;
float rotPuertaCuarto = 0.0f;
float posicionCajon1 = -10.5f;
float posicionCajon2 = 11.25f;
float posicionCajonSala = -24.0f;
float movPelotaX = 6.0f;
float movPelotaY = 14.4f;
float movPelotaZ = -7.5f;
float rotPelota = 0.0f;
float rotOso = 0.0f;
float rotTelefonoArriba = 0.0f;
float movOsoY = 19.05f;
bool animVentana1 = false;
bool animVentana2 = false;
bool animPuertaFachada1 = false;
bool animPuertaFachada2 = false;
bool animPuertaCuarto1 = false;
bool animPuertaCuarto2 = false;
bool animCajon11 = false;
bool animCajon12 = false;
bool animCajon21 = false;
bool animCajon22 = false;
bool pelotaEnMovimiento = false;
bool pelotaEnMovimiento2 = false;
bool movPelota1 = true;
bool movPelota2 = false;
bool movPelota3 = false;
bool movPelota4 = false;
bool movPelota5 = false;
bool movPelota6 = false;
bool movPelota7 = false;
bool movPelota8 = false;
bool osoEnMovimiento = false;
bool movOso1 = true;
bool movOso2 = false;
bool telefonoEnMovimiento = false;
bool movTelefono1 = true;
bool movTelefono2 = false;
bool animCajonSala1 = false;
bool animCajonSala2 = false;

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	//Carga de modelos 
	Model casa((char*)"Models/CasaChicas/casaFinal.obj");
	Model telefono((char*)"Models/Telefono/Phone2.obj");
	Model telefonoArriba((char*)"Models/Telefono/Phone1.obj");
	Model mesita((char*)"Models/Mesita/mesitaConTextura.obj");
	Model cama((char*)"Models/Cama/Bed3.obj");
	Model alfombra((char*)"Models/Alfombra2/alfombra2.obj");
	Model lampara((char*)"Models/lampara2/lampara2.obj");
	Model repisa((char*)"Models/Repisa/repisaLibros.obj");
	Model puertaCasa((char*)"Models/Casa/puerta_casa.obj");
	Model puertaCuarto((char*)"Models/Casa/puerta_cuarto.obj");
	Model ventana((char*)"Models/Casa/ventana.obj");
	Model ventanasCirculares((char*)"Models/Casa/ventana cirular.obj");
	Model ventanaConBarrotes((char*)"Models/Casa/ventana con barrotes.obj");
	Model barrotes((char*)"Models/Casa/barrotes.obj");
	Model mueble((char*)"Models/Mueble/mueble.obj");
	Model cajon1((char*)"Models/Mueble/cajon1.obj");
	Model cajon2((char*)"Models/Mueble/cajon2.obj");
	Model pelota((char*)"Models/Pelota/pelota.obj");
	Model oso((char*)"Models/Oso de peluche/oso.obj");
	Model sofa((char*)"Models/Sofa/sofa.obj");
	Model mesaSala((char*)"Models/MesaSala/mesaSala.obj");
	Model muebleSala((char*)"Models/Muebles Sala/muebleGrande.obj");
	Model cajonesMuebleSala((char*)"Models/Muebles Sala/cajones.obj");
	Model tele((char*)"Models/Tele/tele.obj");
	Model bocina((char*)"Models/Muebles Sala/bocina.obj");
	Model mesitaLampara((char*)"Models/mesitaSala/mesitaSala.obj");
	Model lamparaSala((char*)"Models/lamparaSala/lamparaSala.obj");

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"),1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);

		view = camera.GetViewMatrix();

		//Objetos 
		//Casa
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		casa.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Telefono
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(39.5f, 87.0f, 51.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		telefono.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		//Telefono Arriba
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(39.5f, 87.0f, 51.0f));
		model = glm::rotate(model, glm::radians(rotTelefonoArriba), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		telefonoArriba.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Mesita
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.0f, 15.15f, 10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		mesita.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Cama
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.2f, 1.4f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 10.5f, 5.3f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		cama.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Alfombra
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 13.5f, -3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		alfombra.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		//Lampara
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 23.55f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		lampara.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

		//Repisa
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.8f, 1.8f, 0.7f));
		model = glm::translate(model, glm::vec3(4.0f, 11.3f, 16.2f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		repisa.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Puerta entrada casa
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.82f, 5.33f, 7.69f));
		model = glm::rotate(model, glm::radians(rotPuertaFachada), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaCasa.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Puerta cuarto
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.01f, 1.0f));
		model = glm::translate(model, glm::vec3(-11.2f, 18.53f, -9.78f));
		model = glm::rotate(model, glm::radians(rotPuertaCuarto), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		puertaCuarto.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Barrotes
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		barrotes.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Mueble
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.75f, 14.39f, 5.2f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		mueble.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Cajón1 derecha
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posicionCajon1, 14.39f, 3.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		cajon1.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Cajón2 izquierda
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-6.45f, 14.39f, posicionCajon2));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		cajon2.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Oso
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.8f));
		model = glm::translate(model, glm::vec3(-12.8f, movOsoY, 1.9f));
		model = glm::rotate(model, glm::radians(rotOso), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		oso.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Sofa
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.8f));
		model = glm::translate(model, glm::vec3(-4.0f, 3.2f, 2.8f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		sofa.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Mesa de la sala
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.5f));
		model = glm::translate(model, glm::vec3(-4.0f, 1.22f, -0.2f));
		model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		mesaSala.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Mueble de la sala
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(-6.0f, 3.3f, -24.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		muebleSala.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Cajones del mueble de la sala
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.4f));
		model = glm::translate(model, glm::vec3(-6.0f, 3.3f, posicionCajonSala));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		cajonesMuebleSala.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Tele
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.8f));
		model = glm::translate(model, glm::vec3(-3.9f, 7.25f, -11.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		tele.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Bocina 1
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.25f));
		model = glm::translate(model, glm::vec3(-22.2f, 13.45f, -47.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		bocina.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Bocina 2
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.25f));
		model = glm::translate(model, glm::vec3(3.2f, 13.45f, -47.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		bocina.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Mesita de lámpara
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(3.7f, 4.3f, 3.7f));
		model = glm::translate(model, glm::vec3(0.9f, 0.05f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		mesitaLampara.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Lámpara
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.4f));
		model = glm::translate(model, glm::vec3(8.2f, 9.15f, 2.8f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		lamparaSala.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Ventana fachada
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.7f, 9.1f, -1.65f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.85); //Para translucidez
		ventana.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Ventanas circulares
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.85); //Para translucidez
		ventanasCirculares.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Ventana con barrotes 
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.85); //Para translucidez
		ventanaConBarrotes.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Pelota
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(movPelotaX, movPelotaY, movPelotaZ));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotPelota), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.8); //Para translucidez
		pelota.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);  
		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	//Para animación de objetos 
	if (keys[GLFW_KEY_R]) {
		animVentana1 = true;
	}

	if (keys[GLFW_KEY_F]) {
		animVentana2 = true;
	}

	if (keys[GLFW_KEY_T]) {
		animPuertaFachada1 = true;
	}

	if (keys[GLFW_KEY_G]) {
		animPuertaFachada2 = true;
	}

	if (keys[GLFW_KEY_Y]) {
		animPuertaCuarto1 = true;
	}

	if (keys[GLFW_KEY_H]) {
		animPuertaCuarto2 = true;
	}

	if (keys[GLFW_KEY_U]) {
		animCajon11 = true;
	}

	if (keys[GLFW_KEY_J]) {
		animCajon12 = true;
	}

	if (keys[GLFW_KEY_I]) {
		animCajon21 = true;
	}

	if (keys[GLFW_KEY_K]) {
		animCajon22 = true;
	}

	if (keys[GLFW_KEY_O])
	{
		pelotaEnMovimiento = true;
	}

	if (keys[GLFW_KEY_P])
	{
		pelotaEnMovimiento = false;
	}

	if (keys[GLFW_KEY_L])
	{
		osoEnMovimiento = true;
	}

	if (keys[GLFW_KEY_Z])
	{
		telefonoEnMovimiento = true;
	}

	if (keys[GLFW_KEY_X])
	{
		telefonoEnMovimiento = false;
	}

	if (keys[GLFW_KEY_C])
	{
		animCajonSala1 = true;
	}

	if (keys[GLFW_KEY_V])
	{
		animCajonSala2 = true;
	}

	//Movimiento de objetos 

	if (keys[GLFW_KEY_R])
	{
		if (animVentana1) {
			while (rot < 90) {
				rot += 0.1;
			}

		}
	}

	if (keys[GLFW_KEY_F])
	{
		if (animVentana2) {
			while (rot > 0) {
				rot -= 0.1;
			}
		}
	}

	if (keys[GLFW_KEY_T])
	{
		if (animPuertaFachada1) {
			while (rotPuertaFachada < 90) {
				rotPuertaFachada += 0.1;
			}

		}
	}

	if (keys[GLFW_KEY_G])
	{
		if (animPuertaFachada2) {
			while (rotPuertaFachada > 0) {
				rotPuertaFachada -= 0.1;
			}
		}
	}

	if (keys[GLFW_KEY_Y])
	{
		if (animPuertaCuarto1) {
			while (rotPuertaCuarto < 90) {
				rotPuertaCuarto += 0.01;
			}

		}
	}

	if (keys[GLFW_KEY_H])
	{
		if (animPuertaCuarto2) {
			while (rotPuertaCuarto > 0) {
				rotPuertaCuarto -= 0.01;
			}
		}
	}

	if (keys[GLFW_KEY_U])
	{
		if (animCajon11) {
			while (posicionCajon1 < -9.0) {
				posicionCajon1 += 0.01;
			}

		}
	}

	if (keys[GLFW_KEY_J])
	{
		if (animCajon12) {
			while (posicionCajon1 > -10.5) {
				posicionCajon1 -= 0.01;
			}
		}
	}

	if (keys[GLFW_KEY_I])
	{
		if (animCajon21) {
			while (posicionCajon2 < 11.25) {
				posicionCajon2 += 0.01;
			}

		}
	}

	if (keys[GLFW_KEY_K])
	{
		if (animCajon22) {
			while (posicionCajon2 > 9.3) {
				posicionCajon2 -= 0.01;
			}
		}
	}

	if (keys[GLFW_KEY_C])
	{
		if (animCajonSala1) {
			while (posicionCajonSala < -20.0) {
				posicionCajonSala += 0.01;
			}

		}
	}

	if (keys[GLFW_KEY_V])
	{
		if (animCajonSala2) {
			while (posicionCajonSala > -24.0f) {
				posicionCajonSala -= 0.01;
			}
		}
	}
}

void animacion(){
	if (pelotaEnMovimiento)
	{
		if (movPelota1)
		{
			movPelotaY += 0.1f;
			if (movPelotaY > 17.4f) {
				movPelota1 = false;
				movPelota2 = true;
			}
		}
		if (movPelota2)
		{
			movPelotaY -= 0.1f;
			movPelotaX -= 0.05f;
			if (movPelotaY < 14.5f && movPelotaX < 4.5f)
			{
				movPelota2 = false;
				movPelota3 = true;
			}
		}
		if (movPelota3)
		{
			movPelotaY += 0.2f;
			movPelotaX -= 0.1f;
			if (movPelotaY > 16.0f && movPelotaX < 3.0f)
			{
				movPelota3 = false;
				movPelota4 = true;
			}
		}
		if (movPelota4)
		{
			movPelotaY -= 0.2f;
			movPelotaX -= 0.1f;
			if (movPelotaY < 14.5f && movPelotaX < 1.5f)
			{
				movPelota4 = false;
				movPelota5 = true;
			}
		}
		if (movPelota5)
		{
			movPelotaY += 0.1f;
			movPelotaX -= 0.05f;
			if (movPelotaY > 15.0f && movPelotaX < 0.0f)
			{
				movPelota5 = false;
				movPelota6 = true;
			}
		}
		if (movPelota6)
		{
			movPelotaY -= 0.1f;
			movPelotaX -= 0.05f;
			if (movPelotaY < 14.5f && movPelotaX < -1.5f)
			{
				movPelota6 = false;
				movPelota7 = true;
			}
		}
		if (movPelota7)
		{
			rotPelota += 1.0f;//Z
			movPelotaX -= 0.01f;
			if (movPelotaX < -7.0f)
			{
				movPelota7 = false;
				movPelota8 = true;
			}
		}
		if (movPelota8) {
			rotPelota -= 3.0f;
			movPelotaX += 0.1f;
			if (movPelotaX > 6.0f) {
				movPelota8 = false;
				movPelota1 = true; 
			}
		}
	}
	
	if (osoEnMovimiento) {
		if (movOso1) {
			rotOso -= 1.0f;//x
			if (rotOso < -90.0f) {
				movOso1 = false;
				movOso2 = true;
			}
		}
		if (movOso2) {
			movOsoY -= 0.1f;
			if (movOsoY < 18.0f) {
				movOso2 = false;
			}
		}
	}

	if (telefonoEnMovimiento) {
		if (movTelefono1) {
			rotTelefonoArriba -= 1.0f;
			if (rotTelefonoArriba < -5.0) {
				movTelefono1 = false;
				movTelefono2 = true;
			}
		}
		if (movTelefono2) {
			rotTelefonoArriba += 1.0f;
			if (rotTelefonoArriba > 5.0) {
				movTelefono2 = false;
				movTelefono1 = true;
			}
		}
	}

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}