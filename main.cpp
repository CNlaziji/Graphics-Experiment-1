// 覆盖 GLAPI 宏，避免 dllimport
#define GLAPI

#include "glad/glad.h"
#include "vcpkg/glfw/include/GLFW/glfw3.h"

#include "Shader.h"
#include "Camera.h"

#include <cmath>
#include <iostream>

// 确保使用标准的 GLM 库函数
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// 转换函数：将 glm::mat4 转换为自定义 mat4 结构体（用于保持与现有代码的兼容性）
struct mat4 {
    float data[16];
    mat4() {
        for (int i = 0; i < 16; i++) data[i] = 0;
        data[0] = data[5] = data[10] = data[15] = 1;
    }
    mat4(float s) {
        for (int i = 0; i < 16; i++) data[i] = 0;
        data[0] = data[5] = data[10] = data[15] = s;
    }
};

// 转换函数：将 glm::mat4 转换为自定义 mat4
mat4 fromGlmMat4(const glm::mat4& glmMat) {
    mat4 m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m.data[i * 4 + j] = glmMat[i][j];
        }
    }
    return m;
}

// 转换函数：将自定义 mat4 转换为 glm::mat4
glm::mat4 toGlmMat4(const mat4& m) {
    glm::mat4 glmMat;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            glmMat[i][j] = m.data[i * 4 + j];
        }
    }
    return glmMat;
}

#include <iostream>

// 窗口大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 相机
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// 时间变量
float deltaTime = 0.0f; // 两帧之间的时间差
float lastFrame = 0.0f; // 上一帧的时间

// 投影切换变量
bool isPerspective = true;

// Transform 接口
class Transform {
private:
    mat4 modelMatrix;

public:
    Transform() : modelMatrix(mat4(1.0f)) {}

    // 获取模型矩阵
    mat4 getModelMatrix() {
        return modelMatrix;
    }

    // TODO: 成员 A 负责 2D 绘制逻辑
    // TODO: 成员 B 负责 2D 变换，包括缩放、反射、切变、旋转、平移
    // TODO: 成员 C 负责 2D 组合变换
    // TODO: 成员 E 负责 3D 图形绘制
    // TODO: 成员 F 负责 3D 变换，包括缩放、平移、绕 x/y/z 轴旋转
    // TODO: 成员 G 负责 3D 组合变换

    // 预留变换逻辑区域
    void applyTransforms() {
        // 重置模型矩阵
        modelMatrix = mat4(1.0f);

        // TODO: 在这里添加平移变换
        // modelMatrix = translate(modelMatrix, vec3(x, y, z));

        // TODO: 在这里添加旋转变换
        // modelMatrix = rotate(modelMatrix, angle, vec3(x, y, z));

        // TODO: 在这里添加缩放变换
        // modelMatrix = scale(modelMatrix, vec3(x, y, z));

        // TODO: 在这里添加切变变换
        // mat4 shear = mat4(1.0f);
        // shear.data[1] = shearFactor; // 水平切变
        // shear[1][0] = shearFactor; // 垂直切变
        // modelMatrix = modelMatrix * shear;

        // TODO: 在这里添加反射变换
        // mat4 reflection = mat4(1.0f);
        // reflection.data[0] = -1.0f; // 关于 y 轴反射
        // modelMatrix = modelMatrix * reflection;
    }
};

// 全局变换对象
Transform transform;

// 处理输入的函数
void processInput(GLFWwindow* window) {
    // 关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // TODO: 成员 D 负责相机移动集成
    // 相机移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveForward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft(deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight(deltaTime);

    // 投影切换
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        isPerspective = true;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        isPerspective = false;
}

// 窗口大小变化回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // 初始化 GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 实验工程模板", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 初始化 GLAD
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 定义着色器代码
    const std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        out vec3 FragPos;
        
        void main() {
            FragPos = aPos;
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        in vec3 FragPos;
        
        void main() {
            // 根据片段位置为不同面分配不同颜色
            vec3 color = vec3(1.0f, 0.5f, 0.2f); // 默认颜色
            
            // 为不同面分配不同颜色
            if (abs(FragPos.x) > 0.49) {
                color = vec3(1.0f, 0.0f, 0.0f); // 红色 - X轴方向的面
            } else if (abs(FragPos.y) > 0.49) {
                color = vec3(0.0f, 1.0f, 0.0f); // 绿色 - Y轴方向的面
            } else if (abs(FragPos.z) > 0.49) {
                color = vec3(0.0f, 0.0f, 1.0f); // 蓝色 - Z轴方向的面
            }
            
            FragColor = vec4(color, 1.0f);
        }
    )";

    // 创建着色器对象
    Shader shader(vertexShaderSource, fragmentShaderSource);

    // 定义顶点数据（一个简单的立方体）
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    // 创建顶点缓冲对象 (VBO) 和顶点数组对象 (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 绑定 VAO
    glBindVertexArray(VAO);

    // 绑定 VBO 并填充数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 计算时间差
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 处理输入
        processInput(window);

        // 清除颜色和深度缓冲区
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用着色器
        shader.use();

        // 应用变换
        transform.applyTransforms();

        // 获取模型矩阵
        mat4 model = transform.getModelMatrix();

        // 获取视图矩阵
        glm::mat4 view = camera.getViewMatrix();

        // 获取投影矩阵
        mat4 projection;
        if (isPerspective) {
            glm::mat4 glmProj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            projection = fromGlmMat4(glmProj);
        } else {
            glm::mat4 glmProj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
            projection = fromGlmMat4(glmProj);
        }

        // 设置 uniform 变量
        shader.setMat4("model", toGlmMat4(model));
        shader.setMat4("view", view);
        shader.setMat4("projection", toGlmMat4(projection));

        // 绘制立方体
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 交换缓冲区并处理事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 清理资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // 终止 GLFW
    glfwTerminate();
    return 0;
}