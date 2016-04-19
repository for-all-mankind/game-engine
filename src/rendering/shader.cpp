#include "shader.h"
#include "../util/file.h"

#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Ice
{
  Shader::Shader( std::string vertex, std::string fragment )
  {
    _program = glCreateProgram();

    _vert = Load( GL_VERTEX_SHADER  , vertex   );
    _frag = Load( GL_FRAGMENT_SHADER, fragment );

    Compile();
  }

  Shader::~Shader()
  {
    glDetachShader( _program, _vert );
    glDetachShader( _program, _frag );

    glDeleteProgram( _program );
  }

  void Shader::RegisterUniform( const GLchar* name )
  {
    GLint uniform = glGetUniformLocation( _program, name );
    _uniform_locations.emplace( name, uniform );
  }

  void Shader::UpdateUniform( const GLchar* name, i32 value )
  {
    glUniform1i( GetUniformLocation( name ), value );
  }

  void Shader::UpdateUniform( const GLchar* name, f32 value )
  {
    glUniform1f( GetUniformLocation( name ), value );
  }

  void Shader::UpdateUniform( const GLchar* name, i32* values, i32 count )
  {
    glUniform1iv( GetUniformLocation( name ), count, values );
  }

  void Shader::UpdateUniform( const GLchar* name, f32* values, i32 count )
  {
    glUniform1fv( GetUniformLocation( name ), count, values );
  }

  void Shader::UpdateUniform( const GLchar* name, const glm::vec2& vec )
  {
    glUniform2f( GetUniformLocation( name ), vec.x, vec.y );
  }

  void Shader::UpdateUniform( const GLchar* name, const glm::vec3& vec )
  {
    glUniform3f( GetUniformLocation( name ), vec.x, vec.y, vec.z );
  }

  void Shader::UpdateUniform( const GLchar* name, const glm::vec4& vec )
  {
    glUniform4f( GetUniformLocation( name ), vec.x, vec.y, vec.z, vec.w );
  }

  void Shader::UpdateUniform( const GLchar* name, const glm::mat4& mat )
  {
    glUniformMatrix4fv( GetUniformLocation( name ), 1, GL_FALSE, glm::value_ptr( mat ) );
  }

  GLint Shader::GetUniformLocation( const GLchar* name )
  {
    auto location = _uniform_locations.find( name );

    if ( location == _uniform_locations.end() )
    {
      GLint uniform = glGetUniformLocation( _program, name );
      _uniform_locations.emplace( name, uniform );
      return uniform;
    }
    else
      return location->second;
  }

  void Shader::Bind() const
  {
    glUseProgram( _program );
  }

  void Shader::UnBind() const
  {
    glUseProgram( 0 );
  }

  GLuint Shader::Load( GLuint type, std::string& name )
  {
    std::cout << "Loading shader: " << name << std::endl;

    std::string str;
    read_file( name, &str );

    GLuint      shader = glCreateShader( type );
    const char* source = str.c_str();

    glShaderSource ( shader, 1, &source, NULL );
    glCompileShader( shader );

    GLint result;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
    if ( result == GL_FALSE )
    {
      GLint length;
      glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length );

      char error[ length ];
      glGetShaderInfoLog( shader, length, &length, &error[0] );

      std::cout << &error[0] << std::endl;
      glDeleteShader( shader );

      return 0;
    }

    return shader;
  }

  void Shader::Compile()
  {
    std::cout << "Building shader program..." << std::endl;

    glAttachShader( _program, _vert );
    glAttachShader( _program, _frag );

    glLinkProgram    ( _program );
    glValidateProgram( _program );

    GLint result;
    glGetProgramiv( _program, GL_VALIDATE_STATUS, &result );
    if ( result == GL_FALSE )
    {
      GLint length;
      glGetProgramiv( _program, GL_INFO_LOG_LENGTH, &length );

      std::vector<char> error( length );
      glGetShaderInfoLog( _program, length, &length, &error[0] );

      std::cout << &error[0] << std::endl;
      glDeleteProgram( _program );
    }

    glDeleteShader( _vert );
    glDeleteShader( _frag );

    std::cout << "Shader program successfully built" << std::endl;
  }
}