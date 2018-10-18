#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderCode.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void create_vertex_shader(unsigned int* shader_id);
void create_fragment_shader(unsigned int* shader_id);
void create_shader_program(unsigned int* shaderProgram);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize Glad" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//����(���ظ�)
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f,   // ���Ͻ�
	};
	//����
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3,
	};

	//VAO: ����������󣨴洢���ǵ��ã�, �κ����Ķ������Ե��ö��ᴢ�������VAO��
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//VBO: ���㻺�����, �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//EBO:������������
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//���ö�������ָ�� ����:��ʼλ�ã�����ά�ȣ��������ͣ��Ƿ��׼����������������ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//������ɫ������
	unsigned int shaderProgram;
	create_shader_program(&shaderProgram);
	//�߿�ģʽ����������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		//��ʱ��任��ɫ
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		// ����
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);  // ����������0��ʼ��һ��3������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // ���������EBO��ƫ����
		glBindVertexArray(0);  //��֤�������ò����޸�VAO
		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

// ��ɫ������
void create_shader_program(unsigned int* shaderProgram)
{
	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;
	create_vertex_shader(&vertexShader);
	create_fragment_shader(&fragmentShader);
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	int success = 0;
	char infoLog[512];
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		cout << "GLPROGRAM LINK SHADER ERROR:\n" << infoLog << endl;
	}
	else
	{
		cout << "GLPROGRAM LINK SHADER SUCCESS" << endl;
	}
}

// ������ɫ��
void create_vertex_shader(unsigned int* vertexShader) {
	const char* vertexShaderSource = ShaderCode::vertex_code;
	// unsigned int vertexShader;
	*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(*vertexShader);
	int sucess;
	char infoLog[512];
	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
		cout << "ERROE: SHADER VERTEX COMPILATION_FAILED\n" << infoLog << endl;
	}
	else
	{
		cout << "SHADER VERTEX COMPILATION_SUCCESS" << endl;
	}
}

//ƬԪ��ɫ��
void create_fragment_shader(unsigned int* fragmentShader)
{
	const char* fragmentShaderSource = ShaderCode::fragment_code;
	// unsigned int fragmentShader;
	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(*fragmentShader);
	int sucess;
	char infoLog[512];
	glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
		cout << "ERROE: SHADER FRAGMENT COMPILATION_FAILED\n" << infoLog << endl;
	}
	else
	{
		cout << "SHADER FRAGMENT COMPILATION_SUCCESS" << endl;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}