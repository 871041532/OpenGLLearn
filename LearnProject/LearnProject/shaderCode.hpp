#ifndef file_shaderCode
#define file_shaderCode

namespace ShaderCode
{
	const char* vertex_code = R"(

#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertexColor =  vec4(0.5, 0.0, 0.5, 1.0);
}

	)";

	const char* fragment_code = R"(

#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;
void main()
{
	FragColor = ourColor;
}

	)";
}




#endif // !shader.hpp
