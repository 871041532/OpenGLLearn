#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"
int main()
{
	glfwInit();
	// ���ô�汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// ����С�汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ʹ�ú���ģʽ(��������)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ��ʼ��glfw
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// ���ݱ���ĵ�ַ��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// �����ӿڴ�С�Լ��ص�����
	glViewport(0, 0, 800, 600);
	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) ->void {
		glViewport(0, 0, width, height);
	};
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// �������
	auto processInput = [](GLFWwindow* window) ->void {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	};
	// ��ɫ�����Ļ
	auto clearWithColor = []() -> void {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ״̬����
		glClear(GL_COLOR_BUFFER_BIT); // ״̬ʹ��
	};

	// ����VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��VAO
	glBindVertexArray(VAO);

	float vertices[] = {
		// λ��               // ��ɫ
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};


	//�����������VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//�󶨻�����󵽶��㻺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���������ݸ��Ƶ������ڴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���Ӷ�������, ��ʼλ�ã��������Դ�С���������ͣ� �Ǳ�׼���� ������ ��ʼλ��ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//unsigned int indices[] = {0, 1, 2};
	//unsigned int EBO;	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader ourShader("1.3.3practice.vs", "1.3.3practice.fs");
	// ������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		clearWithColor();

		ourShader.use();
		// ������ɫ����ɫ
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		ourShader.setFloat("xOffset", 0.5f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // ����������ʼ������������Ŀ��ֱ�Ӵ�VBO�л�ȡֻ�ܻ���һ��������
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	// �ͷų�ʼ��ʱ�������Դ
	glfwTerminate();
	return 0;
}