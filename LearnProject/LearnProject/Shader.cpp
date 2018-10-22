#include "Shader.h"


Shader::Shader(const GLchar * vertex_path, const GLchar * fragment_path)
{
	// 1.��·���л�ȡ����Ƭ����ɫ��
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ��֤ifstream��������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// ���ļ�
		vShaderFile.open(vertex_path);
		fShaderFile.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;
		// ��ȡ�ļ��Ļ������ݵ���������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// �ر��ļ�������
		vShaderFile.close();
		fShaderFile.close();
		// ת����������string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2.������ɫ��
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
