#include "Game.h"


//Private Functions

void Game::initGLFW()
{
	if (glfwInit() == GLFW_FALSE) //Init GLFW
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::InitWindow(
	const char *title,
	bool resizable
)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);
	glfwSetFramebufferSizeCallback(window, Game::framebuffer_resize_callback);

	glfwMakeContextCurrent(this->window);
}
void Game::initGLEW()
{
	//INIT GLEW(NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error::MAIN.CPP::GLEW" << "\n";
		glfwTerminate();
	}
}

void Game::initOpenGLOptions()
{
					   //WINDOW//
	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

					   //MOUSE//
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


}

void Game::initMatrices()
{
	//ModelMatrix VIEW
	this->ViewMatrix = glm::mat4(1.f);
	this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);	
	this->ProjectionMatrix = glm::mat4(1.f);

	this->ProjectionMatrix = glm::mat4(1.f); //QUIZAS ESTO NO SIRVA
	this->ProjectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->NearPlane,
		this->FarPlane);
	//End of ModelMatrix VIEW
}

void Game::initShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR,
		this->GL_VERSION_MINOR,
		"vertex_core.glsl", "fragment_core.glsl"));

}

void Game::initTextures()
{
	//TEXTURE 0

	this->textures.push_back(new Texture("Sprites_and_textures/Tex_Box.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Sprites_and_textures/Tex_Box_SpecularMap.png", GL_TEXTURE_2D));

	this->textures.push_back(new Texture("Sprites_and_textures/back.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Sprites_and_textures/f2.png", GL_TEXTURE_2D));

	//TEXTURE 1

	/*this->textures.push_back(new Texture("Sprites_and_textures/back.png", GL_TEXTURE_2D));
	this->textures.push_back(new Texture("Sprites_and_textures/Tex_Box_SpecularMap.png", GL_TEXTURE_2D));*/
}

void Game::initMaterials()
{
	//MATERIAL 0TEX_F2_1
	this->materials.push_back(new Material(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(2.f), 0, 1));
}

void Game::initOBJModels()
{
	std::vector<Vertex> temp;
	temp = loadOBJ("3DModels/Wooden_box_01_Cube.obj");
}



