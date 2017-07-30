find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_GFX_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_subdirectory(sim)
add_subdirectory(render)

add_executable(ludumdare39-game main.cpp)
target_link_libraries(ludumdare39-game render sim ${SDL2_IMAGE_LIBRARIES} ${SDL2_GFX_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_LIBRARY})
