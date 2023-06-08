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
#include "Texture.h"
#include "modelAnim.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(-100.0f, 2.0f, -45.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
float movCamera = 0.0f;





//Variables Animacion las cuales son usadas para
//los movimientos de rotacion, traslacion y activacion 
//de animaciones y sentindos

bool sentido = false, sentidoP = false,AguaAnim = true;
bool animLevanta = false;
bool animCoche = false;
bool animTigre = false, animTigreDos = true,sentidoMandiDos = false, sentidoCola = false, sentidoColaDos = false; 
bool animTrompa = false;
bool animCaida = false;
bool animCaminata = false;
float movFront = 0,movBack = 0, movCuerpo = 0, movTrompa = 0;
float movFrontDos = 0, movBackDos = 0, movCuerpoDos = 0;

float rotTrompa = 0,rotTrompaDos = 0, rotTrompaL = 0, cuentaT = 0;
float movEle = 0;
float rotPar, rotImp;
float rotFrente = 0, rotTras = 0;
float rotFrenteDos = -90, rotTrasDos = 90;
float rotT = -90;
bool animPuerta = false; 
bool animJirafa = false, sentidoJ = false, retro = false;
float rotParJ, rotImpJ;
float movJira = 0;
float rotJX = 0,rotJZ = 0, rotJY = 0;
float movCocheZ = 0, movCocheX = 0, rotCoche = 0;
bool sentidoCoche = false, sentidoMandi = false;
float rotPuerta;
float tiempo;
float speed;
float rotParT = 0, rotImpT = 0, movTigre = 0, movCuerpoT = 0, rotCuerpoT = 0;
float movFrontTY = 0, movFrontTX = 0, rotFronT= 0;
float movMandiY = 0, movMandiX = 0, rotMandi = 0, rotCola = 0, rotMandiDos = 0, rotCL = 0;
bool sentidoT = false;

float movPandaX = 0,movPandaY = 0, movPandaZ = 0;
float movIzqTrasX = 0, movIzqTrasY = 0, movIzqTrasZ = 0;
float movDerTrasX = 0, movDerTrasY = 0, movDerTrasZ = 0;
float movIzqDelX = 0, movIzqDelY = 0, movIzqDelZ = 0;
float movDerDelX = 0, movDerDelY = 0, movDerDelZ = 0;

float rotTrasX = 0;
float rotTrasY = 0;
float rotTrasZ = 0;

float rotDelX = 0;
float rotDelY = 0;
float rotDelZ = 0;


float rotMonoDos = 0;
bool sentidoMono = false, animMono = true;
float rotMono = 0, movMonoX = 0, movMonoY = 0, movMonoZ = 0;



// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 1.0f, -45.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

bool active;


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Keyframes
float posX = PosIni.x, posY = PosIni.y, posZ = PosIni.z;


#define MAX_FRAMES 5
int i_max_steps = 190;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ


	float movPandaX; 
	float movPandaY;
	float movPandaZ;
	float movIzqTrasX;
	float movIzqTrasY;
	float movIzqTrasZ;
	float movDerTrasX;
	float movDerTrasY;
	float movDerTrasZ;
	float movIzqDelX;
	float movIzqDelY;
	float movIzqDelZ;
	float movDerDelX;
	float movDerDelY;
	float movDerDelZ;
	float movInc;

	float movPandaX_Inc;
	float movPandaY_Inc;
	float movPandaZ_Inc;
	float movIzqTrasX_Inc;
	float movIzqTrasY_Inc;
	float movIzqTrasZ_Inc;
	float movDerTrasX_Inc;
	float movDerTrasY_Inc;
	float movDerTrasZ_Inc;
	float movIzqDelX_Inc;
	float movIzqDelY_Inc;
	float movIzqDelZ_Inc;
	float movDerDelX_Inc;
	float movDerDelY_Inc;
	float movDerDelZ_Inc;


	float rotDelY;
	float rotDelZ;
	float rotDelX;
	float rotDelX_Inc;
	float rotDelY_Inc;
	float rotDelZ_Inc;

	float rotTrasY;
	float rotTrasZ;
	float rotTrasX;
	float rotTrasX_Inc;
	float rotTrasY_Inc;
	float rotTrasZ_Inc;

	float movMonoX;
	float movMonoY;
	float movMonoZ;
	float rotMono;

	float movMonoX_Inc;
	float movMonoY_Inc;
	float movMonoZ_Inc;
	float rotMono_Inc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(posX,posY,posZ),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0),
	glm::vec3(0,0,0)
};

glm::vec3 LightP1;