void Game::initModels_Quad()
{
	std::vector<Mesh*>meshes;

	


	meshes.push_back(
		new Mesh(
			&Quad(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	//FINAL MODELS (Positions)
	this->models.push_back(new Model(
		glm::vec3(0.f, 0.f, 0.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(0.f, 0.f, 1.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(0.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	/////////////////////

	this->models.push_back(new Model(
		glm::vec3(1.f, 0.f, 0.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(1.f, 0.f, 1.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(1.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	/////////////////////////////////////////////77
	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 0.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 1.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);
	 
	////////////////////////////////////////7///

	this->models.push_back(new Model(
		glm::vec3(3.f, 0.f, 0.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(3.f, 0.f, 1.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(3.f, 0.f, 2.f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	for (auto *&i : meshes)
		delete i;

}
void Game::initModels_Pyramid()
{
	std::vector<Mesh*>meshes;

	meshes.push_back(
		new Mesh(
			&Pyramid(),
			glm::vec3(0.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
		)
	);

	
	
	 //FINAL MODELS (Positions)
	this->models.push_back(new Model(
		glm::vec3(0.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(1.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(2.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);



	this->models.push_back(new Model(
		glm::vec3(3.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(4.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	this->models.push_back(new Model(
		glm::vec3(5.f, 0.f, -0.5f),
		this->materials[0],
		this->textures[TEX_BACK_0],
		this->textures[TEX_BACK_SPECULAR],
		meshes
	)
	);

	for (auto *&i : meshes)
		delete i;

	
}

void Game::initLights()
{
	this->lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::initUniforms()
{
	//1.4 INIT UNIFORMS

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
	

	// End UNIFORMS
}

void Game::updateUniforms() //Sends ALL to the GPU
{
	//Update View Matrix (camera)
	this->ViewMatrix = this->camera.getViewMatrix();

	this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
	this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

	//Update framebuffer size and projections matrix
	glfwGetFramebufferSize(this->window, &this->frameBufferWidth, &this->frameBufferHeight);

	this->ProjectionMatrix = glm::perspective(glm::radians(this->fov), static_cast<float>(this->frameBufferWidth) / this->frameBufferHeight,
		this->NearPlane, this->FarPlane);

	
}

//Construtor and Destructor
Game::Game(
	const char *title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
	//Init variables
	this->window = nullptr;
	this->frameBufferWidth = this->WINDOW_WIDTH;
	this->frameBufferHeight = this->WINDOW_HEIGHT;

							//ModelMatrix VIEW
	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	 

			
	this->fov = 90.f; 
	this->NearPlane = 0.1f;
	this->FarPlane = 1000.f;


	this->deltaTi = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;

	this->lastMouseX = 0.0;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;

						//End of ModelMatrix VIEW

	this->initGLFW();
	this->InitWindow(title, resizable);
	this->initGLEW();
	this->initOpenGLOptions();
	this->initMatrices();
	this->initShaders();
	this->initTextures();
	this->initMaterials();
	this->initOBJModels();
	this->initModels_Pyramid();
	this->initModels_Quad();
	
	this->initLights();
	this->initUniforms();
}


Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
	{
		delete this->shaders[i];
	}
	for (size_t i = 0; i < this->textures.size(); i++)
	{
		delete this->textures[i];
	}
	for (size_t i = 0; i < this->materials.size(); i++)
	{
		delete this->materials[i];
	}
	

	for (auto*& i : this->models)
		delete i;

	for (size_t i = 0; i < this->lights.size(); i++)
	{
		delete this->lights[i];
	}
}






//Accessor

int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//Modifier

void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}



//Functions

void Game::updateDeltaT()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->deltaTi = this->curTime - this->lastTime;
	this->lastTime = this->curTime;

	/*std::cout << "DT: " << this->deltaTi << "/n";
	std::cout << "MouseOffsetX: " << this->mouseOffsetX << "/n";
	std::cout << " Mouse OffsetY: " << this->mouseOffsetY << "/n";*/
}

void Game::updateMouseInput()
{
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if (this->firstMouse)
	{
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	//Calc offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->mouseY - this->lastMouseY;

	//Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;
}

void Game::updateKeyboardInput()
{
	//Program
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	//Camera
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTi, FORWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTi, BACKWARD);
	}
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTi, LEFT);
	}
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->camera.move(this->deltaTi, RIGHT);
	}

	if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		this->camPosition.y += 0.002f;
	}
	if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
	{
		this->camPosition.y -= 0.002f;
	}
}

void Game::updateInput() //Updates CONTROLS
{

	glfwPollEvents();

	this->updateKeyboardInput();
	this->updateMouseInput();
	this->camera.updateInput(deltaTi, -1, this->mouseOffsetX, this->mouseOffsetY);
	
}

void Game::update()
{
	//UPDATE INPUT --- 
	this->updateDeltaT();
	this->updateInput();

	/*this->models[0]->rotate(glm::vec3(0.f, 1.f, 0.f));
	this->models[1]->rotate(glm::vec3(0.f, 2.f, 0.f));
	this->models[2]->rotate(glm::vec3(1.f, 1.f, 0.f));*/
}

void Game::render()
{	
	
	//UPDATE ---
	

	//DRAW ---/////////////////////////////////////////////////////////////////////////////

	//Clear
	glClearColor(0.f, 0.f, 0.f, 1.f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	//update the uniforms
	this->updateUniforms();

	//Render Models

	for(auto&i : this->models)
		i->render(this->shaders[SHADER_CORE_PROGRAM]);

	

	//End Draw
	glfwSwapBuffers(window);
	glFlush();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


//Static functions
void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) //Function that Resizes Viewport
{
	glViewport(0, 0, fbW, fbH);
}