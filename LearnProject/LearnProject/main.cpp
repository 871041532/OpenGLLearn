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

	//顶点(不重复)
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f,   // 左上角
	};
	//索引
	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3,
	};

	//VAO: 顶点数组对象（存储的是调用）, 任何随后的顶点属性调用都会储存在这个VAO中
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	//VBO: 顶点缓冲对象, 把顶点数组复制到缓冲中供OpenGL使用
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//EBO:顶点索引缓冲
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//设置顶点属性指针 参数:起始位置，向量维度，数据类型，是否标准化，步长，缓冲区偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	//创建着色器程序
	unsigned int shaderProgram;
	create_shader_program(&shaderProgram);
	//线框模式绘制三角形
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		//随时间变换颜色
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		// 输入
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);  // 顶点索引从0开始，一共3个顶点
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // 顶点个数，EBO中偏移量
		glBindVertexArray(0);  //保证其他调用不会修改VAO
		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

// 着色器程序
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

// 顶点着色器
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

//片元着色器
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