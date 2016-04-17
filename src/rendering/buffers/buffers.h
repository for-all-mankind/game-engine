#ifndef ICE_BUFFERS_H
#define ICE_BUFFERS_H

#include <GL/glew.h>

/*
  A set of simple RAII classes to wrap the
  creation, deletion and usage of OpenGL
  buffer objects.
*/

namespace Ice
{
  template<GLenum TARGET>
  class Buffer
  {
  public:
    Buffer()
    {
      glGenBuffers( 1, &_handle );
    }

    ~Buffer()
    {
      glDeleteBuffers( 1, &_handle );
    }

    void Bind()
    {
      glBindBuffer( TARGET, _handle );
    }

    void UnBind()
    {
      glBindBuffer( TARGET, 0 );
    }

    void BufferData( GLsizeiptr size, const GLvoid* data, GLenum usage )
    {
      glBufferData( TARGET, size, data, usage );
    }

  private:
    GLuint _handle;
  };

  /////////////////////////////////

  typedef Buffer<GL_ARRAY_BUFFER>         VertexBuffer;
  typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> ElementBuffer;

  /////////////////////////////////

  class GLvao
  {
  public:
    GLvao();
    ~GLvao();

    void Bind();
    void UnBind();

    VertexBuffer&  VBO();
    ElementBuffer& EBO();

    // VAP ( VertexAttribPointer )
    void SetVAP( GLuint index, GLint size, GLenum type, GLboolean normalised, GLsizei stride, const GLvoid* pointer );

  private:
    GLuint _handle;

    VertexBuffer  _vbo;
    ElementBuffer _ebo;
  };
}

#endif // ICE_BUFFERS_H