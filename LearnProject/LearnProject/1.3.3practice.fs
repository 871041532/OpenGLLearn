	#version 330 core
	out vec4 FragColor;
	in vec3 ourColor;
	in vec3 newPos;
	void main()
	{
	    // ʹ��out�ؼ��ְѶ���λ�������Ƭ����ɫ��, ���½��Ǻڵ�����Ϊ��rgba����ȡ0
		FragColor = vec4(newPos, 1.0);
		// FragColor = vec4(ourColor, 1.0);
	}