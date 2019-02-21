	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec3 ourColor;
	uniform float xOffset;
	out vec3 newPos;
	void main()
	{
		// 1.�޸Ķ�����ɫ�������������µߵ�
		// 2.ʹ��uniform����ˮƽƫ����
		gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
		ourColor = aColor;
		newPos = aPos;
	}