void saveFrame(void)
{

	

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].movPandaX = movPandaX;
	KeyFrame[FrameIndex].movPandaY = movPandaY;
	KeyFrame[FrameIndex].movPandaZ = movPandaZ;
	KeyFrame[FrameIndex].movIzqTrasX = movIzqTrasX;
	KeyFrame[FrameIndex].movIzqTrasY = movIzqTrasY;
	KeyFrame[FrameIndex].movIzqTrasZ = movIzqTrasZ;
	KeyFrame[FrameIndex].movDerTrasX = movDerTrasX;
	KeyFrame[FrameIndex].movDerTrasY = movDerTrasY;
	KeyFrame[FrameIndex].movDerTrasZ = movDerTrasZ;
	KeyFrame[FrameIndex].movIzqDelX = movIzqDelX;
	KeyFrame[FrameIndex].movIzqDelY = movIzqDelY;
	KeyFrame[FrameIndex].movIzqDelZ = movIzqDelZ;
	KeyFrame[FrameIndex].movDerDelX = movDerDelX;
	KeyFrame[FrameIndex].movDerDelY = movDerDelY;
	KeyFrame[FrameIndex].movDerDelZ = movDerDelZ;

	KeyFrame[FrameIndex].rotTrasX = rotTrasX;
	KeyFrame[FrameIndex].rotTrasY = rotTrasY;
	KeyFrame[FrameIndex].rotTrasZ = rotTrasZ;

	KeyFrame[FrameIndex].rotDelX = rotDelX;
	KeyFrame[FrameIndex].rotDelY = rotDelY;
	KeyFrame[FrameIndex].rotDelZ = rotDelZ;

	KeyFrame[FrameIndex].movMonoX = movMonoX;
	KeyFrame[FrameIndex].movMonoY = movMonoY;
	KeyFrame[FrameIndex].movMonoZ = movMonoZ;
	KeyFrame[FrameIndex].rotMono = rotMono;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	movPandaX = KeyFrame[0].movPandaX;
	movPandaY = KeyFrame[0].movPandaY;
	movPandaZ = KeyFrame[0].movPandaZ;

	movIzqTrasX = KeyFrame[0].movIzqTrasX;
	movIzqTrasY = KeyFrame[0].movIzqTrasY;
	movIzqTrasZ = KeyFrame[0].movIzqTrasZ;
	movDerTrasX = KeyFrame[0].movDerTrasX;
	movDerTrasY = KeyFrame[0].movDerTrasY;
	movDerTrasZ = KeyFrame[0].movDerTrasZ;
	movIzqDelX = KeyFrame[0].movIzqDelX;
	movIzqDelY = KeyFrame[0].movIzqDelY;
	movIzqDelZ = KeyFrame[0].movIzqDelZ;
	movDerDelX = KeyFrame[0].movDerDelX;
	movDerDelY = KeyFrame[0].movDerDelY;
	movDerDelZ = KeyFrame[0].movDerDelZ;



	rotTrasX = KeyFrame[0].rotTrasX;
	rotTrasY = KeyFrame[0].rotTrasY;
	rotTrasZ = KeyFrame[0].rotTrasZ;

	rotTrasX = KeyFrame[0].rotDelX;
	rotTrasY = KeyFrame[0].rotDelY;
	rotTrasZ = KeyFrame[0].rotDelZ;

	movMonoX = KeyFrame[0].movMonoX;
	movMonoY = KeyFrame[0].movMonoY;
	movMonoZ = KeyFrame[0].movMonoZ;
	rotMono = KeyFrame[0].rotMono;
	


}

void interpolation(void)
{

	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;


	KeyFrame[playIndex].movPandaX_Inc   = (KeyFrame[playIndex + 1].movPandaX - KeyFrame[playIndex].movPandaX) / i_max_steps;
	KeyFrame[playIndex].movPandaY_Inc   = (KeyFrame[playIndex + 1].movPandaY - KeyFrame[playIndex].movPandaY) / i_max_steps; 
	KeyFrame[playIndex].movPandaZ_Inc   = (KeyFrame[playIndex + 1].movPandaZ - KeyFrame[playIndex].movPandaZ) / i_max_steps; 
	KeyFrame[playIndex].movIzqTrasX_Inc = (KeyFrame[playIndex + 1].movIzqTrasX - KeyFrame[playIndex].movIzqTrasX) / i_max_steps;
	KeyFrame[playIndex].movIzqTrasY_Inc = (KeyFrame[playIndex + 1].movIzqTrasY - KeyFrame[playIndex].movIzqTrasY) / i_max_steps; 
	KeyFrame[playIndex].movIzqTrasZ_Inc = (KeyFrame[playIndex + 1].movIzqTrasZ - KeyFrame[playIndex].movIzqTrasZ) / i_max_steps; 
	KeyFrame[playIndex].movDerTrasX_Inc = (KeyFrame[playIndex + 1].movDerTrasX - KeyFrame[playIndex].movDerTrasX) / i_max_steps; 
	KeyFrame[playIndex].movDerTrasY_Inc = (KeyFrame[playIndex + 1].movDerTrasY - KeyFrame[playIndex].movDerTrasY) / i_max_steps; 
	KeyFrame[playIndex].movDerTrasZ_Inc = (KeyFrame[playIndex + 1].movDerTrasZ - KeyFrame[playIndex].movDerTrasZ) / i_max_steps; 
	KeyFrame[playIndex].movIzqDelX_Inc  = (KeyFrame[playIndex + 1].movIzqDelX - KeyFrame[playIndex].movIzqDelX) / i_max_steps;  
	KeyFrame[playIndex].movIzqDelY_Inc  = (KeyFrame[playIndex + 1].movIzqDelY - KeyFrame[playIndex].movIzqDelY) / i_max_steps; 
	KeyFrame[playIndex].movIzqDelZ_Inc  = (KeyFrame[playIndex + 1].movIzqDelZ - KeyFrame[playIndex].movIzqDelZ) / i_max_steps; 
	KeyFrame[playIndex].movDerDelX_Inc  = (KeyFrame[playIndex + 1].movDerDelX - KeyFrame[playIndex].movDerDelX) / i_max_steps; 
	KeyFrame[playIndex].movDerDelY_Inc  = (KeyFrame[playIndex + 1].movDerDelY - KeyFrame[playIndex].movDerDelY) / i_max_steps; 
	KeyFrame[playIndex].movDerDelZ_Inc  = (KeyFrame[playIndex + 1].movDerDelZ - KeyFrame[playIndex].movDerDelZ) / i_max_steps; 

	KeyFrame[playIndex].rotTrasX_Inc = (KeyFrame[playIndex + 1].rotTrasX - KeyFrame[playIndex].rotTrasX) / i_max_steps;
	KeyFrame[playIndex].rotTrasY_Inc = (KeyFrame[playIndex + 1].rotTrasY - KeyFrame[playIndex].rotTrasY) / i_max_steps;
	KeyFrame[playIndex].rotTrasZ_Inc = (KeyFrame[playIndex + 1].rotTrasZ - KeyFrame[playIndex].rotTrasZ) / i_max_steps;


	KeyFrame[playIndex].rotDelX_Inc = (KeyFrame[playIndex + 1].rotDelX - KeyFrame[playIndex].rotDelX) / i_max_steps;
	KeyFrame[playIndex].rotDelY_Inc = (KeyFrame[playIndex + 1].rotDelY - KeyFrame[playIndex].rotDelY) / i_max_steps;
	KeyFrame[playIndex].rotDelZ_Inc = (KeyFrame[playIndex + 1].rotDelZ - KeyFrame[playIndex].rotDelZ) / i_max_steps;

	KeyFrame[playIndex].movMonoX_Inc = (KeyFrame[playIndex + 1].movMonoX - KeyFrame[playIndex].movMonoX) / i_max_steps;
	KeyFrame[playIndex].movMonoY_Inc = (KeyFrame[playIndex + 1].movMonoY - KeyFrame[playIndex].movMonoY) / i_max_steps;
	KeyFrame[playIndex].movMonoZ_Inc = (KeyFrame[playIndex + 1].movMonoZ - KeyFrame[playIndex].movMonoZ) / i_max_steps;
	KeyFrame[playIndex].rotMono_Inc = (KeyFrame[playIndex + 1].rotMono - KeyFrame[playIndex].rotMono) / i_max_steps;


}




