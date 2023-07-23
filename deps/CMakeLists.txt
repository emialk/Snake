include(FetchContent)

# Raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        fec96137e8d10ee6c88914fbe5e5429c13ee1dac  # release-4.5.0
)

FetchContent_MakeAvailable(raylib)
