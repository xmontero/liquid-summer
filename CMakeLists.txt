SET( CMAKE_SYSTEM_NAME Windows )

SET( CMAKE_C_COMPILER x86_64-w64-mingw32-gcc )
SET( CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++ )
SET( CMAKE_RC_COMPILER x86_64-w64-mingw32-windres )

# here is the target environment located
SET( CMAKE_FIND_ROOT_PATH /files/fluor/fluor_compiler_test/SDL2-2.0.3/x86_64-w64-mingw32 /usr/x86_64-w64-mingw32 )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

cmake_minimum_required( VERSION 2.6 )
project( liquid-summer )

# Use our modified FindSDL2* modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${liquid-summer_SOURCE_DIR}/cmake" )
set( BIN_DIR ${liquid-summer_SOURCE_DIR}/bin )

# Bump up warning levels appropriately for clang, gcc & msvc and build in debug mode
if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11 -static -static-libgcc -static-libstdc++" )
	set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g" )
	set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2" )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC" )
	if( CMAKE_CXX_FLAGS MATCHES "/W[0-4]" )
		string( REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )
	else()
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" )
	endif()
endif()

find_package( SDL2 REQUIRED )
include_directories( ${SDL2_INCLUDE_DIR} )
include_directories( include )

find_package( SDL2_image REQUIRED )
include_directories( ${SDL2_IMAGE_INCLUDE_DIR} )

find_package( SDL2_ttf REQUIRED )
include_directories( ${SDL2_TTF_INCLUDE_DIR} )

add_executable( liquid-summer
	src/AffineTransformation.cpp
	src/AffineTransformations.cpp
	src/Fractal.cpp
	src/LiquidSummer.cpp
	src/main.cpp
	src/Matrix3x3.cpp
	src/StarField.cpp
	src/Vector3d.cpp
)

target_link_libraries( liquid-summer ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} )
install( TARGETS liquid-summer RUNTIME DESTINATION ${BIN_DIR} )