int main()
{
	// Init GLFW
	glfwInit();




	// Set all the required options for GLFW
	/*(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final: Zoologico", nullptr, nullptr);

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
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.frag");

	//Carga de modelos y rutas de los mismos
	Model Zoo((char*)"Models/Zoologico.obj");
	Model Domo((char*)"Models/Domo.obj");
	Model Agua((char*)"Models/Agua.obj");
	Model PuertaDer((char*)"Models/PuertaDer.obj");
	Model PuertaIzq((char*)"Models/PuertaIzq.obj");

	//Elefantes
	Model Trompa((char*)"Models/Elefante/Trompa.obj");
	Model Ele((char*)"Models/Elefante/Elefante.obj");
	Model DerFront((char*)"Models/Elefante/DerFront.obj");
	Model DerTras((char*)"Models/Elefante/DerTras.obj");
	Model IzqTras((char*)"Models/Elefante/IzqTras.obj");
	Model IzqFront((char*)"Models/Elefante/IzqFront.obj");
	

	Model TrompaDos((char*)"Models/Elefante/TrompaDos.obj");
	Model EleDos((char*)"Models/Elefante/ElefanteDos.obj");
	Model DerFrontDos((char*)"Models/Elefante/DerFrontDos.obj");
	Model DerTrasDos((char*)"Models/Elefante/DerTrasDos.obj");
	Model IzqTrasDos((char*)"Models/Elefante/IzqTrasDos.obj");
	Model IzqFronDos((char*)"Models/Elefante/IzqFrontDos.obj");


	//Jirafas
	Model Jirafa((char*)"Models/Jirafa/Cabeza.obj");
	Model Torso((char*)"Models/Jirafa/Torso.obj");
	Model DerFrontJ((char*)"Models/Jirafa/DerFront.obj");
	Model IzqFrontJ((char*)"Models/Jirafa/IzqFront.obj");
	Model DerTrasJ((char*)"Models/Jirafa/DerTras.obj");
	Model IzqTrasJ((char*)"Models/Jirafa/IzqTras.obj");


	Model JirafaDos((char*)"Models/Jirafa/CabezaDos.obj");
	Model TorsoDos((char*)"Models/Jirafa/TorsoDos.obj");
	Model DerFrontDosJ((char*)"Models/Jirafa/DerFrontDos.obj");
	Model IzqFrontDosJ((char*)"Models/Jirafa/IzqFrontDos.obj");
	Model DerTrasDosJ((char*)"Models/Jirafa/DerTrasDos.obj");
	Model IzqTrasDosJ((char*)"Models/Jirafa/IzqTrasDos.obj");

	//Coche
	Model Coche((char*)"Models/Coche.obj");

	//Tigres
	Model Tigre((char*)"Models/Tigre/Tigre.obj");
	Model Hosico((char*)"Models/Tigre/Mandibula.obj");
	Model IzqTrasT((char*)"Models/Tigre/IzqTras.obj");
	Model IzqFrontT((char*)"Models/Tigre/IzqFront.obj");
	Model DerTrasT((char*)"Models/Tigre/DerTras.obj");
	Model DerFrontT((char*)"Models/Tigre/DerFront.obj");

	Model TigreDos((char*)"Models/Tigre/TigreDos.obj");
	Model HosicoDos((char*)"Models/Tigre/MandiDos.obj");
	Model Cola((char*)"Models/Tigre/Cola.obj");


	//Tigres
	Model Panda((char*)"Models/Panda/CuerpoP.obj");
	Model DerDelP((char*)"Models/Panda/DerDel.obj");
	Model IzqDelP((char*)"Models/Panda/IzqDel.obj");
	Model DerTrasP((char*)"Models/Panda/DerTras.obj");
	Model IzqTrasP((char*)"Models/Panda/IzqTras.obj");

	//Monos
	Model Mono((char*)"Models/Mono/Mono.obj");
	Model MonoDos((char*)"Models/Mono/Mono.obj");


	// Build and compile our shader program

	//Inicializaci�n de KeyFrames

	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;

		KeyFrame[i].movPandaX = 0;
		KeyFrame[i].movPandaY = 0;
		KeyFrame[i].movPandaZ = 0;
		KeyFrame[i].movIzqTrasX =0;
		KeyFrame[i].movIzqTrasY =0;
		KeyFrame[i].movIzqTrasZ =0;
		KeyFrame[i].movDerTrasX =0;
		KeyFrame[i].movDerTrasY =0;
		KeyFrame[i].movDerTrasZ =0;
		KeyFrame[i].movIzqDelX = 0;
		KeyFrame[i].movIzqDelY = 0;
		KeyFrame[i].movIzqDelZ = 0;
		KeyFrame[i].movDerDelX = 0;
		KeyFrame[i].movDerDelY = 0;
		KeyFrame[i].movDerDelZ = 0;

		KeyFrame[i].rotTrasX = 0;
		KeyFrame[i].rotTrasY = 0;
		KeyFrame[i].rotTrasZ = 0;
					   
		KeyFrame[i].rotDelX = 0;
		KeyFrame[i].rotDelY = 0;
		KeyFrame[i].rotDelZ = 0;

		KeyFrame[i].rotMono = 0;
		KeyFrame[i].movMonoX = 0;
		KeyFrame[i].movMonoY = 0;
		KeyFrame[i].movMonoZ = 0;

	}



	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Carga de las texturas para el skybox(formato de imagenes en tga)
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

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


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.78f, 0.78f, 0.78f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), -91.919342f, 1.06f, -126.390137f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.20f);


		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

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

		// Bind diffuse map
		//glBindTexture(GL_TEXTURE_2D, texture1);*/

		// Bind specular map
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);*/


		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp



		//Carga de modelos

		view = camera.GetViewMatrix();
		glm::mat4 model(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0); //Desactiva la transparencia 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);//Pasa al color alpha 1 para quitar tra
		Zoo.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(23.776f, 2.167f, 41.19f));
		model = glm::rotate(model, glm::radians(rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0); //Desactiva la transparencia 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);//Pasa al color alpha 1 para quitar tra
		PuertaIzq.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(29.911f , 2.167f, 41.18f));
		model = glm::rotate(model, glm::radians(-rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0); //Desactiva la transparencia 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);//Pasa al color alpha 1 para quitar tra
		PuertaDer.Draw(lightingShader);

		//Elefante
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(-22.576 - movEle, 1.991f, -9.195f));
		model = glm::translate(model, glm::vec3(0,-movCuerpo,0));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0); //Desactiva la transparencia 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);//Pasa al color alpha 1 para quitar tra
		Ele.Draw(lightingShader);



		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movEle, posY, posZ));
		model = glm::translate(model, glm::vec3(-24.216f, 2.339f, -9.192f));
		model = glm::translate(model, glm::vec3(0, -movCuerpo, 0));
		model = glm::rotate(model, glm::radians(rotTrompa), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Trompa.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(-22.789f - movEle, 1.59f, -9.527f));
		model = glm::translate(model, glm::vec3(0, -movFront, 0));
		model = glm::rotate(model, glm::radians(rotPar), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotFrente), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerFront.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(-20.87f - movEle, 1.271f, -9.495f));
		model = glm::translate(model, glm::vec3(0,-movBack, 0));
		model = glm::rotate(model, glm::radians(rotPar), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTras), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTras.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(-20.864f - movEle, 1.27f, -8.887f));
		model = glm::translate(model, glm::vec3(0, -movBack, 0));
		model = glm::rotate(model, glm::radians(-rotImp), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTras), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTras.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(-22.79f - movEle, 1.591f, -8.856f));
		model = glm::translate(model, glm::vec3(0, -movFront, 0));
		model = glm::rotate(model, glm::radians(-rotImp), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotFrente), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqFront.Draw(lightingShader);
		
		//Segundo Elefante

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movCuerpoDos, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(-32.163, 0.802f, -5.566f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0); //Desactiva la transparencia 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);//Pasa al color alpha 1 para quitar tra
		EleDos.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movTrompa, posZ));
		model = glm::translate(model, glm::vec3(-32.159f, 0.802f, -3.932f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotT), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTrompaDos), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTrompaL), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TrompaDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movFrontDos, posZ));
		model = glm::translate(model, glm::vec3(-32.502f, 0.802f, -5.35f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotTrasDos), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerFrontDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movBackDos, posZ));
		model = glm::translate(model, glm::vec3(-32.459f, 0.802f, -7.274f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotFrenteDos), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTrasDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movBackDos, posZ));
		model = glm::translate(model, glm::vec3(-31.859f, 0.802f, -7.267f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotFrenteDos), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTrasDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY+ movFrontDos, posZ));
		model = glm::translate(model, glm::vec3(-31.82f, 0.802f, -5.349f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotTrasDos), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqFronDos.Draw(lightingShader);




		//Jirafas

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(36.79f + movJira, 3.576f , 36.001f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotJZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotJX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotJY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Jirafa.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));		
		model = glm::translate(model, glm::vec3(36.27f + movJira, 2.581f, 36.029f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Torso.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));		
		model = glm::translate(model, glm::vec3(36.399f + movJira, 2.137f, 36.172f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotParJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerFrontJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(36.376f + movJira, 2.137f, 35.82f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotImpJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqFrontJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(35.27f + movJira, 2.145f, 36.132f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotImpJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTrasJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(35.271f + movJira, 2.144f, 35.851f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotParJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTrasJ.Draw(lightingShader);





		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(44.925f-movJira, 3.576f, 36.063f));
		model = glm::rotate(model, glm::radians(rotJZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-rotJX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotJY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		JirafaDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(45.447f - movJira, 2.581f, 36.029f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TorsoDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(45.327f - movJira, 2.137f, 35.883f));
		model = glm::rotate(model, glm::radians(rotParJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerFrontDosJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(45.344f - movJira, 2.137f, 36.236f));
		model = glm::rotate(model, glm::radians(-rotImpJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqFrontDosJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(46.446f - movJira, 2.145f, 35.927f));
		model = glm::rotate(model, glm::radians(-rotImpJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTrasDosJ.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(46.443f - movJira, 2.145f, 36.206f));
		model = glm::rotate(model, glm::radians(rotParJ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTrasDosJ.Draw(lightingShader);


		//Coche
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX+ movCocheX, posY, posZ + movCocheZ));
		model = glm::translate(model, glm::vec3(52.075f, 0.724f, 43.058f));
		model = glm::rotate(model, glm::radians(rotCoche), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Coche.Draw(lightingShader);

		//Tigre
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre, posY + movCuerpoT, posZ));
		model = glm::translate(model, glm::vec3(-0.609f,-2.618f,-3.562));
		model = glm::rotate(model, glm::radians(rotCuerpoT), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Tigre.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre + movMandiX, posY+movMandiY, posZ));
		model = glm::translate(model, glm::vec3(-1.609f, -2.28f, -3.563f));
		model = glm::rotate(model, glm::radians(rotMandi), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Hosico.Draw(lightingShader);

		
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre - movFrontTX, posY + movFrontTY, posZ));
		model = glm::translate(model, glm::vec3(-1.297f, -2.393f, -3.459f));
		model = glm::rotate(model, glm::radians(-rotImpT), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotFronT), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqFrontT.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre - movFrontTX, posY + movFrontTY, posZ));
		model = glm::translate(model, glm::vec3(-1.298f, -2.391f, -3.696f));
		model = glm::rotate(model, glm::radians(rotParT), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotFronT), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerFrontT.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre, posY, posZ));
		model = glm::translate(model, glm::vec3(0.009f, -2.359f, -3.701f));
		model = glm::rotate(model, glm::radians(-rotImpT), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTrasT.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX - movTigre, posY, posZ));
		model = glm::translate(model, glm::vec3(0.012f, -2.362f, -3.482f));
		model = glm::rotate(model, glm::radians(rotParT), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTrasT.Draw(lightingShader);

		

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX , posY, posZ));
		model = glm::translate(model, glm::vec3(12.875f, -2.577f,0));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		TigreDos.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(13.577f, -2.275f, -0.013f));
		model = glm::rotate(model, glm::radians(rotMandiDos), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HosicoDos.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(11.779f, -2.207f, -0.008f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotCola), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotCL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Cola.Draw(lightingShader);

		//Panda FRAMES
		KeyFrame[0].movIzqDelX = 0.000000;
		KeyFrame[1].movIzqDelX = -0.300000;
		KeyFrame[2].movIzqDelX = -0.600000;
		KeyFrame[3].movIzqDelX = -1.300000;
		KeyFrame[0].movIzqDelY = 0.000000;
		KeyFrame[1].movIzqDelY = 1.700000;
		KeyFrame[2].movIzqDelY = 3.399999;
		KeyFrame[3].movIzqDelY = 5.199997;
		KeyFrame[0].movIzqDelZ = 0.000000;
		KeyFrame[1].movIzqDelZ = 0.000000;
		KeyFrame[2].movIzqDelZ = 0.000000;
		KeyFrame[3].movIzqDelZ = 0.000000;
		KeyFrame[0].movDerDelX = 0.000000;
		KeyFrame[1].movDerDelX = -0.300000;
		KeyFrame[2].movDerDelX = -0.600000;
		KeyFrame[3].movDerDelX = -1.300000;
		KeyFrame[0].movDerDelY = 0.000000;
		KeyFrame[1].movDerDelY = 1.700000;
		KeyFrame[2].movDerDelY = 3.399999;
		KeyFrame[3].movDerDelY = 5.199997;
		KeyFrame[0].movDerDelZ = 0.000000;
		KeyFrame[1].movDerDelZ = 0.000000;
		KeyFrame[2].movDerDelZ = 0.000000;
		KeyFrame[3].movDerDelZ = 0.000000;
		KeyFrame[0].movIzqTrasX = 0.000000;
		KeyFrame[1].movIzqTrasX = -0.300000;
		KeyFrame[2].movIzqTrasX = -0.600000;
		KeyFrame[3].movIzqTrasX = -1.300000;
		KeyFrame[0].movIzqTrasY = 0.000000;
		KeyFrame[1].movIzqTrasY = 1.700000;
		KeyFrame[2].movIzqTrasY = 3.399999;
		KeyFrame[3].movIzqTrasY = 5.199997;
		KeyFrame[0].movIzqTrasZ = 0.000000;
		KeyFrame[1].movIzqTrasZ = 0.000000;
		KeyFrame[2].movIzqTrasZ = 0.000000;
		KeyFrame[3].movIzqTrasZ = 0.000000;

		KeyFrame[0].movDerTrasX = 0.000000;
		KeyFrame[1].movDerTrasX = -0.300000;
		KeyFrame[2].movDerTrasX = -0.600000;
		KeyFrame[3].movDerTrasX = -1.300000;
		KeyFrame[0].movDerTrasY = 0.000000;
		KeyFrame[1].movDerTrasY = 1.700000;
		KeyFrame[2].movDerTrasY = 3.399999;
		KeyFrame[3].movDerTrasY = 5.199997;
		KeyFrame[0].movDerTrasZ = 0.000000;
		KeyFrame[1].movDerTrasZ = 0.000000;
		KeyFrame[2].movDerTrasZ = 0.000000;
		KeyFrame[3].movDerTrasZ = 0.000000;

		KeyFrame[0].movPandaX = 0.000000;
		KeyFrame[1].movPandaX = -0.300000;
		KeyFrame[2].movPandaX = -0.600000;
		KeyFrame[3].movPandaX = -1.300000;
		KeyFrame[0].movPandaY = 0.000000;
		KeyFrame[1].movPandaY = 1.700000;
		KeyFrame[2].movPandaY = 3.399999;
		KeyFrame[3].movPandaY = 5.199997;
		KeyFrame[0].movPandaZ = 0.000000;
		KeyFrame[1].movPandaZ = 0.000000;
		KeyFrame[2].movPandaZ = 0.000000;
		KeyFrame[3].movPandaZ = 0.000000;

		KeyFrame[0].rotDelZ = 0.000000;
		KeyFrame[1].rotDelZ = -39.000000;
		KeyFrame[2].rotDelZ = 7.000000;
		KeyFrame[3].rotDelZ = -41.500000;

		KeyFrame[0].rotTrasZ = 0.000000;
		KeyFrame[1].rotTrasZ = 32.500000;
		KeyFrame[2].rotTrasZ = -22.500000;
		KeyFrame[3].rotTrasZ = 37.500000;




		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX , posY, posZ ));
		model = glm::translate(model, glm::vec3(5.376, 1.67, 21.387));
		model = glm::translate(model, glm::vec3(movPandaX, movPandaY, movPandaZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Panda.Draw(lightingShader);




		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX , posY, posZ));
		model = glm::translate(model, glm::vec3(5.24, 1.474, 21.669));
		model = glm::translate(model, glm::vec3(movDerDelX, movDerDelY, movDerDelZ));
		model = glm::rotate(model, glm::radians(rotDelY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotDelZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotDelX), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerDelP.Draw(lightingShader);

		
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX , posY, posZ));
		model = glm::translate(model, glm::vec3(5.235, 1.471, 21.046));
		model = glm::translate(model, glm::vec3(movIzqDelX, movIzqDelY, movIzqDelZ));
		model = glm::rotate(model, glm::radians(rotDelY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotDelZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotDelX), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqDelP.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(5.436, 0.43,21.215));
		model = glm::translate(model, glm::vec3(movDerTrasX, movDerTrasY, movDerTrasZ));

		model = glm::rotate(model, glm::radians(rotTrasY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotTrasZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTrasX), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DerTrasP.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::translate(model, glm::vec3(5.456, 0.422, 21.515));
		model = glm::translate(model, glm::vec3(movIzqTrasX, movIzqTrasY, movIzqTrasZ));

		model = glm::rotate(model, glm::radians(rotTrasY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotTrasZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(rotTrasX), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		IzqTrasP.Draw(lightingShader);


		//Monos
		KeyFrame[0].rotMono = 45.000000;
		KeyFrame[1].rotMono = -130.000000;
		KeyFrame[2].rotMono = -140.000000;
		KeyFrame[3].rotMono = -90.000000;
		KeyFrame[4].rotMono = -20.000000;
		KeyFrame[0].movMonoX = 0.000000;
		KeyFrame[1].movMonoX = 0.000000;
		KeyFrame[2].movMonoX = -0.010000;
		KeyFrame[3].movMonoX = 0.180000;
		KeyFrame[4].movMonoX = 0.000000;
		KeyFrame[0].movMonoY = 0.000000;
		KeyFrame[1].movMonoY = -0.190000;
		KeyFrame[2].movMonoY = 0.830000;
		KeyFrame[3].movMonoY = 0.989999;
		KeyFrame[4].movMonoY = -0.050000;
		KeyFrame[0].movMonoZ = 0.000000;
		KeyFrame[1].movMonoZ = -0.070000;
		KeyFrame[2].movMonoZ = 2.639998;
		KeyFrame[3].movMonoZ = 5.110022;
		KeyFrame[4].movMonoZ = 7.980088;

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(40.576, 1.297, -5.708)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(movMonoX, movMonoY, movMonoZ)); //Posicion inicial 
		model = glm::rotate(model, glm::radians(rotMono), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Mono.Draw(lightingShader);


		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ)); //Posicion inicial 
		model = glm::translate(model, glm::vec3(38.019, 1.402, -7.114)); //Posicion inicial
		model = glm::rotate(model, glm::radians(92.519f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotMonoDos), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		MonoDos.Draw(lightingShader);



		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 1);//Activacion de trasparencia
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 0.3f);//Nivel de trasparecia con valor en color alpha		
		Domo.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0f, 1.0f, 1.0f, 1.0);
		glBindVertexArray(0);

		animShader.Use();
		tiempo = glfwGetTime() * speed;
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(animShader.Program, "model");
		viewLoc = glGetUniformLocation(animShader.Program, "view");
		projLoc = glGetUniformLocation(animShader.Program, "projection");
		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(glGetUniformLocation(animShader.Program, "time"), tiempo);
		Agua.Draw(animShader);
		glBindVertexArray(0);



		




		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default




		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}



