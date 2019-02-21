#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
int main()
{
	glfwInit();
	// 设置大版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// 设置小版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 使用核心模式(不向后兼容)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 初始化glfw
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// 根据编译的地址初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// 设置视口大小以及回调函数
	glViewport(0, 0, 800, 600);
	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) ->void {
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// 输入控制
	auto processInput = [](GLFWwindow* window) ->void {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	};
	// 颜色清空屏幕
	auto clearWithColor = []() -> void {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置
		glClear(GL_COLOR_BUFFER_BIT); // 状态使用
	};

	// 创建VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 绑定VAO
	glBindVertexArray(VAO);

	float vertices[] = {
		// 位置               // 颜色
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};


	//创建缓冲对象VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//绑定缓冲对象到顶点缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 将顶点数据复制到缓冲内存
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 链接顶点属性, 起始位置，顶点属性大小，数据类型， 非标准化， 步长， 起始位置偏移量
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unsigned int indices[] = {0, 1, 2};
	//unsigned int EBO;	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader ourShader("1.3.3practice.vs", "1.3.3practice.fs");
	// 设置渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		clearWithColor();

		ourShader.use();
		// 设置着色器颜色
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		ourShader.setFloat("xOffset", 0.5f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // 顶点数组起始索引，顶点数目。直接从VBO中获取只能绘制一个三角形
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	// 释放初始化时分配的资源
	glfwTerminate();
	return 0;
}