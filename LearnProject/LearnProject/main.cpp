#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <direct.h>
using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "ShaderCode.hpp"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& mixValue);
void create_vertex_shader(unsigned int* shader_id);
void create_fragment_shader(unsigned int* shader_id);
void create_shader_program(unsigned int* shaderProgram);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL", NULL, NULL);
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
	glViewport(0, 0, 600, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 顶点(不重复)
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.88f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.88f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.88f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.88f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};
	// 顶点索引
	unsigned int indices[] =
	{
		//0, 1, 2, 0, 2, 3,
		0, 1, 3, 1, 2, 3,
	};
	// VAO: 顶点数组对象（存储的是调用）, 任何随后的顶点属性调用都会储存在这个VAO中
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// VBO: 顶点缓冲对象, 把顶点数组复制到缓冲中供OpenGL使用
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// EBO:顶点索引缓冲
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// 设置顶点属性指针 参数:起始位置，向量维度，数据类型，是否标准化，步长，缓冲区偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  // 对应了定点着色器中的location 0
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);  // 对应了定点着色器中的location 1
	// 纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	char path[500];
	_getcwd(path, 500);
	cout << "Work Path: " << path << endl;
	string vPath = string(path) + "/resource/shader/vertex/vertex02_texture.shader";
	string fPath = string(path) + "/resource/shader/fragment/fragment02_texture.shader";
	Shader shader = Shader(vPath.c_str(), fPath.c_str());

	stbi_set_flip_vertically_on_load(true);
	// 生成纹理
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置，纹理环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// 为当前绑定的纹理对象设置，纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// mipmap过滤 (只用于缩小的情况)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// 载入图片生成纹理
	string texturePath = string(path) + "/resource/texture/renwang.jpg";
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// 第二个纹理
	// 生成纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// 为当前绑定的纹理对象设置，纹理环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// 为当前绑定的纹理对象设置，纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// mipmap过滤 (只用于缩小的情况)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// 载入图片生成纹理
	string texturePath2 = string(path) + "/resource/texture/wall.jpg";
	data = stbi_load(texturePath2.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//线框模式绘制三角形
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float mixValue = 0.2;
	while (!glfwWindowShouldClose(window))
	{
		//随时间变换颜色
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

		// 输入
		processInput(window, mixValue);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);
		shader.setFloat("mixValue", mixValue);
		shader.use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);	
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(VAO);	
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);  // EBO顶点个数，EBO中偏移量
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float& mixValue)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01;
		mixValue = mixValue > 0 ? mixValue : 0;
		mixValue = mixValue < 1 ? mixValue : 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01;
		mixValue = mixValue > 0 ? mixValue : 0;
		mixValue = mixValue < 1 ? mixValue : 1;
	}
}