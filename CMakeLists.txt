# --- Provided as a reference, please add your CMakeLists.txt to .gitignore --- #
cmake_minimum_required (VERSION 3.10)
project (
	"Medieval Life"
	VERSION 0.0.0.0
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++26")
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(OUT_DIR "./")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../game-win7x64/Engine")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")

set (core "Core")
set (modloader "LogicGatekeeper")
set (maploader "Terrain")
set (client "Client")
set (game "Game")

add_library(${core} SHARED
	"game/core/fundamentals.cpp"
	"game/core/nodes.cpp"
	"game/core/self.cpp"
)
add_library(${modloader} SHARED "game/modloader/self.cpp")
add_library(${maploader} SHARED "game/maploader/self.cpp")
add_library(${client} SHARED "game/client/self.cpp")
add_executable (${game} "game/main.cpp")

target_link_options(${core} PRIVATE
	"-shared"
)
target_link_options(${modloader} PRIVATE
	"-shared"
)
target_link_options(${maploader} PRIVATE
	"-shared"
)
target_link_options(${client} PRIVATE
	"-shared"
)
target_link_options(${game} PRIVATE
	"-mwindows"
)

include_directories(
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/include"
	"C:/SDK/C++/Lua/lua-5.4.2_win64/include"
	"C:/SDK/C++/argparse"
)

target_link_libraries(${core} PUBLIC
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2.dll.a"
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2main.a"
	"-lwinmm -lopengl32"
)
target_link_libraries(${core} PRIVATE
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_mixer.dll.a"
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a"
	"-lmsvcrt -lmingw32 -lsetupapi -limm32 -lversion -lrpcrt4"
)
target_link_libraries(${modloader} PRIVATE
	"C:/SDK/C++/Lua/lua-5.4.2_win64/liblua54.a"
)
target_link_libraries(${maploader} PRIVATE
	${core}
)
target_link_libraries(${client} PRIVATE
	${core}
	"C:/SDK/C++/SDL2/x86_64-w64-mingw32/lib/libSDL2_net.a"
)
target_link_libraries(${game} PUBLIC
	${core}
	${client}
	${modloader}
	${maploader}
)