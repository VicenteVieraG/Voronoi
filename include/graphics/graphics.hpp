#pragma once

#include <vector>
#include <string>
#include <cstddef>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

namespace Graphics{
    struct Site{
        float x;
        float y;
    };
    using Point = Site;
    using Vertex = Site;

    class Global{
        private:
            gl::GLuint vao;
            gl::GLuint vbo;
            gl::GLuint shaderProgram;
            std::vector<Site> sites;

            void initBuffers();
            void updateBufferData();

            void createShader();
            gl::GLuint compileShader(const gl::GLenum type, const std::string& source);
            const std::string loadShaderFile(const std::string& filePath);
        public:
            Global();
            ~Global();

            void addSite(const Site& site);
            void clearSites();
            const std::size_t countSites() const;

            void draw() const;
    };
};