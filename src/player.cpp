#include <vector>

#include "raylib.h"
#include "player.h"
#include "raymath.h"
#include "glob.h"

namespace player {
  Player::Player(Vector2 pos):
    pos_{pos}, dir_{}, lastMoveDir_{}, tail_{}, grow_{false}
  {
    TraceLog(LOG_INFO, "New player created at position: (%f, %f)\n", pos.y, pos.x);
  }

  void Player::move(){
    // Update the tail
    if(!tail_.empty()){
      tail_.insert(tail_.begin(), pos_);
    }

    // Remove last tail element
    if(!tail_.empty()){
      tail_.pop_back();
    }
    
    if(grow_) {
      grow_ = false;
      tail_.insert(tail_.begin(), pos_);
    }

    // Move head
    pos_ = Vector2Add(pos_, glob::dirToVec(dir_));
    lastMoveDir_ = dir_;

    // Wrap if we hit border

    if(pos_.y < 0)
      pos_.y = glob::gridCntVert - 1;
    else if(pos_.y >= glob::gridCntVert)
      pos_.y = 0;

    if(pos_.x < 0)
      pos_.x = glob::gridCntHorz - 1;
    else if(pos_.x >= glob::gridCntHorz)
      pos_.x = 0;
    
  }

  void Player::keyboardControl(){
    if(IsKeyPressed(KEY_UP) or IsKeyPressed(KEY_W)){
      if(!(lastMoveDir_ == glob::Direction::DOWN))
	dir_ = glob::Direction::UP;
    }
    else if(IsKeyPressed(KEY_DOWN) or IsKeyPressed(KEY_S)){
      if(!(lastMoveDir_ == glob::Direction::UP))
	dir_ = glob::Direction::DOWN;
    }
    else if(IsKeyPressed(KEY_LEFT) or IsKeyPressed(KEY_A)){
      if(!(lastMoveDir_ == glob::Direction::RIGHT))
      dir_ = glob::Direction::LEFT;
    }
    else if(IsKeyPressed(KEY_RIGHT) or IsKeyPressed(KEY_D)){
      if(!(lastMoveDir_ == glob::Direction::LEFT))
	dir_ = glob::Direction::RIGHT;
    }
  }
} // namespace player
