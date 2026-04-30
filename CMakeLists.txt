cmake_minimum_required ( VERSION 3.5 )

project ( OpenXcom )

set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )
include(BuildType)

set (CMAKE_CXX_STANDARD 23)

# Find OpenGL
set (OpenGL_GL_PREFERENCE LEGACY)
find_package ( OpenGL )
include_directories ( ${OPENGL_INCLUDE_DIR} )

# Include rapidyaml lib
include_directories(${CMAKE_SOURCE_DIR}/libs/rapidyaml)
if(NOT UNIX)
   include_directories ( deps/include/SDL deps/include )
   set( SDL_LIBRARY SDL )
   set ( SDLGFX_LIBRARY SDL_gfx )
   set ( SDLMIXER_LIBRARY SDL_mixer )
   set ( SDLIMAGE_LIBRARY SDL_image )

   set(DEPS_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib/x64)
elseif(UNIX)
    include(FindPkgConfig)
    pkg_check_modules(PKG_SDL REQUIRED sdl)
    pkg_check_modules(PKG_ZLIB REQUIRED zlib)
    pkg_check_modules(PKG_SDLIMAGE REQUIRED SDL_image)
    pkg_check_modules(PKG_SDLGFX REQUIRED SDL_gfx)
    pkg_check_modules(PKG_SDLMIXER REQUIRED SDL_mixer)

    include_directories(${PKG_SDL_INCLUDE_DIRS} ${PKG_ZLIB_INCLUDE_DIRS} ${PKG_SDLIMAGE_INCLUDE_DIRS})
    include_directories(${PKG_SDLGFX_INCLUDE_DIRS} ${PKG_SDLMIXER_INCLUDE_DIRS})
    set(PKG_DEPS_LDFLAGS ${PKG_SDL_LDFLAGS} ${PKG_ZLIB_LDFLAGS} ${PKG_SDLIMAGE_LDFLAGS} ${PKG_SDLGFX_LDFLAGS} ${PKG_SDLMIXER_LDFLAGS} ${OPENGL_LIBRARIES})
endif()

add_subdirectory ( src )
