#pragma once

#include <cmath>

#include "glad/glad.h"

// 确保使用标准的 GLM 库函数
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    // 相机属性
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // 相机参数
    float Yaw;
    float Pitch;

    // 相机移动速度
    float MovementSpeed;

    // 构造函数，使用默认值
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) : MovementSpeed(2.5f) {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // 获取 View 矩阵
    glm::mat4 getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // 更新相机位置
    void setPosition(glm::vec3 position) {
        Position = position;
    }

    // 移动相机
    void moveForward(float deltaTime) {
        Position += Front * MovementSpeed * deltaTime;
    }

    void moveBackward(float deltaTime) {
        Position -= Front * MovementSpeed * deltaTime;
    }

    void moveLeft(float deltaTime) {
        Position -= Right * MovementSpeed * deltaTime;
    }

    void moveRight(float deltaTime) {
        Position += Right * MovementSpeed * deltaTime;
    }

private:
    // 更新相机的方向向量
    void updateCameraVectors() {
        // 计算新的 Front 向量
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        // 重新计算 Right 和 Up 向量
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};