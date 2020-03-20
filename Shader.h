#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<glew.h>
#include<glfw3.h>
#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>


class Shader
{
private:
	//Member Variables
	GLuint id;
	
	const int versionMajor;
	const int versionMinor;

	//Private functions
	std::string loadShaderSource(char *fileName) //This function loads and reads the source file of the shader
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file; //Declaration of the name of the file

		//Vertex
		in_file.open(fileName); // Opens the file

		if (in_file.is_open()) //It checks if the file was successfully opened
		{
			while (std::getline(in_file, temp))  //extracts characters until the given character is found inside this file
				src += temp + "\n";
		}
		else //If not...then gets error
		{
			std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE " << fileName << "\n";
			
		}


		in_file.close(); //Closes file

		std::string versionNr =
			std::to_string(this->versionMajor) +
			std::to_string(this->versionMinor) +
			"0";

		src.replace(src.find("#version"), 12, ("#version " + versionNr));
		

		return src;
	}

	GLuint loadShader(GLenum type, char *fileName)
	{
		
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type); //Declaration of Vertex_Shader
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR LOADING SHADERS COULD NOT BE DONE " << fileName << "\n";
			std::cout << infoLog << "\n";
			
		}
		return shader;
	}

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;
		this->id = glCreateProgram();
		

		glAttachShader(this->id, vertexShader);


		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}

		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);

		glGetProgramiv(this->id, GL_LINK_STATUS, &success);  //Query of the success of the Shader's linking operation

		if (!success) // And if thequery was not successful then...
		{
			glGetShaderInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR LOADING PROGRAM COULD NOT BE DONE" << "\n";
			std::cout << infoLog << "\n";
			
		}

		glUseProgram(0);

	}
public:
	//Constructors/Destructors

	
	Shader(const int versionMajor, const int versionMinor, char *vertexFile, char *fragmentFile, char *geometryFile = "")
		: versionMajor(versionMajor), versionMinor(versionMinor)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

		if (geometryFile != "")
		{
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}

		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);
		this->linkProgram(vertexShader, geometryShader, fragmentShader);

		//End
		
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
		
	}
	
	~Shader()
	{
		glDeleteProgram(this->id);
	}

	//Set uniform functions
	void use()
	{
		glUseProgram(this->id);
	}

	void unuse()
	{
		glUseProgram(0);
	}

	void set1i(GLint value, const GLchar *name)
	{
		this->use();

		glUniform1i(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	

	void set1f(GLfloat value, const GLchar *name)
	{
		this->use();

		glUniform1f(glGetUniformLocation(this->id, name), value);

		this->unuse();
	}

	void setVec2f(glm::fvec2 value, const GLchar *name)
	{
		this->use();

		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec3f(glm::fvec3 value, const GLchar *name)
	{
		this->use();

		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setVec4f(glm::fvec4 value, const GLchar *name)
	{
		this->use();

		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));

		this->unuse();
	}

	void setMat3fv(glm::mat3 value, const GLchar *name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}

	void setMat4fv(glm::mat4 value, const GLchar *name, GLboolean transpose = GL_FALSE)
	{
		this->use();

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));

		this->unuse();
	}
};