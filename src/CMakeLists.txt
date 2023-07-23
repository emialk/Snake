
add_library(snake_src
  world_grid.cpp
  world_grid.h
  player.cpp
  player.h
  glob.cpp
  glob.h
  )

target_include_directories(snake_src PUBLIC .)
target_link_libraries(snake_src PRIVATE raylib)
target_compile_options(snake_src PRIVATE ${DEFAULT_WARNINGS})
# Run clang-tidy when building
set_target_properties(snake_src PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
