#pragma once

#include <vector>
#include <string>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

namespace Graphics{
    struct Vertex{
        float x;
        float y;
    };

    class Global{
        private:
            gl::GLuint vao;
            gl::GLuint vbo;
            gl::GLuint shaderProgram;
            std::vector<Vertex> vertices;

            void initBuffers();
            void updateBufferData();

            void createShader();
            gl::GLuint compileShader(const gl::GLenum type, const std::string& source);
            const std::string loadShaderFile(const std::string& filePath);
        public:
            Global();
            ~Global();
    };
};