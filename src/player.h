#pragma once
#include "glob.h"
#include "raymath.h"
#include <vector>

namespace player {

class Player {
public:
  Player() = default;
  Player(Vector2 pos);
  ~Player() = default;

  void grow() { grow_ = true; }
  void move();
  void keyboardControl();

  void setDir(glob::Direction dir) { dir_ = dir; }
  glob::Direction getDir() const { return dir_; }
  Vector2 getPos() const { return pos_; }
  std::vector<Vector2> getTail() const { return tail_; }
  void clearTail() {tail_.clear();}

private:
  Vector2 pos_;
  glob::Direction dir_;
  glob::Direction lastMoveDir_;
  std::vector<Vector2> tail_;
  bool grow_;
};
} // namespace player
