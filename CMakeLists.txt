cmake_minimum_required(VERSION 3.5)
project(ray_casting)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_library(geom SHARED src/geometry/vector.c src/geometry/triangle.c src/geometry/ray.c src/geometry/matrix.c)
add_library(utf8 SHARED src/utf8/utf8_utils.c src/utf8/utf8_ctype.c src/utf8/utf8_read.c src/utf8/utf8_write.c)
add_library(coll SHARED src/collections/arrayList.c src/collections/stack.c src/collections/queue.c)
add_library(util SHARED src/utils/utils.c)

target_link_libraries(geom PRIVATE util)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable("${PROJECT_NAME}" src/main.c src/objParser/objParser.c src/gui/draw.c src/gui/window.c src/gui/render.c)
target_link_libraries("${PROJECT_NAME}" utf8 coll util geom m ${GTK3_LIBRARIES})
