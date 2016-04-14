#ifndef ICE_SHADER_H
#define ICE_SHADER_H

#include "../util/types.h"
#include "../maths/maths.h"

#include <GL/glew.h>
#include <string>
#include <unordered_map>

namespace Ice
{
  class Shader
  {
  public:
    Shader( std::string path );
    ~Shader();

    void SetUniform( const GLchar* name, i32  value );
    void SetUniform( const GLchar* name, f32  value );
    void SetUniform( const GLchar* name, i32* values, i32 count );
    void SetUniform( const GLchar* name, f32* values, i32 count );
    void SetUniform( const GLchar* name, const  Vec2& vec  );
    void SetUniform( const GLchar* name, const  Vec3& vec  );
    void SetUniform( const GLchar* name, const  Vec4& vec  );
    void SetUniform( const GLchar* name, const  Mat4& mat  );

    void Bind  () const;
    void Unbind() const;

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