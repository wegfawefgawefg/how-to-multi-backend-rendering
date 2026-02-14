cmake_minimum_required(VERSION 3.16)
project(how_to_multi_backend_rendering VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MBR_USE_BUNDLED_SDL "Fetch SDL2 from source when system package is unavailable" OFF)

set(MBR_TARGET multi_backend_demo)
if (ANDROID)
    # SDLActivity loads libmain.so by default on Android.
    set(MBR_TARGET main)
    add_library(${MBR_TARGET} SHARED
        src/main.cpp
        src/app/DemoScene.cpp
        src/renderer/RendererFactory.cpp
        src/renderer/SDLRenderer2D.cpp
    )
else()
    add_executable(${MBR_TARGET}
        src/main.cpp
        src/app/DemoScene.cpp
        src/renderer/RendererFactory.cpp
        src/renderer/SDLRenderer2D.cpp
    )
endif()

target_include_directories(${MBR_TARGET} PRIVATE include)

if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set_target_properties(${MBR_TARGET} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.multibackenddemo"
        MACOSX_BUNDLE_BUNDLE_NAME "MultiBackendDemo"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    )
endif()

if (MSVC)
    target_compile_options(${MBR_TARGET} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${MBR_TARGET} PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (EMSCRIPTEN)
    # Emscripten supplies SDL2 when USE_SDL=2 is enabled.
    # Output .html for easiest local testing.
    set_target_properties(${MBR_TARGET} PROPERTIES SUFFIX ".html")
    target_compile_options(${MBR_TARGET} PRIVATE "-sUSE_SDL=2")
    target_link_options(${MBR_TARGET} PRIVATE
        "-sUSE_SDL=2"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sASSERTIONS=1"
        "-sWASM=1"
    )
else()
    if (MBR_USE_BUNDLED_SDL)
        include(FetchContent)
        FetchContent_Declare(
            SDL2
            URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.9.zip
        )
        set(SDL_SHARED OFF CACHE BOOL "" FORCE)
        set(SDL_STATIC ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(SDL2)

        if (TARGET SDL2::SDL2)
            target_link_libraries(${MBR_TARGET} PRIVATE SDL2::SDL2)
        elseif(TARGET SDL2-static)
            target_link_libraries(${MBR_TARGET} PRIVATE SDL2-static)
        else()
            message(FATAL_ERROR "Bundled SDL2 enabled but no expected SDL2 target was created.")
        endif()

        if (TARGET SDL2main)
            target_link_libraries(${MBR_TARGET} PRIVATE SDL2main)
        endif()
    else()
        find_package(SDL2 QUIET)
        if (TARGET SDL2::SDL2)
            target_link_libraries(${MBR_TARGET} PRIVATE SDL2::SDL2)
        elseif (TARGET SDL2::SDL2-static)
            target_link_libraries(${MBR_TARGET} PRIVATE SDL2::SDL2-static)
        else()
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(SDL2 REQUIRED sdl2)
            target_include_directories(${MBR_TARGET} PRIVATE ${SDL2_INCLUDE_DIRS})
            target_link_libraries(${MBR_TARGET} PRIVATE ${SDL2_LIBRARIES})
            target_compile_options(${MBR_TARGET} PRIVATE ${SDL2_CFLAGS_OTHER})
            target_link_options(${MBR_TARGET} PRIVATE ${SDL2_LDFLAGS_OTHER})
        endif()
    endif()
endif()
