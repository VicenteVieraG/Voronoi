#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include <graphics.hpp>

namespace Graphics{
    Global::Global(){
        // this->createShader();
        // this->initBuffers();
        this->loadShaderFile("./shaders/vertexShader.glsl");
        this->loadShaderFile("./shaders/fragmentShader.glsl");
    }
    Global::~Global(){
        gl::glDeleteBuffers(1, &this->vbo);
        gl::glDeleteVertexArrays(1, &this->vao);
        gl::glDeleteProgram(this->shaderProgram);
    }

    void Global::initBuffers(){}
    void Global::updateBufferData(){}

    void Global::createShader(){std::cout<<"createShader()\n";}

    const std::string Global::loadShaderFile(const std::string& filePath){
        std::ifstream shaderFile(filePath);
        if(!shaderFile) return "";

        std::stringstream fileBuffer;
        fileBuffer<<shaderFile.rdbuf();

        const std::string shaderContent = fileBuffer.str();
        return shaderContent;
    }
};


// void Global::initBuffers(){
//     /* ~~Initialize VAO and VBO~~ */
//     gl::glGenVertexArrays(1, &this->vao);
//     gl::glBindVertexArray(this->vao);

//     gl::glGenBuffers(1, &this->vbo);
//     gl::glBindBuffer(gl::GL_ARRAY_BUFFER, vbo);
//     // gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(this->points), this->points, gl::GL_STATIC_DRAW);

//     // Configure vertex attributes
//     gl::glEnableVertexAttribArray(0);
//     gl::glVertexAttribPointer(0, 2, gl::GL_FLOAT, gl::GL_FALSE, 0, nullptr);

//     // Security unbind
//     // gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
//     gl::glBindVertexArray(0);
// }