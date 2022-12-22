#include <rainout/utils.h>
#include <openglRender.h>
#include <glad/glad.h>
#include <cstdlib>
#include <cstdio>

struct
{
    uint32_t vertex;
    uint32_t fragment;
}_shared;

using rainout::Texture;

namespace rainoutCore
{
    bool glRender::init(void* proc)
    {
        if(!gladLoadGLLoader((GLADloadproc)proc))
            return false;

        char* vshader = rainout::Utils::loadFileToBuffer("res/vertex.glsl");
        char* fshader = rainout::Utils::loadFileToBuffer("res/fragment.glsl");

        uint32_t vertex = compileShader(VERTEX_SHADER_TYPE, vshader);
        uint32_t fragment = compileShader(FRAGMENT_SHADER_TYPE, fshader);
        if(!glIsShader(vertex) || !glIsShader(fragment))
            //TODO: Log an error here
            return false;

        _shared.vertex = vertex;
        _shared.fragment = fragment;

        return true;
    }

    void glRender::drawColor(float R, float G, float B, float A)
    {
        glClearColor(R,G,B,A);
    }

    glRender::Primitive glRender::createPrimitive(uint8_t primitiveType)
    {
        uint32_t vbo, vao, ebo;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //TODO: Remove this shit
        primitiveType = 0;

        float vertices[20] = 
        {
            -0.06f, -0.06f, 0.0f, 0.0f, 0.0f,
            0.06f, -0.06f, 0.0f, 1.0f, 0.0f,
            0.06f,  0.06f, 0.0f, 1.0f, 1.0f,
            -0.06f,  0.06f, 0.0f, 0.0f, 1.0f,
        };

        uint32_t indexes[6] = 
        {
            0, 1, 2,
            0, 2, 3
        };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture cordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

        Primitive primitive;
        primitive.vao = vao;
        primitive.vbo = vbo;
        primitive.ebo = ebo;
        primitive.id = compileProgram(_shared.vertex, _shared.fragment);
        primitive.text = 0;

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return primitive;
    }

    void glRender::setPrimitiveTexture(Primitive* primitive, Texture* texture)
    {
        uint32_t text;
        glGenTextures(1, &text);
        glBindTexture(GL_TEXTURE_2D, text);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint32_t* data = (uint32_t*)texture->data;
        int width = texture->width;
        int height = texture->height;

        GLenum textureFormat = GL_RGBA;
        GLenum textureType = GL_UNSIGNED_BYTE;

        switch(texture->bitCount)
        {
            case 16:
                {
                    textureFormat = GL_RGB;
                    textureType = GL_UNSIGNED_SHORT_5_6_5;
                    break;
                }
            case 24:
                {
                    textureFormat = GL_RGB;
                    textureType = GL_UNSIGNED_BYTE;
                    break;
                }
        }

        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, textureFormat, textureType, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }


        primitive->text = text; 
    }

    void glRender::deletePrimitive(Primitive primitive)
    {
        glDeleteBuffers(1, &primitive.vao);
        glDeleteBuffers(1, &primitive.ebo);
        glDeleteBuffers(1, &primitive.vbo);
        glDeleteProgram(primitive.id);
    }

    void glRender::render(Primitive primitive)
    {
        glUseProgram(primitive.id);
        glBindVertexArray(primitive.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void glRender::render(Primitive primitive, rainout::Material material, rainout::Mat4f matrix)
    {
        rainout::Vec3f color = material.color;

        uint32_t colorIndex = glGetUniformLocation(primitive.id,"vColor");
        uint32_t transformIndex = glGetUniformLocation(primitive.id, "transform");
        uint32_t renderTexture = glGetUniformLocation(primitive.id, "useTexture");

        glUseProgram(primitive.id);
        glBindVertexArray(primitive.vao);
        glUniform4f(colorIndex, color.x, color.y, color.z, 1.0f);
        glUniformMatrix4fv(transformIndex, 1, GL_FALSE, (const float*)matrix.e);
        glUniform1i(renderTexture, primitive.text != 0);
        glBindTexture(GL_TEXTURE_2D, primitive.text);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    uint32_t glRender::compileShader(uint8_t shaderType, char* source)
    {
        GLenum type;
        switch(shaderType)
        {
            case VERTEX_SHADER_TYPE:
                type = GL_VERTEX_SHADER;
                break;
            case FRAGMENT_SHADER_TYPE:
                type = GL_FRAGMENT_SHADER;
                break;
            default:
                return 0;
        }

        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);

        char infoLog[512];
        int success;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            fprintf(stderr, "Can't compile shader of type %u: %s\n",shaderType, infoLog);
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    uint32_t glRender::compileProgram(uint32_t vertex, uint32_t fragment)
    {
        uint32_t program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        char infoLog[512];
        int success;

        glGetProgramiv(program,GL_LINK_STATUS,&success);
        if(!success)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            fprintf(stderr, "Can't compile program: %s\n",infoLog);
            return 0;
        }

        return program;
    }

    void glRender::update()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void glRender::stop()
    {
        glDeleteShader(_shared.vertex);
        glDeleteShader(_shared.fragment);
    }
}
