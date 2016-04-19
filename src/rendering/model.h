#ifndef ICE_MODEL_H
#define ICE_MODEL_H

#include "vertex.h"

#include <string>

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
