#include "oglShaderFactory.h"
#include "graphics/IShaderProgram.h"
#include "core/debug/Log.h"

#include <GL/glew.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

using namespace radium;


GLuint oglShaderFactory::createShaderProgram(ShaderProgramDescription& spd)
{
    assert(spd.filename);

    // For any shader program, we MUST at least have a pixel and vertex shader
    if (!spd.vertexShader || !spd.pixelShader)
    {
        RAD_ENGINE_ERROR("[GL] Shader descriptor for {} has no Vertex/Pixel shader listed", spd.filename);
        return -1;
    }

    ShaderID id = -1;
    
    U32 filesize = 0;
    char* buffer = nullptr;

    buffer = _int_readShader(spd.filename, filesize);

    if (!buffer)
        return -1;

    RAD_ENGINE_INFO("[GL] Compile shader at {}; {} bytes", spd.filename, filesize);

    auto vshaderId = createShader(*spd.vertexShader, buffer, filesize);
    if (vshaderId == -1)
    {
        delete[] buffer;
        return -1;
    }
    auto pshaderId = createShader(*spd.pixelShader, buffer, filesize);

    if (pshaderId == -1)
    {
        delete[] buffer;
        return -1;
    }

    GLuint shaders[] = { vshaderId, pshaderId };
    id = _int_linkShaderProgram(shaders, 2);

    delete[] buffer;

    if (id != -1)
    {
        RAD_ENGINE_INFO("[GL] Shader {} successfully compild and linked. ID: 0x{:X}", spd.filename, (unsigned int)id);
    }

    return id;
}

char* oglShaderFactory::_int_readShader(const char* filename, U32& size)
{
    // TODO: Move most of this into the FS abstraction layer
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        RAD_ENGINE_CRITICAL("[GL] Failed to open shader source: {}", filename);
        return nullptr;
    }

    // Get file size
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    char* buffer = new char[size + 1];
    fread(buffer, 1, size, fp);

    // add null byte at the end
    buffer[size + 1] = 0;

    fclose(fp);

    return buffer;
}

GLuint oglShaderFactory::_int_linkShaderProgram(GLuint shaders[], U8 numShaders)
{
    GLuint shaderProgramID = glCreateProgram();

    for (U8 i = 0; i < numShaders; i++)
        glAttachShader(shaderProgramID, shaders[i]);

    glLinkProgram(shaderProgramID);

    GLint status;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);

    if(status != GL_TRUE)
    {
        RAD_ENGINE_CRITICAL("[GL] Failed to link shader program!");
        return -1;
    }

    glValidateProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &status);

    if (status != GL_TRUE)
    {
        RAD_ENGINE_CRITICAL("[GL] Failed to validate shader program!");
        return -1;
    }

    // cleanup
    for (U8 i = 0; i < numShaders; i++)
        glDeleteShader(shaders[i]);

    return shaderProgramID;
}

GLuint oglShaderFactory::createShader(ShaderDescription& sd, const char* source, U32 size)
{
    // TODO: figure out if this neds to be made thread safe
    static char tempShaderBuffer[1024];
    static GLenum spTypeToGlType[] = {GL_INVALID_VALUE, GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

    // make sure it is in the array and not and invalid value
    assert(sd.type >= 1 && sd.type < 3);

    assert(source && "oglShaderFactory: source is null");

    int sectionSize = _int_extractShader(sd.sectionName, source, size, tempShaderBuffer, sizeof(tempShaderBuffer));

    if (sectionSize == 0)
    {
        RAD_ENGINE_ERROR("[GL] No match section found for \"{}\"", sd.sectionName);
        return -1;
    }


    GLuint shaderId = _int_createShader(spTypeToGlType[(int)sd.type], tempShaderBuffer, sectionSize + 1);
    
    memset(tempShaderBuffer, 0, sectionSize + 1);

    return shaderId;
}

GLuint oglShaderFactory::_int_createShader(GLenum type, const char* source, U32 size)
{
    assert(source);

    GLuint sid = glCreateShader(type);

    glShaderSource(sid, 1, &source, reinterpret_cast<const GLint*>(&size));

    glCompileShader(sid);

    int compileStatus = 0;
    glGetShaderiv(sid, GL_COMPILE_STATUS, &compileStatus);

#ifdef RAD_DEBUG
    char errorBuffer[256];

    if (compileStatus == GL_FALSE)
    {
        int len = -1;
        glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &len);
        glGetShaderInfoLog(sid, sizeof(errorBuffer), &len, errorBuffer);

        // Since this is only compiled in debug builds I am going to ignore
        // the performance/memory drawbacks of this...

        const char* shaderTypeStr = nullptr;

        switch (type){
            case GL_VERTEX_SHADER:
                shaderTypeStr = "VERTEX"; break;
            case GL_FRAGMENT_SHADER:
                shaderTypeStr = "FRAGMENT"; break;
            default:
                shaderTypeStr = "UNKNOWN"; break;
        }

        RAD_ENGINE_ERROR("[GL] Failed to compile {} shader: {}", shaderTypeStr, errorBuffer);
        glDeleteShader(sid);
    }

#endif // RAD_DEBUG

    return (compileStatus == GL_TRUE ? sid : -1);
}


int oglShaderFactory::_int_extractShader(const char* sectionName, const char* source, U32 sourceSize, char* out, U32 outSize)
{
    int sectionSize = 0;
    bool isReadingShaderSection = false;

    const char* srcPtr = source;

    size_t sectionNameLen = strlen(sectionName);
    /*
        Iterate over the source. If we see `#section <sectionName>`, then start adding to the buffer
        until we see #endsection

        If `sectionName` is not found, the buffer will not be filled, and a sectionSize of '0' will be returned,
        evoking an error in the calling function
    */

    while (*srcPtr && srcPtr < (source + sourceSize))
    {
        char cur = *srcPtr;

        if (cur == '#')
        {
            if (strncmp(srcPtr, "#section ", 9) == 0)
            {
                // `9` for len("#section ")
                if (strncmp(srcPtr + 9, sectionName, sectionNameLen - 1) == 0)
                {
                    isReadingShaderSection = true;

                    srcPtr += 9 + (sectionNameLen);

                    continue;
                }
            }
            // `11` for len("#endsection")
            else if (strncmp(srcPtr, "#endsection", 11) == 0 && isReadingShaderSection)
            {
                break;
            }

        }

        if (isReadingShaderSection)
        {

            out[sectionSize++] = cur;
        }

        srcPtr++;

    }

    out[sectionSize + 1] = 0;

    return sectionSize;
}

