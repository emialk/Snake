#pragma once
#include <vector>
#include "glob.h"
#include "player.h"

namespace world_grid {
  class WorldGrid {
  public:
    WorldGrid(int gridW, int gridH, int gridCntVert, int gridCntHorz);
    ~WorldGrid() = default;

    // grid access
    int& at(const Vector2& pos);
    int& at(int y, int x);
    std::vector<int>& row(int row_idx);

    std::string str() const;
    void update(player::Player& snake, Vector2& foodList);
    void clear();

  private:
    int gw_; // Grid width
    int gh_; // Grid height 
    int gcVert_; // Grid count vertical
    int gcHorz_; // Grid count horizontal
    std::vector<std::vector<int>> grid_; // Grid data indexed by (horz, vert)
  };
} // namespace world_grid
