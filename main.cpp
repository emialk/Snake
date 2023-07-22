#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <sstream>

#include "raylib.h"
#include "raymath.h"
#include "world_grid.h"
#include "glob.h"

void initWindow(int w, int h, std::string title){
  // Init raylib window
  InitWindow(w, h, title.data());
  SetTargetFPS(60);
}

int main(void){
  initWindow(glob::winWidth, glob::winHeight, glob::winTitle);
  world_grid::WorldGrid world {glob::gridWidth, glob::gridHeight, glob::gridCntVert, glob::gridCntHorz};

  player::Player snake{{.x=floorf(glob::gridCntHorz/2.0), .y=floorf(glob::gridCntVert/2.0)}};
  snake.setDir(glob::Direction::RIGHT);

  Vector2 food = {.x=5, .y=10};
  
  int frameCnt {};
  while (!WindowShouldClose()){
    TraceLog(LOG_INFO, "Starting to work with frame: %d", frameCnt++);    

    // Poll keyboard
    snake.keyboardControl();

    // Update physics
    if(frameCnt % glob::framesPerPhysicsTick == 0){
      snake.move();
      world.update(snake, food);
      //TraceLog(LOG_INFO, "World state\n%s", world.str().data());
    }
    
    ///// Begin Drawing /////
    BeginDrawing();
    ClearBackground(BLACK);

    // Create a checkerboard ground texture
    Image img = GenImageChecked(glob::winWidth, glob::winHeight,
				glob::gridWidth, glob::gridHeight, DARKBROWN, DARKGRAY);

    // Loop through every grid cell and draw based on content
    for(int row = 0; row < glob::gridCntVert; ++row){
      for(int col = 0; col < glob::gridCntHorz; ++col){
	int& cell = world.at(row, col);

	if(cell == glob::ObjCode::SNAKE_HEAD){
	  ImageDrawRectangle(&img, col * glob::gridWidth, row * glob::gridHeight,
			     glob::gridWidth, glob::gridHeight, BLACK);
	  ImageDrawRectangle(&img, col * glob::gridWidth + 1, row * glob::gridHeight + 1,
			     glob::gridWidth - 2, glob::gridHeight - 2, GREEN);
	}

	if(cell == glob::ObjCode::SNAKE_TAIL){
	  ImageDrawRectangle(&img, col * glob::gridWidth, row * glob::gridHeight,
			     glob::gridWidth, glob::gridHeight, DARKGREEN);
	}

	if(cell == glob::ObjCode::FOOD){
	  ImageDrawRectangle(&img, col * glob::gridWidth, row * glob::gridHeight,
			     glob::gridWidth, glob::gridHeight, RED);
	}
      }
    }
 
    Texture2D backgroundTexture = LoadTextureFromImage(img);
    DrawTextureRec(backgroundTexture, (Rectangle){0, 0, glob::winWidth, glob::winHeight},
		   Vector2Zero(), WHITE); 

    std::stringstream ss;
    ss << "Score: " << std::to_string(snake.getTail().size()); 
    DrawText(ss.str().data(), 1, 1, 30, WHITE);
      
    EndDrawing();
    UnloadImage(img);
    UnloadTexture(backgroundTexture);
    ///// End Drawing /////
  }

  CloseWindow();
  return 0;
}
