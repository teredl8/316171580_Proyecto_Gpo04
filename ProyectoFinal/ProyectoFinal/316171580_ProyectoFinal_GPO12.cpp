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

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
//glm::vec3 lightPos1(3.0f, 0.0f, 3.0f);
//glm::vec3 lightPos2(-3.0f, 0.0f, 3.0f);
//glm::vec3 lightPos3(3.0f, 0.0f, -3.0f);
//glm::vec3 lightPos4(-3.0f, 0.0f, -3.0f);
bool active;

// Positions of the point lights
//glm::vec3 pointLightPositions[] = {
//	glm::vec3(3.0f,0.0f, 3.0f),
//	glm::vec3(-3.0f,0.0f, 3.0f),
//	glm::vec3(3.0f,0.0f,  -3.0f),
//	glm::vec3(-3.0f,0.0f, -3.0f)
//};

float rot = 0.0f;
float rotPuertaFachada = 0.0;
float rotPuertaCuarto = 0.0;
bool animVentana1 = false;
bool animVentana2 = false;
bool animPuertaFachada1 = false;
bool animPuertaFachada2 = false;
bool animPuertaCuarto1 = false;
bool animPuertaCuarto2 = false;

//Posición SpotLight
glm::vec3 spotLightPosition(0.0f, 0.0f, 0.0f);

//Dirección SpotLight
glm::vec3 spotLightDirection(1.0f, 1.0f, 1.0f);


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



glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);


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
	
	Model casa((char*)"Models/Casa/casaChicas.obj");
	Model telefono((char*)"Models/Phone_/Phone2.obj");
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

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f);


		//// Point light 1
	 //   glm::vec3 lightColor1;
		//lightColor1.x= abs(sin(glfwGetTime() *Light1.x));
		//lightColor1.y= abs(sin(glfwGetTime() *Light1.y));
		//lightColor1.z= sin(glfwGetTime() *Light1.z);

		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor1.x,lightColor1.y, lightColor1.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor1.x,lightColor1.y,lightColor1.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.075f);



		//// Point light 2
		//glm::vec3 lightColor2;
		//lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		//lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		//lightColor2.z = sin(glfwGetTime() * Light2.z);

		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.045f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.075f);

		//// Point light 3
		//glm::vec3 lightColor3;
		//lightColor3.x = abs(sin(glfwGetTime() * Light3.x));
		//lightColor3.y = abs(sin(glfwGetTime() * Light3.y));
		//lightColor3.z = sin(glfwGetTime() * Light3.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.045f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.075f);

		//// Point light 4
		//glm::vec3 lightColor4;
		//lightColor4.x = abs(sin(glfwGetTime() * Light4.x));
		//lightColor4.y = abs(sin(glfwGetTime() * Light4.y));
		//lightColor4.z = sin(glfwGetTime() * Light4.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.045f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.075f);

		// SpotLight
		/*glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), spotLightPosition.x, spotLightPosition.y, spotLightPosition.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), spotLightDirection.x, spotLightDirection.y, spotLightDirection.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"),1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));*/

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


		//Carga de modelo 
		view = camera.GetViewMatrix();

		//Casa
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		casa.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Telefono
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.2f));
		model = glm::translate(model, glm::vec3(40.0f, 87.0f, 51.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);
		telefono.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);

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
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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



		glEnable(GL_BLEND);//Activa la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Ventana fachada
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(10.7f, 9.1f, -1.65f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 0.0, 0.85); //Para translucidez
		ventana.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Ventanas circulares
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 0.0, 0.85); //Para translucidez
		ventanasCirculares.Draw(lightingShader);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Ventana con barrotes 
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 0.0, 0.85); //Para translucidez
		ventanaConBarrotes.Draw(lightingShader);
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

		//// Set matrices
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		//model = glm::mat4(1);
		//model = glm::translate(model, lightPos1);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//// Draw the light object (using light's vertex attributes)
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(VAO);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		//glBindVertexArray(0);



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

	/*if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
		pointLightPositions[1].x += 0.01f;
		pointLightPositions[2].x += 0.01f;
		pointLightPositions[3].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
		pointLightPositions[1].x -= 0.01f;
		pointLightPositions[2].x -= 0.01f;
		pointLightPositions[3].x -= 0.01f;
	}*/

	//if (keys[GLFW_KEY_Y])
	//{
	//	pointLightPositions[0].y += 0.01f;
	//	pointLightPositions[1].y += 0.01f;
	//	pointLightPositions[2].y += 0.01f;
	//	pointLightPositions[3].y += 0.01f;
	//}

	//if (keys[GLFW_KEY_H])
	//{
	//	pointLightPositions[0].y -= 0.01f;
	//	pointLightPositions[1].y -= 0.01f;
	//	pointLightPositions[2].y -= 0.01f;
	//	pointLightPositions[3].y -= 0.01f;
	//}
	//if (keys[GLFW_KEY_U])
	//{
	//	pointLightPositions[0].z -= 0.1f;
	//	pointLightPositions[1].z -= 0.1f;
	//	pointLightPositions[2].z -= 0.1f;
	//	pointLightPositions[3].z -= 0.1f;
	//}
	//if (keys[GLFW_KEY_J])
	//{
	//	pointLightPositions[0].z += 0.01f;
	//	pointLightPositions[1].z += 0.01f;
	//	pointLightPositions[2].z += 0.01f;
	//	pointLightPositions[3].z += 0.01f;
	//}

	/*if (keys[GLFW_KEY_R])
	{
		spotLightPosition.x += 0.01f;
	}

	if (keys[GLFW_KEY_F])
	{
		spotLightPosition.x -= 0.01f;
	}

	if (keys[GLFW_KEY_I])
	{
		spotLightPosition.y += 0.01f;
	}

	if (keys[GLFW_KEY_K])
	{
		spotLightPosition.y -= 0.01f;
	}

	if (keys[GLFW_KEY_O])
	{
		spotLightPosition.z += 0.01f;
	}

	if (keys[GLFW_KEY_L])
	{
		spotLightPosition.z -= 0.01f;
	}

	if (keys[GLFW_KEY_X])
	{
		spotLightDirection.x += 0.01f;
	}

	if (keys[GLFW_KEY_Z])
	{
		spotLightDirection.x -= 0.01f;
	}
	
	if (keys[GLFW_KEY_V])
	{
		spotLightDirection.y += 0.01f;
	}

	if (keys[GLFW_KEY_C])
	{
		spotLightDirection.y -= 0.01f;
	}

	if (keys[GLFW_KEY_N])
	{
		spotLightDirection.z += 0.01f;
	}

	if (keys[GLFW_KEY_B])
	{
		spotLightDirection.z -= 0.01f;
	}
	*/

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

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.941f, 0.278f, 0.882f);
			Light2 = glm::vec3(0.0f, 1.0f, 0.0f);
			Light3 = glm::vec3(0.0f, 0.0f, 1.0f);
			Light4 = glm::vec3(1.0f, 0.0f, 1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
			Light2 = glm::vec3(0);
			Light3 = glm::vec3(0);
			Light4 = glm::vec3(0);
		}
	}

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