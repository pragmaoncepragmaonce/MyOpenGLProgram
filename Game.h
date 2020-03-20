#pragma once
#include"libs.h"
#include "Camera.h"	
#include "OBJLoader.h";

enum shader_enum{ SHADER_CORE_PROGRAM = 0};
enum texture_enum { TEX_BACK_0 = 0, TEX_BACK_SPECULAR, TEX_F2_1, TEX_F2_1_SPECULAR}; //quizas se elimine el 0
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD0 = 0};

class Game
{
private:
	//Variables
	   //window
	GLFWwindow *window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int frameBufferWidth;
	int frameBufferHeight;


	   //OpenGL Context (content)
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

					//Delta
	float deltaTi;
	float curTime;
	float lastTime;
					//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	//END OF OpenGL Context (content)

	//Camera
	Camera camera;

	//Matrices
	glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::mat4 ProjectionMatrix;

	float fov;
	float NearPlane;
	float FarPlane;

	//Shaders
	std::vector<Shader*> shaders;

	//Textures
	std::vector<Texture*> textures;

	//Materials
	std::vector<Material*> materials;

	


	//Models
	std::vector<Model*> models;

	//Lights
	std::vector<glm::vec3*> lights;

	//Private Functions

	void initGLFW(); //1-First init GLFW
	void InitWindow( //2-Then create the window
	const char *title,	
	bool resizable
	);
	void initGLEW(); //3-AFTER window CONTEXT CREATION
	void initOpenGLOptions();
	void initMatrices();
	void initShaders();
	void initTextures();
	void initMaterials();

	void initOBJModels();
	void initModels_Pyramid();
	void initModels_Quad();


	void initLights();
	void initUniforms();

	void updateUniforms();


	//Static Variables

public:
	//Construtor and Destructor
	Game(
		const char *title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable
	);
	virtual ~Game();
	//Accessors

	int getWindowShouldClose();

	//Modifiers

	void setWindowShouldClose();

	//Functions
	void updateDeltaT();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void update(); 
	void render();

	//Static Functions
	static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
	
};

