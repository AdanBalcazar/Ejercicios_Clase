/*----------------------------------------------------------------------------------*/
/*-----------------------------------  Práctica 7 ----------------------------------*/
/*-----------------------------------    2019-2   ----------------------------------*/
/*------------- Computación Gráfica e Interacción Humano Computadora ---------------*/

/*------------- Balcázar Rodríguez Adan Alí ---------------*/
/*-------------- Visual Studio Versión 2017 ---------------*/

/*--------------------- Instructivo: ----------------------*/
/*
Con las teclas del teclado se puede mover a todo el sistema:
	D: Mueve el sistema a la izquierda
	A: Mueve el sistema a la derecha
	W: Acerca el sistema
	S: Aleja el sistema
	Flecha abajo: Rota el sistema hacia enfrente
	Flecha arriba: Rota el sistema hacia atras
	AvPág: Mueve el sistema hacia abajo
	RePág: Mueve el sistema hacia arriba

Con el Mouse se puede mover la cámara desde la cual se observa el sistema
	Al mover el mouse a la derecha, la cámara gira a la derecha
	Al mover el mouse a la izquierda, la cámara gira a la izquierda
	Al mover el mouse hacia arriba, la cámara gira hacia arriba
	Al mover el mouse hacia abajo, la cámara gira hacia abajo
*/

#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;

float	sol = 0.0f,
mercurio = 0.0f,
venus = 0.0f,
tierra = 0.0f,
lunaTierra = 0.0f,
marte = 0.0f,
luna1Marte = 0.0f,
luna2Marte = 0.0f,
jupiter = 0.0f,
luna1Jupiter = 0.0f,
luna2Jupiter = 0.0f,
luna3Jupiter = 0.0f,
luna4Jupiter = 0.0f,
saturno = 0.0f,
anillo1Saturno = 0.0f,
anillo2Saturno = 0.0f,
urano = 0.0f,
luna1Urano = 0.0f,
luna2Urano = 0.0f,
neptuno = 0.0f,
lunaNeptuno = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Normals
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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.25f;
	mercurio += 0.46f;
	venus += 0.425f;
	tierra += 0.36f;
	lunaTierra += 0.345f;
	marte += 0.275f;
	luna1Marte += 0.15f;
	luna2Marte += 0.225f;
	jupiter += 0.2f;
	luna1Jupiter += 0.1f;
	luna2Jupiter += 0.05f;
	luna3Jupiter += 0.125f;
	luna4Jupiter += 0.09f;
	saturno += 0.165f;
	anillo1Saturno += 0.075f;
	anillo2Saturno += 0.11f;
	urano += 0.125f;
	luna1Urano += 0.04f;
	luna2Urano += 0.06f;
	neptuno += 0.09f;
	lunaNeptuno += 0.025f;
}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos);

	// create transformations and Projection

	glm::mat4 temp01 = glm::mat4(1.0f);     //Temporal

	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);

	glBindVertexArray(VAO);


	//Colocar código aquí
	
	//Mercurio
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(3, 0, 0));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.885f, 0.670f, 0.415f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Venus
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(4.5, 0, 0));
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.39f, 0.39f, 0.39f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.980f, 0.533f, 0.115f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Tierra
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(6.5, 0, 0));
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.45f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.058f, 0.36f, 0.95f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna de la Tierra
	model = temp01;
	model = glm::rotate(model, glm::radians(lunaTierra), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.6, 0, 0));
	model = glm::rotate(model, glm::radians(lunaTierra), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Marte
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(8.3, 0, 0));
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.32f, 0.32f, 0.32f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.95f, 0.02f, 0.03f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 1 de Marte
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Marte), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(-0.41, 0, 0));
	model = glm::rotate(model, glm::radians(luna1Marte), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.055f, 0.055f, 0.055f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 2 de Marte
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Marte), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.45, 0, 0.15));
	model = glm::rotate(model, glm::radians(luna2Marte), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.026f, 0.026f, 0.026f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Júpiter
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(11.25, 0, 0));
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.84f, 0.84f, 0.84f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.95f, 0.895f, 0.35f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 1 de Júpiter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(-0.97, 0.12, -0.32));
	model = glm::rotate(model, glm::radians(luna1Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.055f, 0.055f, 0.055f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 2 de Júpiter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.95, 0, 0.27));
	model = glm::rotate(model, glm::radians(luna2Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.026f, 0.026f, 0.026f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 3 de Júpiter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna3Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(-1.05, 0.25, 0.12));
	model = glm::rotate(model, glm::radians(luna3Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.064f, 0.064f, 0.064f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 4 de Júpiter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna4Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.995, -0.42, 0.01));
	model = glm::rotate(model, glm::radians(luna4Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.036f, 0.036f, 0.036f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Saturno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(14.3, 0, 0));
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.84f, 0.84f, 0.84f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.62f, 0.505f, 0.403f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Anillo 1 de Saturno
	model = temp01;
	model = glm::rotate(model, glm::radians(anillo1Saturno), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1, 0, 1));
	model = glm::scale(model, glm::vec3(1.15f, 0.0f, 1.15f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.85f, 0.75f, 0.65f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Anillo 2 de Saturno
	model = temp01;
	model = glm::rotate(model, glm::radians(anillo2Saturno), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1, 0, 1));
	model = glm::scale(model, glm::vec3(1.45f, 1.45f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.62f, 0.505f, 0.403f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Urano
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(17.4, 0, 0));
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.22f, 0.69f, 0.8f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna 1 de Urano
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Urano), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(-0.91, 0, -0.1));
	model = glm::rotate(model, glm::radians(luna1Urano), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.064f, 0.064f, 0.064f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light
	
	//Luna 2 de Urano
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Urano), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.84, 0.32, 0.2));
	model = glm::rotate(model, glm::radians(luna2Urano), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.023f, 0.023f, 0.023f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Neptuno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(19.7, 0, 0));
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.64f, 0.64f, 0.64f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.73f, 0.3f, 0.88f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Luna de Neptuno
	model = temp01;
	model = glm::rotate(model, glm::radians(lunaNeptuno), glm::vec3(0, 1, 0));  //Movimiento de traslación
	model = glm::translate(model, glm::vec3(0.95, 0, -0.18));
	model = glm::rotate(model, glm::radians(lunaNeptuno), glm::vec3(0, 1, 0));  //Movimiento de rotación
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.9f, 0.9f, 0.9f);
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//Fuente de Luz - Sol
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);	
		
	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	lampShader.setMat4("model", model);
	lampShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	
	lampShader.setMat4("model", model);
	my_sphere.render();	//Sphere



	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light

	//glBindVertexArray(0);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        my_input(window);
		animate();

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}