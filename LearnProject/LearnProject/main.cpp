#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) ->void{
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
	auto clearWithColor = []() -> void{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ״̬����
		glClear(GL_COLOR_BUFFER_BIT); // ״̬ʹ��
	};

	// ����VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��VAO
	glBindVertexArray(VAO);

	float vertices[] = {
		-0.5f, 0.5f, 0.0f, //
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f, //
		 0.5f, 0.5f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	//�����������VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//�󶨻�����󵽶��㻺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���������ݸ��Ƶ������ڴ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���Ӷ�������, ��ʼλ�ã��������Դ�С���������ͣ� �Ǳ�׼���� ������ ��ʼλ��ƫ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ���ö�������
	glEnableVertexAttribArray(0);

	// �����������EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ������ɫ��Դ����
	auto vertexShaderSource = R"(
	#version 330 core
	layout (location = 0) in vec3 aPos;
	void main()
	{
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	}
	)";
	// ������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Դ�븽�ŵ���ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// ������
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ƬԪ��ɫ��Դ��
	auto fragmentShaderSource = R"(
	#version 330 core
	out vec4 FragColor;
	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
	)";
	// ƬԪ��ɫ������
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// ��ɫ������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// �߿�ģʽ
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		clearWithColor();

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6); // ����������ʼ������������Ŀ��ֱ�Ӵ�VBO�л�ȡֻ�ܻ���һ��������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ��������EBOƫ����
		glBindVertexArray(0);
	}

	// �ͷų�ʼ��ʱ�������Դ
	glfwTerminate();
	return 0;
}