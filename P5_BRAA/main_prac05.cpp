/*----------------------------------------------------------------------------------*/
/*-----------------------------------  Pr�ctica 5 ----------------------------------*/
/*-----------------------------------    2019-2   ----------------------------------*/
/*------------- Computaci�n Gr�fica e Interacci�n Humano Computadora ---------------*/

/*------------- Balc�zar Rodr�guez Adan Al� ---------------*/
/*-------------- Visual Studio Versi�n 2017 ---------------*/

/*--------------------- Instructivo: ----------------------*/
/*
Con las teclas del teclado se puede mover a la figura
	W: Aleja
	A: Mueve a la izquierda
	S: Acerca
	D: Mueve a la derecha
	ReP�g: Mueve hacia arriba
	AvP�g: Mueve hacia abajo
	Flecha Arriba: Rota hacia arriba
	Flecha Abajo: Rota hacia abajo
	Flecha Izquierda: Rota a la izquierda
	Flecha Derecha: Rota a la derecha

Con las siguientes teclas, se mueven las articulaciones del brazo
	T: Baja el brazo desde el hombro
	T + SHIFT: Sube el brazo desde el hombro
	Y: Contrae el brazo desde el codo
	Y + SHIFT: Estira el brazo desde el codo
	U: Contrae la mu�eca
	U + SHIFT: Estira la mu�eca
	I: Contrae el pulgar
	I + SHIFT: Estira el pulgar
	O: Contrae el �ndice
	O + SHIFT: Estira el �ndice
	P: Contrae el dedo medio
	P + SHIFT: Estira el dedo medio
	K: Contrae el anular
	K + SHIFT: Estira el anular
	L: Contrae el me�ique
	L + SHIFT: Estira el me�ique
*/


#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;

