	#version 330 core
	out vec4 FragColor;
	in vec3 ourColor;
	in vec3 newPos;
	void main()
	{
	    // 使用out关键字把顶点位置输出到片段着色器, 左下角是黑的是因为，rgba负数取0
		FragColor = vec4(newPos, 1.0);
		// FragColor = vec4(ourColor, 1.0);
	}