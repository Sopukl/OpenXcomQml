cmake_policy(SET CMP0009 NEW)  #GLOB_RECURSE
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    Qml
    QuickControls2
)
add_definitions(-DQT_NO_EMIT)

if (MSVC)
    add_compile_options(/wd4503)  # decorated name length exceeded
    add_compile_options(/wd4661)  # no suitable definition provided for explicit template instantiation request
    add_compile_options(/wd4267)  # conversion from 'size_t' to 'int', possible loss of data
    add_compile_options(/wd4244)  # conversion from 'double' to 'float', possible loss of data
    add_compile_options(/wd4244)  # conversion from 'double' to 'float', possible loss of data
    add_compile_options(/wd5030)  # attribute [[gnu::always_inline]] is not recognized
    add_compile_options(/bigobj)
endif()

set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/src/Qml ${CMAKE_BINARY_DIR}/imports CACHE STRING "")

set ( root_src
  lodepng.cpp
  main.cpp
  md5.cpp
  GameRenderer.cpp
  XcomImagesProvider.cpp
)

file(GLOB_RECURSE basescape_src "Basescape/*.cpp")
file(GLOB_RECURSE battlescape_src "Battlescape/*.cpp")
file(GLOB_RECURSE engine_src "Engine/*.cpp")
file(GLOB_RECURSE geoscape_src "Geoscape/*.cpp")
file(GLOB_RECURSE interface_src "Interface/*.cpp")
file(GLOB_RECURSE menu_src "Menu/*.cpp")
file(GLOB_RECURSE mod_src "Mod/*.cpp")
file(GLOB_RECURSE savegame_src "Savegame/*.cpp")
file(GLOB_RECURSE ufopedia_src "Ufopaedia/*.cpp")

set ( rapidyaml_src
  ../libs/rapidyaml/c4/base64.cpp
  ../libs/rapidyaml/c4/char_traits.cpp
  ../libs/rapidyaml/c4/error.cpp
  ../libs/rapidyaml/c4/format.cpp
  ../libs/rapidyaml/c4/language.cpp
  ../libs/rapidyaml/c4/memory_resource.cpp
  ../libs/rapidyaml/c4/memory_util.cpp
  ../libs/rapidyaml/c4/utf.cpp
  ../libs/rapidyaml/c4/yml/common.cpp
  ../libs/rapidyaml/c4/yml/node.cpp
  ../libs/rapidyaml/c4/yml/node_type.cpp
  ../libs/rapidyaml/c4/yml/parse.cpp
  ../libs/rapidyaml/c4/yml/preprocess.cpp
  ../libs/rapidyaml/c4/yml/reference_resolver.cpp
  ../libs/rapidyaml/c4/yml/tag.cpp
  ../libs/rapidyaml/c4/yml/tree.cpp
  ../libs/rapidyaml/c4/yml/version.cpp

)

set ( cxx_src
    ${root_src}
    ${basescape_src}
    ${battlescape_src}
    ${engine_src}
    ${geoscape_src}
    ${interface_src}
    ${menu_src}
    ${mod_src}
    ${savegame_src}
    ${ufopedia_src}
    ${rapidyaml_src}
)
set ( c_src
  ../libs/miniz/miniz.c
)

file(GLOB_RECURSE all_headers
    "*.h"
    "*.hpp"
    "../libs/rapidyaml/**/*.h"
)

set ( openxcom_src ${c_src} ${cxx_src})

add_executable (
    openxcom
    ${openxcom_src}
    ${all_headers}
    Qml/XCom.qrc
    Images.qrc
)

target_link_libraries(openxcom
    Qt6::Core
    Qt6::Quick
    Qt6::Qml
    Qt6::QuickControls2
)

if(NOT UNIX)
    target_link_directories(openxcom PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../deps/lib/x64)

    target_link_libraries(openxcom
        ${system_libs}
        ${EXTRA_XCOM_LIBS}
        ${WIN32_LIBS}
        SDLmain
        ${SDL_LIBRARY}
        ${SDLMIXER_LIBRARY}
        ${SDLIMAGE_LIBRARY}
        ${SDLGFX_LIBRARY}
        opengl32
    )
else()
    target_link_libraries(openxcom
        ${system_libs}
        ${PKG_DEPS_LDFLAGS}
        ${EXTRA_XCOM_LIBS}
        ${WIN32_LIBS}
    )
endif()
