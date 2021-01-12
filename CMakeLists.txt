cmake_minimum_required( VERSION 2.8 )
project( line_match )

# set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_BUILD_TYPE "Debug" )
# 这样${CMAKE_CXX_FLAGS}继承的写法更加安全
set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -O3" )
add_compile_options(-fPIC)

find_package( OpenCV 3.1 REQUIRED )

message(${PROJECT_NAME})
include_directories( 
    ${OpenCV_INCLUDE_DIRS} 
    ${PROJECT_SOURCE_DIR}/include
)

add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} )
