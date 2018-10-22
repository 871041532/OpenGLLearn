#include "Shader.h"


Shader::Shader(const GLchar * vertex_path, const GLchar * fragment_path)
{
	// 1.从路径中获取顶点片段着色器
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// 打开文件
		vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();
		// 转换数据流到string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2.编译着色器
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

	}
	catch (const std::istream::failure& e)
	{
		std::cout << "ERROR: SHADER_FILE_READ_FAILD" << std::endl;
	}
}

void Shader::use()
{
}

void Shader::setBool(const std::string & name, bool value) const
{
}

void Shader::setInt(const std::string & name, int value) const
{
}

void Shader::setFloat(const std::string & name, float value) const
{
}
