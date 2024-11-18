cmake_minimum_required (VERSION 3.10)

project ("cevil")

set(debug "-g -O0")
set(release "-O3 -DNDEBUG")
set(gui "-Wl,-subsystem,windows")
set(dll "-shared")

set(CMAKE_CXX_FLAGS "-std=c++26 ${debug}")

set(OUT_DIR "cd/..")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${OUT_DIR}/tmp")

set (Game "Game")
set (modloader "oddmod")

add_library(${modloader} SHARED "modloader.cpp")
add_executable (${Game} "main.cpp")

target_link_options(${Game} PRIVATE
	${gui}
)
target_link_options(${modloader} PRIVATE
	${dll}
)
include_directories(
	"D:/DIMA/ALL/SDK/C++/SDL2/include"
)
target_link_libraries(${Game} PUBLIC
	${modloader}
	"D:/DIMA/ALL/SDK/C++/SDL2/lib/x64/SDL2.lib"
	"D:/DIMA/ALL/SDK/C++/SDL2/lib/x64/SDL2_image.lib"
	"D:/DIMA/ALL/SDK/C++/SDL2/lib/x64/SDL2_mixer.lib"
	"D:/DIMA/ALL/SDK/C++/SDL2/lib/x64/SDL2_ttf.lib"
	"D:/DIMA/ALL/SDK/C++/SDL2/lib/x64/SDL2_net.lib"
)
set_target_properties(${Game} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/__game/engine")
set_target_properties(${modloader} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/__game/engine")