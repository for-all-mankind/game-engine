#include <Ice/Buffers.hpp>

namespace Ice
{
  GLvao::GLvao()
  {
    glGenVertexArrays( 1, &_handle );
  }

  GLvao::~GLvao()
  {
    glDeleteVertexArrays( 1, &_handle );
  }

  void GLvao::Bind()
  {
    glBindVertexArray( _handle );
  }

  void GLvao::UnBind()
  {
    glBindVertexArray( 0 );
  }

  VertexBuffer&  GLvao::VBO() { return _vbo; }
  ElementBuffer& GLvao::EBO() { return _ebo; }

  void GLvao::SetVAP( GLuint index, GLint size, GLenum type, GLboolean normalised, GLsizei stride, const GLvoid* pointer )
  {
    glVertexAttribPointer( index, size, type, normalised, stride, pointer );
    glEnableVertexAttribArray( index );
  }
}