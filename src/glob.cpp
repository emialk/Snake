#include "glob.h"
#include "raymath.h"

namespace glob {
  Vector2 dirToVec(Direction dir){
    Vector2 vec = Vector2Zero();

    if(dir == Direction::UP)
      vec.y = -1;

    if(dir == Direction::DOWN)
      vec.y = 1;

    if(dir == Direction::LEFT)
      vec.x = -1;

    if(dir == Direction::RIGHT)
      vec.x = 1;
    
    return vec;
  }
  
} // namespace glob
