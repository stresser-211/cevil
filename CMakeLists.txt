cmake_minimum_required (VERSION 3.10)

project ("cocojumbo")

set(dbg "-g -O0")
set(rel "-O3 -DNDEBUG")
set(gui "-Wl -subsystem windows")
set(dll "-shared")

set(CMAKE_CXX_FLAGS "-std=c++26 ${dbg}")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(OUT_DIR "./")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../Engine")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")

set (core "Core")
set (game "Game")
set (modloader "Register")
set (maploader "Terrain")
set (client "Client")

add_library(${core} SHARED "game/core/self.cpp")
add_library(${maploader} SHARED "game/maploader/self.cpp")
add_library(${client} SHARED "game/client/self.cpp")
add_executable(${modloader} "game/modloader/self.cpp")
add_executable (${game} "game/main.cpp")

target_link_options(${core} PRIVATE
	${dll}
)
target_link_options(${maploader} PRIVATE
	${dll}
)
target_link_options(${client} PRIVATE
	${dll}
)
target_link_options(${game} PRIVATE
	${gui}
)
include_directories(
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/include"
	"C:/SDK/C++/Lua/lua-5.4.2_win64/include"
	"C:/SDK/C++/Lua"
)
target_link_libraries(${core} PUBLIC
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2.a"
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_image.a"
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_mixer.a"
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_ttf.a"
)
target_link_libraries(${modloader} PRIVATE
	"C:/SDK/C++/Lua/lua-5.4.2_win64/liblua54.a"
)
target_link_libraries(${maploader} PRIVATE
	${core}
)
target_link_libraries(${client} PRIVATE
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_net.a"
)
target_link_libraries(${game} PRIVATE
	${core}
	${client}
	${maploader}
)
# set_target_properties(${game} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})