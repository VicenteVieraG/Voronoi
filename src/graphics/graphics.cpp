#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <utility>
#include <fstream>
#include <sstream>
#include <cstddef>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include <graphics.hpp>

namespace Graphics{
    Global::Global(){
        this->createShader();
        this->initBuffers();
    }
    Global::~Global(){
        gl::glDeleteBuffers(1, &this->vbo);
        gl::glDeleteVertexArrays(1, &this->vao);
        gl::glDeleteProgram(this->shaderProgram);
    }

    void Global::initBuffers(){
        /* ~~Initialize VAO and VBO~~ */
        gl::glGenVertexArrays(1, &this->vao);
        gl::glBindVertexArray(this->vao);

        gl::glGenBuffers(1, &this->vbo);
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->vbo);

        gl::glEnableVertexAttribArray(0);
        gl::glVertexAttribPointer(0, 2, gl::GL_FLOAT, gl::GL_FALSE, 0, nullptr);

        // Security unbind
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
        gl::glBindVertexArray(0);
    }

    void Global::updateBufferData(){
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, this->vbo);
        gl::glBufferData(gl::GL_ARRAY_BUFFER,
            this->sites.size() * sizeof(Site),
            this->sites.data(),
            gl::GL_DYNAMIC_DRAW
        );
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    }

    void Global::createShader(){
        this->shaderProgram = gl::glCreateProgram();
        const std::array<const std::pair<std::string, gl::GLenum>, 2> shaderPaths =
        {{
            {"./shaders/vertexShader.glsl", gl::GL_VERTEX_SHADER},
            {"./shaders/fragmentShader.glsl", gl::GL_FRAGMENT_SHADER}
        }};
        std::vector<gl::GLuint> compiledShaders;

        for(const auto& [path, shaderType] : shaderPaths){
            const std::string shaderSrc = this->loadShaderFile(path);
            const gl::GLuint shader = this->compileShader(shaderType, shaderSrc);

            gl::glAttachShader(this->shaderProgram, shader);
            compiledShaders.push_back(shader);
        }

        gl::glLinkProgram(this->shaderProgram);

        gl::GLint success;
        gl::glGetProgramiv(this->shaderProgram, gl::GL_LINK_STATUS, &success);
        if(!success){
            char infoLog[512];
            gl::glGetProgramInfoLog(this->shaderProgram, 512, nullptr, infoLog);
            std::cerr<<"--[ERROR]: Program Linking Error: "<<infoLog<<std::endl;
        }

        for(const auto& shader : compiledShaders) gl::glDeleteShader(shader);
    }

    gl::GLuint Global::compileShader(const gl::GLenum type, const std::string& source){
        gl::GLuint shader = gl::glCreateShader(type);
        const gl::GLchar* src = source.c_str();
        gl::glShaderSource(shader, 1, &src, nullptr);
        gl::glCompileShader(shader);

        gl::GLint success;
        gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &success);
        if(!success){
            char log[512];
            gl::glGetShaderInfoLog(shader, 512, nullptr, log);
            std::cerr<<"--[ERROR]: Shader Compile Error: "<<log<<std::endl;
        }

        return shader;
    }

    const std::string Global::loadShaderFile(const std::string& filePath){
        std::ifstream shaderFile(filePath);
        if(!shaderFile) {
            std::cerr << "--[ERROR]: Shader file not found: " << filePath << std::endl;
            return "";
        }

        std::stringstream fileBuffer;
        fileBuffer<<shaderFile.rdbuf();

        const std::string shaderContent = fileBuffer.str();
        return shaderContent;
    }

    void Global::addSite(const Site& site){
        this->sites.push_back(site);
        this->updateBufferData();
        return;
    }
    void Global::clearSites(){
        this->sites.clear();
        return;
    }
    const std::size_t Global::countSites() const {
        return this->sites.size();
    }

    void Global::draw() const {
        gl::glUseProgram(this->shaderProgram);
        gl::glBindVertexArray(this->vao);
        gl::glDrawArrays(gl::GL_POINTS, 0, static_cast<gl::GLsizei>(this->countSites()));
        gl::glBindVertexArray(0);
        gl::glUseProgram(0);
        return;
    }
};