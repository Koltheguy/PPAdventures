#pragma once
#include <glad/glad.h>

class GameObject {
public:
    virtual ~GameObject() {} 

    virtual void draw() = 0;
    virtual void render() = 0;
};