#include <sstream>
#include <iomanip>

#include "raylib.h"
#include "world_grid.h"
#include "raymath.h"
#include "glob.h"

namespace world_grid {

  WorldGrid::WorldGrid(int gridW, int gridH, int gridCntVert, int gridCntHorz):
    gw_{gridW}, gh_{gridH}, gcVert_{gridCntVert}, gcHorz_{gridCntHorz}
  {
    // Resize the grid_ to the given sizes
    grid_.resize(gcVert_);
    for(auto& row : grid_){
      row.resize(gcHorz_);
    }
  }

  int& WorldGrid::at(const Vector2& pos){
    return grid_.at(pos.y).at(pos.x);
  };
  
  int& WorldGrid::at(int y, int x){
    return grid_.at(y).at(x);
  };

  std::vector<int>& WorldGrid::row(int row_idx) {
    return grid_.at(row_idx);
  };

  std::string WorldGrid::str() const{
    std::stringstream ss;
    for(const auto& row : grid_){
      for(const auto& elem : row){
	ss << std::left << std::setw(3) << std::to_string(elem);
      }
      ss << "\n";
    }

    std::string out {ss.str()};
    out.pop_back();
    return out;
  }
  
  void WorldGrid::update(player::Player& snake, Vector2& food){
    // Collision
    Vector2 snakePos = snake.getPos();
      
    if(at(snakePos) == glob::ObjCode::FOOD){
      snake.grow();
      food.x = rand() % glob::gridCntHorz;
      food.y = rand() % glob::gridCntVert;
    }

    if(at(snake.getPos()) == glob::ObjCode::SNAKE_TAIL){
       // game over
      TraceLog(LOG_INFO, "Collision with tail at: (%d, %d)",
	       static_cast<int>(snakePos.y), static_cast<int>(snakePos.x));
    }

    // Update
    clear();
    at(snakePos) = glob::ObjCode::SNAKE_HEAD;

    for(auto& tail : snake.getTail()){
      at(tail) = glob::ObjCode::SNAKE_TAIL;
    }
    
    at(food) = glob::ObjCode::FOOD;
  }

  void WorldGrid::clear(){
    for(auto& r : grid_){
      for(auto& c : r){
	c = glob::ObjCode::EMPTY;
      }
    }
  }
  
} // namespace world_grid
