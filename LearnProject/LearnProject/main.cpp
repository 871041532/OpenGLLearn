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
	// ������Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
		clearWithColor();
	}

	// �ͷų�ʼ��ʱ�������Դ
	glfwTerminate();
	return 0;
}