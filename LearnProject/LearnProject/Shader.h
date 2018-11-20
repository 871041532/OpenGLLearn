#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// ����ID
	unsigned int ID;

public:
	// ��������ȡ��������ɫ��
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);
	// ʹ�ü������
	void use();
	// uniform���ߺ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4fv(const std::string& name, const GLfloat* value_ptr) const;
};

#endif
