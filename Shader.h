#pragma once

#include <string>
#include "glm/glm.hpp"

class Shader {
public:
    unsigned int ID;

    // 构造函数：从文件路径读取着色器
    Shader(const char* vertexPath, const char* fragmentPath);

    // 构造函数：从字符串读取着色器
    Shader(const std::string& vertexCode, const std::string& fragmentCode);

    // 使用/激活程序
    void use();

    // 工具函数：设置 uniform 变量
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

private:
    // 检查着色器编译/链接错误的辅助函数
    void checkCompileErrors(unsigned int shader, std::string type);
};