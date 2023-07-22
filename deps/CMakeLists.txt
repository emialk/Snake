include(FetchContent)

# Google test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b796f7d44681514f58a683a3a71ff17c94edb0c1 # release-1.13.0
)

# SPDLOG
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG        7e635fca68d014934b4af8a1cf874f63989352b7  # release-1.12.0
)

# Raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        fec96137e8d10ee6c88914fbe5e5429c13ee1dac  # release-4.5.0
)


FetchContent_MakeAvailable(googletest spdlog raylib)
