#include"Shader.h"

Shader::Shader(const std::string& filepath)
    : m_ProgramID(0)
{
    ShaderSources sources = ParseShader(filepath);
    m_ProgramID = CreateProgram(sources.vertexShader, sources.fragmentShader);

    GLCall(glUseProgram(m_ProgramID));
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_ProgramID));
}

void Shader::UseProgram() {
    GLCall(glUseProgram(m_ProgramID));
}

void Shader::UnuseProgram() {
    GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name) {
    GLCall(int uniLocation = glGetUniformLocation(m_ProgramID, name.c_str()));
    if (uniLocation == -1)
        std::cout << "No active uniform with name " << name << std::endl;

    return uniLocation;
}

void Shader::SetUniformMat4f(const std::string& uniformName, glm::mat4 matrix) {
    glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]);
}

ShaderSources Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    if (stream.fail()) {
        std::cout << "COULDN'T OPEN THE FILE " << filepath << std::endl;
        ASSERT(false);
    }

    enum class SHADERTYPE { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    std::stringstream sources[2];
    SHADERTYPE type = SHADERTYPE::NONE;

    std::string line;
    while (getline(stream, line)) {

        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = SHADERTYPE::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = SHADERTYPE::FRAGMENT;
            }
        }
        else {
            sources[(int)type] << line << '\n';
        }
    }
    return { sources[0].str(), sources[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_TRUE) return id;

    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)malloc(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile shader!" << std::endl;
    std::cout << message << std::endl;
    free(message);
    return 0;
}

unsigned int Shader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    unsigned int program = glCreateProgram();
    unsigned int vertexSh = CompileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentSh = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

    glAttachShader(program, vertexSh);
    glAttachShader(program, fragmentSh);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexSh);
    glDeleteShader(fragmentSh);

    return program;
}