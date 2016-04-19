#ifndef ICE_MODEL_H
#define ICE_MODEL_H

#include <Ice/Common/Types.hpp>
#include <Ice/Vertex.hpp>

namespace Ice
{
  class Model
  {
  public:
    Model();
    Model( const Model&  model );
    Model(       Model&& model );

    ~Model();

    Model& operator=( const Model&  model );
    Model& operator=(       Model&& model );

    void Load( const std::string& filename );

  private:
    Vertex* vertex_data;
  };
}

#endif // ICE_MODEL_H
