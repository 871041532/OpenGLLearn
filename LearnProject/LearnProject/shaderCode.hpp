#ifndef SHADERCODE_HPP
#define SHADERCODE_HPP


namespace ShaderCode
{
	const char* vertex_code = R"(

#version 330 core
layout (location = 0) in vec3 aPos;  // 位置变量属性值为0
layout (location = 1) in vec3 aColor;  //  
out vec3 ourColor;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor;
}

	)";

	const char* fragment_code = R"(

#version 330 core
in vec3 ourColor;
out vec4 FragColor;
void main()
{
	FragColor = vec4(ourColor, 1.0);
}

	)";
}

#endif // !SHADERCODE_HPP