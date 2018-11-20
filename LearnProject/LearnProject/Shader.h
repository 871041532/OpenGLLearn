#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// 程序ID
	unsigned int ID;

public:
	// 构造器读取并构建着色器
	Shader(const GLchar* vertex_path, const GLchar* fragment_path);
	// 使用激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4fv(const std::string& name, const GLfloat* value_ptr) const;
};

#endif
