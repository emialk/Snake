#pragma once
#include <string>
#include "raymath.h"

namespace glob {
  constexpr int gridWidth {32};
  constexpr int gridHeight {32};
  constexpr int gridCntHorz {25};
  constexpr int gridCntVert {15};
  constexpr int winWidth {gridWidth * gridCntHorz};
  constexpr int winHeight {gridHeight * gridCntVert};
  constexpr int framesPerPhysicsTick {3};
  const std::string winTitle {"Snake"};

  enum ObjCode {
    EMPTY = 0,
    SNAKE_HEAD,
    SNAKE_TAIL,
    FOOD
  };

  enum Direction {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  Vector2 dirToVec(Direction dir);  
} // namespace glob
