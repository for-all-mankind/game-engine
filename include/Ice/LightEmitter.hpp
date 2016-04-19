#ifndef ICE_LIGHT_EMITTER_H
#define ICE_LIGHT_EMITTER_H

#include <Ice/Common/Types.hpp>
#include <Ice/Component.hpp>
#include <Ice/Maths.hpp>

namespace Ice
{
  class LightEmitter : public Component
  {
  public:
    LightEmitter( Node* parent );

    void Update( f32 delta ) override;
    void Render() const override;
  };
}

#endif // ICE_LIGHT_EMITTER_H