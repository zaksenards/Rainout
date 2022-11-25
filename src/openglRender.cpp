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

bool rainoutCore::init(void* proc)
{
    if(!gladLoadGLLoader((GLADloadproc)proc))
        return false;

    char* vshader = Rainout::Utils::loadFileToBuffer("res/vertex.glsl");
    char* fshader = Rainout::Utils::loadFileToBuffer("res/fragment.glsl");

    uint32_t vertex = compileShader(VERTEX_SHADER_TYPE, vshader);
    uint32_t fragment = compileShader(FRAGMENT_SHADER_TYPE, fshader);
    if(!glIsShader(vertex) || !glIsShader(fragment))
        //TODO: Log an error here
        return false;

    _shared.vertex = vertex;
    _shared.fragment = fragment;

    return true;
}

void rainoutCore::drawColor(float R, float G, float B, float A)
{
    glClearColor(R,G,B,A);
}

rainoutCore::Primitive rainoutCore::createPrimitive(uint8_t primitiveType)
{
    uint32_t vbo, vao, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //TODO: Remove this shit
    primitiveType = 0;

    float vertices[12] = 
    {
        -0.05f, -0.05f, 0.0f,
         0.05f, -0.05f, 0.0f,
         0.05f,  0.05f, 0.0f,
        -0.05f,  0.05f, 0.0f
    };

    uint32_t indexes[6] = 
    {
        0, 1, 2,
        0, 2, 3
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);


    Primitive primitive;
    primitive.vao = vao;
    primitive.vbo = vbo;
    primitive.ebo = ebo;
    primitive.id = compileProgram(_shared.vertex, _shared.fragment);

    return primitive;
}

void rainoutCore::deletePrimitive(Primitive primitive)
{
    glDeleteBuffers(1, &primitive.vao);
    glDeleteBuffers(1, &primitive.ebo);
    glDeleteBuffers(1, &primitive.vbo);
    glDeleteProgram(primitive.id);
}

void rainoutCore::render(Primitive primitive)
{
    glUseProgram(primitive.id);
    glBindVertexArray(primitive.vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
}

void rainoutCore::render(Primitive primitive, rainout::Material material, rainout::Mat4f matrix)
{
    rainout::Vec3f color = material.color;
    
    uint32_t colorIndex = glGetUniformLocation(primitive.id,"vColor");
    uint32_t transformIndex = glGetUniformLocation(primitive.id, "transform");

    glUseProgram(primitive.id);
    glBindVertexArray(primitive.vao);
    glUniform4f(colorIndex, color.x, color.y, color.z, 1.0f);
    glUniformMatrix4fv(transformIndex, 1, GL_FALSE, (const float*)matrix.e);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

uint32_t rainoutCore::compileShader(uint8_t shaderType, char* source)
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

uint32_t rainoutCore::compileProgram(uint32_t vertex, uint32_t fragment)
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

void rainoutCore::update()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void rainoutCore::stop()
{
    glDeleteShader(_shared.vertex);
    glDeleteShader(_shared.fragment);
}
