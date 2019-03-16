/*----------------------------------------------------------------------------------*/
/*-----------------------------------  Pr�ctica 6 ----------------------------------*/
/*-----------------------------------    2019-2   ----------------------------------*/
/*------------- Computaci�n Gr�fica e Interacci�n Humano Computadora ---------------*/

/*------------- Balc�zar Rodr�guez Adan Al� ---------------*/
/*-------------- Visual Studio Versi�n 2017 ---------------*/

/*--------------------- Instructivo: ----------------------*/
/*
Con las teclas del teclado se puede mover a todo el sistema:
	D: Mueve el sistema a la izquierda
	A: Mueve el sistema a la derecha
	W: Acerca el sistema
	S: Aleja el sistema
	Flecha abajo: Rota el sistema hacia enfrente
	Flecha arriba: Rota el sistema hacia atras
	AvP�g: Mueve el sistema hacia abajo
	ReP�g: Mueve el sistema hacia arriba

*/

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>
#include <iostream>

#define M_PI 3.14159265358979323846264338327950288
//#include "Sphere.h"

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

//To Buid the Sphere
//---------------------------------------------------------------------------
//const int na = 36;                        // vertex grid size
const int meridianos = 36;			        // vertex grid size   na -> meridianos
const int paralelos = 8;			        // nb -> paralelos
const int meridianos3 = meridianos * 3;     // line in grid size
const int nn = paralelos * meridianos3;     // whole grid size
GLfloat sphere_pos[nn]; // vertex
GLfloat sphere_nor[nn]; // normal
//GLfloat sphere_col[nn];   // color
GLuint  sphere_ix[meridianos*(paralelos - 1) * 6];    // indices
GLuint sphere_vbo[4] = { -1,-1,-1,-1 };
GLuint sphere_vao[4] = { -1,-1,-1,-1 };