void animacion()
{


	//Movimiento del personaje

	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;


			movPandaX += KeyFrame[playIndex].movPandaX_Inc;
			movPandaY += KeyFrame[playIndex].movPandaY_Inc;
			movPandaZ += KeyFrame[playIndex].movPandaZ_Inc;


			rotDelX += KeyFrame[playIndex].rotDelX_Inc;
			rotDelY += KeyFrame[playIndex].rotDelY_Inc;
			rotDelZ += KeyFrame[playIndex].rotDelZ_Inc;

			rotTrasX += KeyFrame[playIndex].rotTrasX_Inc;
			rotTrasY += KeyFrame[playIndex].rotTrasY_Inc;
			rotTrasZ += KeyFrame[playIndex].rotTrasZ_Inc;



			movIzqDelX += KeyFrame[playIndex].movIzqDelX_Inc;
			movIzqDelY += KeyFrame[playIndex].movIzqDelY_Inc;
			movIzqDelZ += KeyFrame[playIndex].movIzqDelZ_Inc;


			movDerDelX += KeyFrame[playIndex].movDerDelX_Inc;
			movDerDelY += KeyFrame[playIndex].movDerDelY_Inc;
			movDerDelZ += KeyFrame[playIndex].movDerDelZ_Inc;

			movIzqTrasX += KeyFrame[playIndex].movIzqTrasX_Inc;
			movIzqTrasY += KeyFrame[playIndex].movIzqTrasY_Inc;
			movIzqTrasZ += KeyFrame[playIndex].movIzqTrasZ_Inc;
													 
			movDerTrasX += KeyFrame[playIndex].movDerTrasX_Inc;
			movDerTrasY += KeyFrame[playIndex].movDerTrasY_Inc;
			movDerTrasZ += KeyFrame[playIndex].movDerTrasZ_Inc;

			rotMono += KeyFrame[playIndex].rotMono_Inc;

			movMonoX += KeyFrame[playIndex].movMonoX_Inc;
			movMonoY += KeyFrame[playIndex].movMonoY_Inc;
			movMonoZ += KeyFrame[playIndex].movMonoZ_Inc;


			i_curr_steps++;
		}

	}
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (keys[GLFW_KEY_L])
	{
		if (play == false && (FrameIndex > 1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}




	}
	








	if (keys[GLFW_KEY_1])
	{

		animPuerta = !animPuerta;
				
	}

	if (keys[GLFW_KEY_2])
	{

		animCaminata = !animCaminata;
	}

	if (keys[GLFW_KEY_3])
	{

		animTrompa = !animTrompa;
	}
	if (keys[GLFW_KEY_4])
	{

		animCaida = !animCaida;
	}

	if (keys[GLFW_KEY_5])
	{

		animLevanta = !animLevanta;
	}

	
	if (keys[GLFW_KEY_6])
	{

		animJirafa = !animJirafa;
	}

	if (keys[GLFW_KEY_7])
	{

		animCoche = !animCoche;
	}

	if (keys[GLFW_KEY_8])
	{

		animTigre = !animTigre;
	}




	
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

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
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

// Moves/alters the camera positions based on user input
void DoMovement()
{


	//Configuracion color de point Light 

	LightP1 = glm::vec3(0.0f, 0.0f, 0.8f);

	//Frames Panda
	if (FrameIndex < MAX_FRAMES)
	{
		saveFrame();
	}

	//Animaciones


	//Agua
	if (AguaAnim) {
		speed = 3.5f;
	}
	//Puerta
	if (animPuerta) {
		if (rotPuerta <= 90) {
			rotPuerta += 0.1;
		}
	}

	//If para animacion el elefante
	if (animCaminata) {
		if (movEle < 5.55) {
			movEle += 0.001;
			if (rotPar < 35 && rotImp < 35 && sentidoP == false) {
				rotPar += 0.075;
				rotImp += 0.075;
				if (rotPar > 35)
					sentidoP = true;
			}

			if (rotPar > -35 && rotImp > -35 && sentidoP == true) {
				rotPar -= 0.075;
				rotImp -= 0.075;
				if (rotPar < -35)
					sentidoP = false;
			}


		}



	}


	if (animCaida) {
		if (rotFrente <= 90 && rotTras >= -90) {
			rotFrente += 0.5;
			rotTras -= 0.5;
			rotTrompa = -80;
		}

		if (movCuerpo < 1.122 && movFront < 0.966 && movBack < 0.799) {
			movCuerpo += 0.01;
			movFront += 0.0086;
			movBack += 0.00712;

		}


	}


	if (animLevanta) {
		if (rotFrenteDos <= 0 && rotTrasDos >= 0) {
			rotFrenteDos += 0.5;
			rotTrasDos -= 0.5;
			rotT = 0;
		}

		if (movCuerpoDos <= 1.189 && movFrontDos <= 0.798 && movBackDos <= 0.468 && movTrompa <= 1.537) {
			movCuerpoDos += 0.01;
			movFrontDos += 0.006635;
			movBackDos += 0.003936;
			movTrompa += 0.012926;


		}
	}


	if (animTrompa) {


		if (rotT == -90 && rotTrompaDos < 10.0f && sentido == false) {
			rotTrompaDos += 0.08f;
			if (rotTrompaDos > 10.0f)
				sentido = true;

		}


		if (rotT == -90 && rotTrompaDos > -10.0f && sentido == true)
			rotTrompaDos -= 0.025f;
		if (rotTrompaDos < -10.0f)
			sentido = false;


		if (rotT == 0 && rotTrompaL < 25 && sentido == false) {
			rotTrompaL += 0.08f;
			if (rotTrompaL > 25.0f)
				sentido = true;


		}


		if (rotT == 0 && rotTrompaL > -80 && sentido == true)
			rotTrompaL -= 0.08f;
		if (rotTrompaL < -80)
			sentido = false;


	}




	//If para animacion de la jirafa
	if (animJirafa) {
		if (movJira < 3.4 && retro == false) {
			
			movJira += 0.00125;

			if (rotParJ < 35 && rotImpJ < 35 && sentidoJ == false) {
				rotParJ += 0.075;
				rotImpJ += 0.075;
				if (rotParJ > 35)
					sentidoJ = true;
			}

			if (rotParJ > -35 && rotImpJ > -35 && sentidoJ == true) {
				rotParJ -= 0.075;
				rotImpJ -= 0.075;
				if (rotParJ < -35)
					sentidoJ = false;
			}


			if (rotJX > -39.868 && rotJZ < 63.648 && rotJY > -62.795 && movJira > 1.925 && sentidoJ == false) {
				rotJZ += 0.1197;
				rotJX -= 0.075;
				rotJY -= 0.1181;

				if (rotJX < -39.868)
					sentidoJ = true;

			}

			if (rotJX < 3.331 && sentidoJ == true) {
				rotJX += 0.5;

			}
			if (movJira >= 3.4) {
				retro = true;
			}
		}

		if (movJira >= 0.352409 && retro == true) {
			movJira -= 0.00125;
			if (rotParJ < 35 && rotImpJ < 35 && sentidoJ == false) {
				rotParJ += 0.075;
				rotImpJ += 0.075;
				if (rotParJ > 35)
					sentidoJ = true;
			}

			if (rotParJ > -35 && rotImpJ > -35 && sentidoJ == true) {
				rotParJ -= 0.075;
				rotImpJ -= 0.075;
				if (rotParJ < -35)
					sentidoJ = false;
			}

			if (movJira <= 0.352409) {
				retro = false;
				rotJZ = 0;
				rotJX = 3.5f;
				rotJY = 0;
				movJira = 0.352409;
				sentidoJ = false;
			}
		}


	}




	//Animacion coche


	if (animCoche) {
		if (movCocheZ > -45.536 && sentidoCoche == false) {
			movCocheZ -= 0.05;
			if (movCocheZ < -45.536) {
				sentidoCoche = true;

			}

		}
		if (sentidoCoche == true && rotCoche > -90) {
			rotCoche -= 0.05;

		}
		if (rotCoche < -90 && movCocheX > -2.93) {
			movCocheX -= 0.01;
		}

	}




	if (animTigre) {
		if (movTigre < 4.5) {
			movTigre += 0.001;
			if (rotParT < 35 && rotImpT < 35 && sentidoT == false) {
				rotParT += 0.075;
				rotImpT += 0.075;
				if (rotParT > 35)
					sentidoT = true;
			}

			if (rotParT > -35 && rotImpT > -35 && sentidoT == true) {
				rotParT -= 0.075;
				rotImpT -= 0.075;
				if (rotParT < -35)
					sentidoT = false;
			}


		}


		if (movTigre > 4.5) {
			if (movCuerpoT < 1.7 && rotCuerpoT > -66.157) {
				movCuerpoT += 0.01;
				rotCuerpoT -= 0.85;
				movFrontTY = 1.206;
				movFrontTX = -0.5;
				rotFronT = -40.189;
				movMandiX = 0.925;
				movMandiY = 1.5;
				rotMandi = -64.351;
			}

		}



		if (rotMandi < -40 && sentidoMandi == false) {
			rotMandi += 0.08f;
			if (rotMandi > -40)
				sentidoMandi = true;

		}


		if (rotMandi > -72 && sentidoMandi == true)
			rotMandi -= 0.025f;
		if (rotMandi < -72)
			sentidoMandi = false;

	}

	if (animTigreDos) {
		if (rotMandiDos < 15 && sentidoMandiDos == false) {
			rotMandiDos += 0.08f;
			if (rotMandiDos > 15)
				sentidoMandiDos = true;

		}


		if (rotMandiDos > -15 && sentidoMandiDos == true)
			rotMandiDos -= 0.025f;
		if (rotMandiDos < -15)
			sentidoMandiDos = false;




		if (rotCola < 90 && sentidoCola == false) {
			rotCola += 0.05;
			if (rotCola > 90)
				sentidoCola = true;

		}


		if (rotCola > 0 && sentidoCola == true)
			rotCola -= 0.05;
		if (rotCola < 0)
			sentidoCola = false;



		if (rotCL < 25 && sentidoColaDos == false) {
			rotCL += 0.05;
			if (rotCL > 25)
				sentidoColaDos = true;

		}


		if (rotCL > -25 && sentidoColaDos == true)
			rotCL -= 0.05;
		if (rotCL < -25)
			sentidoColaDos = false;

	}




	if (animMono) {

		if (rotMonoDos < 25 && sentidoMono == false) {
			rotMonoDos += 0.08f;
			if (rotMonoDos > 25.0f)
				sentidoMono = true;


		}


		if (rotMonoDos > -25 && sentidoMono == true)
			rotMonoDos -= 0.08f;
		if (rotMonoDos < -25)
			sentidoMono = false;

	}

	

















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



}