//Variables de movimiento angular
float angHombro = 0.0f;
float angCodo = 0.0f;
float angMuneca = 0.0f; 
float angPulgar = 0.0f;
float angIndice = 0.0f;
float angMedio = 0.0f;
float angAnular = 0.0f;
float angMenique = 0.0f;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f);  //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection


	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

	//Hombro
	model = glm::rotate(model, glm::radians(angHombro), glm::vec3(0,0,1));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.5));
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Bicep
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 0.5));
	projectionShader.setVec3("aColor", glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Antebrazo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1, 0, 0));                        //Pivote del Codo
	model = glm::rotate(model, glm::radians(angCodo), glm::vec3(0, 1, 0));    //La rotaci�n se aplica en el codo
	model = glm::translate(model, glm::vec3(1.5, 0, 0));                      //Ya nos movemos al centro del antebrazo para dibujarlo
	modelTemp = model;
	model = glm::scale(model, glm::vec3(3, 1, 0.5));
	projectionShader.setVec3("aColor", glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Palma
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1.5, 0, 0));                       //Pivote de la mu�eca
	model = glm::rotate(model, glm::radians(angMuneca), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la mu�eca
	model = glm::translate(model, glm::vec3(0.5, 0, 0));                       //Ya nos movemos al centro de la palma para dibujarla
	modelTemp2 = model;
	model = glm::scale(model, glm::vec3(1, 1, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Pulgar
	// Falange 1
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));                   //Pivote falange 1
	model = glm::rotate(model, glm::radians(angPulgar), glm::vec3(1, 0, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0, 0.15, 0));                      //Ya nos movemos al centro de la primer falange
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0.5, 0, 1));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0, 0.15, 0));                            //Pivote falange 2
	model = glm::rotate(model, glm::radians(angPulgar*0.75f), glm::vec3(1, 0, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0, 0.15, 0));                            //Ya nos movemos al centro de la segunda falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1.0, 0.0, 0.5));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//�ndice
	// Falange 1
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, 0.375, 0));                   //Pivote falange 1
	model = glm::rotate(model, glm::radians(angIndice), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                      //Ya nos movemos al centro de la primer falange
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0.5, 0.5, 0.5));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Pivote falange 2
	model = glm::rotate(model, glm::radians(angIndice*0.75f), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Ya nos movemos al centro de la segunda falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0.6, 0.6, 0.6));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 3
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Pivote falange 3
	model = glm::rotate(model, glm::radians(angIndice*0.5f), glm::vec3(0, 1, 0));    //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                             //Ya nos movemos al centro de la tercer falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0.7, 0.7, 0.7));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Medio
	// Falange 1
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, 0.125, 0));                  //Pivote falange 1
	model = glm::rotate(model, glm::radians(angMedio), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.2, 0, 0));                      //Ya nos movemos al centro de la primer falange
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0, 0.1, 1));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.2, 0, 0));                            //Pivote falange 2
	model = glm::rotate(model, glm::radians(angMedio*0.75f), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                           //Ya nos movemos al centro de la segunda falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0, 0.4, 1));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 3
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                           //Pivote falange 3
	model = glm::rotate(model, glm::radians(angMedio*0.5f), glm::vec3(0, 1, 0));    //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                           //Ya nos movemos al centro de la tercer falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(0, 0.7, 1));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Anular
	// Falange 1
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, -0.125, 0));                  //Pivote falange 1
	model = glm::rotate(model, glm::radians(angAnular), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                      //Ya nos movemos al centro de la primer falange
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.1, 0.6));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                             //Pivote falange 2
	model = glm::rotate(model, glm::radians(angAnular*0.75f), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Ya nos movemos al centro de la segunda falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.3, 0.6));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 3
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Pivote falange 3
	model = glm::rotate(model, glm::radians(angAnular*0.5f), glm::vec3(0, 1, 0));    //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.15, 0, 0));                            //Ya nos movemos al centro de la tercer falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.5, 0.6));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Me�ique
	// Falange 1
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, -0.375, 0));                   //Pivote falange 1
	model = glm::rotate(model, glm::radians(angMenique), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                        //Ya nos movemos al centro de la primer falange
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.1, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                              //Pivote falange 2
	model = glm::rotate(model, glm::radians(angMenique*0.75f), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                              //Ya nos movemos al centro de la segunda falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.3, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	// Falange 3
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                             //Pivote falange 3
	model = glm::rotate(model, glm::radians(angMenique*0.5f), glm::vec3(0, 1, 0));   //La rotaci�n se aplica en la articulaci�n
	model = glm::translate(model, glm::vec3(0.1, 0, 0));                             //Ya nos movemos al centro de la tercer falange
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setVec3("aColor", glm::vec3(1, 0.5, 0));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);


	// ------------------- Ejemplos de clase ------------------
	/*
	//Cubo Rojo de 5u^3
	projectionShader.setVec3("aColor", glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(5, 5, 5));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Cubo Azul de 8u^3
	projectionShader.setVec3("aColor", glm::vec3(0, 0, 1));
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-17, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(8, 8, 8));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	*/

	glBindVertexArray(0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi funci�n de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.5f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 0.5f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 0.5f;

	//Bot�n de rotaci�n del hombro
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angHombro < 90)
				angHombro += 0.5f;
		}
		else
		{
			if (angHombro > -90)
				angHombro -= 0.5f;
		}
	}

	//Bot�n de rotaci�n del codo
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angCodo < 0)
				angCodo += 0.5f;
		}
		else
		{	
			if (angCodo > -140)
				angCodo -= 0.5f;
		}
	}

	//Bot�n de rotaci�n de la mu�eca
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angMuneca < 20)
				angMuneca += 0.5f;
		}
		else
		{
			if (angMuneca > -90)
				angMuneca -= 0.5f;
		}
	}

	//Bot�n de rotaci�n del pulgar
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angPulgar > 0)
				angPulgar -= 0.5f;
		}
		else
		{
			if (angPulgar < 90)
				angPulgar += 0.5f;
		}
	}
		
	//Bot�n de rotaci�n del �ndice
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angIndice < 0)
				angIndice += 0.5f;
		}
		else
		{
			if (angIndice > -90)
				angIndice -= 0.5f;
		}
	}

	//Bot�n de rotaci�n del dedo medio
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angMedio < 0)
				angMedio += 0.5f;
		}
		else
		{
			if (angMedio > -90)
				angMedio -= 0.5f;
		}
	}

	//Bot�n de rotaci�n del anular
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angAnular < 0)
				angAnular += 0.5f;
		}
		else
		{
			if (angAnular > -90)
				angAnular -= 0.5f;
		}
	}

	//Bot�n de rotaci�n del me�ique
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		{
			if (angMenique < 0)
				angMenique += 0.5f;
		}
		else
		{
			if (angMenique > -90)
				angMenique -= 0.5f;
		}
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}