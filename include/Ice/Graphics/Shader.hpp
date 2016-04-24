#ifndef ICE_SHADER_H
#define ICE_SHADER_H

#include <Ice/Common/OpenGL.hpp>
#include <Ice/Common/Types.hpp>
#include <Ice/Common/NonCopy.hpp>
#include <Ice/Maths/Maths.hpp>

#include <string>
#include <unordered_map>

namespace Ice
{
  class Shader : public Common::NonCopyable
  {
  public:
    Shader( std::string vertex, std::string fragment );
    ~Shader();

    void RegisterUniform( const GLchar* name );

    void UpdateUniform( const GLchar* name, i32  value );
    void UpdateUniform( const GLchar* name, f32  value );
    void UpdateUniform( const GLchar* name, i32* values, i32 count );
    void UpdateUniform( const GLchar* name, f32* values, i32 count );
    void UpdateUniform( const GLchar* name, const Vec2& vec );
    void UpdateUniform( const GLchar* name, const Vec3& vec );
    void UpdateUniform( const GLchar* name, const Vec4& vec );
    void UpdateUniform( const GLchar* name, const Mat4& mat );

    void Bind() const;
    void UnBind() const;
  private:
    GLint  GetUniformLocation( const GLchar* name );
    GLuint Load( GLuint type, std::string& name );
    void   Compile();

  private:
    GLuint _program;
    GLuint _vert;
    GLuint _frag;

    std::unordered_map<const GLchar*, GLint> _uniform_locations;
  };
}

#endif // ICE_SHADER_H