void sphere_init()
{
	// generate the sphere data
	GLfloat x, y, z, a, b, da, db, r = 1.0;
	int ia, ib, ix, iy;
	da = (GLfloat)2.0*M_PI / GLfloat(meridianos);
	db = (GLfloat)M_PI / GLfloat(paralelos - 1);
	// [Generate sphere point data]
	// spherical angles a,b covering whole sphere surface
	for (ix = 0, b = (GLfloat)-0.5*M_PI, ib = 0; ib < paralelos; ib++, b += db)
		for (a = 0.0, ia = 0; ia < meridianos; ia++, a += da, ix += 3)
		{
			// unit sphere
			x = cos(b)*cos(a);
			y = cos(b)*sin(a);
			z = sin(b);
			sphere_pos[ix + 0] = x * r;
			sphere_pos[ix + 1] = y * r;
			sphere_pos[ix + 2] = z * r;
			sphere_nor[ix + 0] = x;
			sphere_nor[ix + 1] = y;
			sphere_nor[ix + 2] = z;
		}
	// [Generate GL_TRIANGLE indices]
	for (ix = 0, iy = 0, ib = 1; ib < paralelos; ib++)
	{
		for (ia = 1; ia < meridianos; ia++, iy++)
		{
			// first half of QUAD
			sphere_ix[ix] = iy;      ix++;
			sphere_ix[ix] = iy + 1;    ix++;
			sphere_ix[ix] = iy + meridianos;   ix++;
			// second half of QUAD
			sphere_ix[ix] = iy + meridianos;   ix++;
			sphere_ix[ix] = iy + 1;    ix++;
			sphere_ix[ix] = iy + meridianos + 1; ix++;
		}
		// first half of QUAD
		sphere_ix[ix] = iy;       ix++;
		sphere_ix[ix] = iy + 1 - meridianos;  ix++;
		sphere_ix[ix] = iy + meridianos;    ix++;
		// second half of QUAD
		sphere_ix[ix] = iy + meridianos;    ix++;
		sphere_ix[ix] = iy - meridianos + 1;  ix++;
		sphere_ix[ix] = iy + 1;     ix++;
		iy++;
	}
	// [VAO/VBO stuff]
	GLuint i;
	glGenVertexArrays(4, sphere_vao);
	glGenBuffers(4, sphere_vbo);
	glBindVertexArray(sphere_vao[0]);
	i = 0; // vertex
	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_pos), sphere_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 1; // indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_vbo[i]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_ix), sphere_ix, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	i = 2; // normal
	glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_nor), sphere_nor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	/*
		i=3; // color
		glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_col),sphere_col,GL_STATIC_DRAW);
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,0,0);
	*/
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void sphere_exit()
{
	glDeleteVertexArrays(4, sphere_vao);
	glDeleteBuffers(4, sphere_vbo);
}
void sphere_draw()
{
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBindVertexArray(sphere_vao[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(sphere_pos)/sizeof(GLfloat));                        // POINTS ... no indices for debug
	glDrawElements(GL_LINE_LOOP, sizeof(sphere_ix) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
	glBindVertexArray(0);
}


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
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp

	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar c�digo aqu�

	//Sol
	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	sphere_draw();	

	//Mercurio
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model,glm::vec3(3,0,0));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.885f, 0.670f, 0.415f));
	sphere_draw();

	//Venus
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(4.5, 0, 0));
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.39f, 0.39f, 0.39f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.980f, 0.533f, 0.115f));
	sphere_draw();

	//Tierra
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(6.5, 0, 0));
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.45f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.058f, 0.36f, 0.95f));
	sphere_draw();

	//Luna 1 de Tierra
	model = temp01;
	model = glm::rotate(model, glm::radians(lunaTierra), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.6, 0, 0));
	model = glm::rotate(model, glm::radians(lunaTierra), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.075f, 0.075f, 0.075f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Marte
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(8.3, 0, 0));
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.32f, 0.32f, 0.32f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.95f, 0.02f, 0.03f));
	sphere_draw();

	//Luna 1 de Marte
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Marte), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(-0.41, 0, 0));
	model = glm::rotate(model, glm::radians(luna1Marte), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.055f, 0.055f, 0.055f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Luna 2 de Marte
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Marte), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.45, 0, 0.15));
	model = glm::rotate(model, glm::radians(luna2Marte), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.026f, 0.026f, 0.026f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//J�piter
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(11.25, 0, 0));
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.84f, 0.84f, 0.84f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.95f, 0.895f, 0.35f));
	sphere_draw();

	//Luna 1 de J�piter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(-0.97, 0.12, -0.32));
	model = glm::rotate(model, glm::radians(luna1Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.055f, 0.055f, 0.055f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Luna 2 de J�piter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.95, 0, 0.27));
	model = glm::rotate(model, glm::radians(luna2Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.026f, 0.026f, 0.026f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Luna 3 de J�piter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna3Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(-1.05, 0.25, 0.12));
	model = glm::rotate(model, glm::radians(luna3Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.064f, 0.064f, 0.064f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Luna 4 de J�piter
	model = temp01;
	model = glm::rotate(model, glm::radians(luna4Jupiter), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.995, -0.42, 0.01));
	model = glm::rotate(model, glm::radians(luna4Jupiter), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.036f, 0.036f, 0.036f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Saturno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(14.3, 0, 0));
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.84f, 0.84f, 0.84f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.62f, 0.505f, 0.403f));
	sphere_draw();

	//Anillo 1 de Saturno
	model = temp01;
	model = glm::rotate(model, glm::radians(anillo1Saturno), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1, 0, 1));
	model = glm::scale(model, glm::vec3(1.15f, 0.0f, 1.15f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.85f, 0.75f, 0.65f));
	sphere_draw();

	//Anillo 2 de Saturno
	model = temp01;
	model = glm::rotate(model, glm::radians(anillo2Saturno), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1, 0, 1));
	model = glm::scale(model, glm::vec3(1.45f, 1.45f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.62f, 0.505f, 0.403f));
	sphere_draw();

	//Urano
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(17.4, 0, 0));
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.76f, 0.76f, 0.76f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.22f, 0.69f, 0.8f));
	sphere_draw();

	//Luna 1 de Urano
	model = temp01;
	model = glm::rotate(model, glm::radians(luna1Urano), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(-0.91, 0, -0.1));
	model = glm::rotate(model, glm::radians(luna1Urano), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.064f, 0.064f, 0.064f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Luna 2 de Urano
	model = temp01;
	model = glm::rotate(model, glm::radians(luna2Urano), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.84, 0.32, 0.2));
	model = glm::rotate(model, glm::radians(luna2Urano), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.023f, 0.023f, 0.023f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();

	//Neptuno
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(19.7, 0, 0));
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f));  //Movimiento de rotaci�n
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.64f, 0.64f, 0.64f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.73f, 0.3f, 0.88f));
	sphere_draw();

	//Luna de Urano
	model = temp01;
	model = glm::rotate(model, glm::radians(lunaNeptuno), glm::vec3(0, 1, 0));  //Movimiento de traslaci�n
	model = glm::translate(model, glm::vec3(0.95, 0, -0.18));
	model = glm::rotate(model, glm::radians(lunaNeptuno), glm::vec3(0, 1, 0));  //Movimiento de rotaci�n
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	sphere_draw();


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
	sphere_init();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);
		animate();

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
	sphere_exit();
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 0.18f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}