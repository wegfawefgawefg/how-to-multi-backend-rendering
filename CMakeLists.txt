cmake_minimum_required(VERSION 3.16)
project(how_to_multi_backend_rendering VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MBR_USE_BUNDLED_SDL "Fetch SDL2 from source when system package is unavailable" OFF)

add_executable(multi_backend_demo
    src/main.cpp
    src/app/DemoScene.cpp
    src/renderer/RendererFactory.cpp
    src/renderer/SDLRenderer2D.cpp
)

target_include_directories(multi_backend_demo PRIVATE include)

if (MSVC)
    target_compile_options(multi_backend_demo PRIVATE /W4 /permissive-)
else()
    target_compile_options(multi_backend_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()

if (EMSCRIPTEN)
    # Emscripten supplies SDL2 when USE_SDL=2 is enabled.
    # Output .html for easiest local testing.
    set_target_properties(multi_backend_demo PROPERTIES SUFFIX ".html")
    target_link_options(multi_backend_demo PRIVATE
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
            target_link_libraries(multi_backend_demo PRIVATE SDL2::SDL2)
        elseif(TARGET SDL2-static)
            target_link_libraries(multi_backend_demo PRIVATE SDL2-static)
        else()
            message(FATAL_ERROR "Bundled SDL2 enabled but no expected SDL2 target was created.")
        endif()
    else()
        find_package(SDL2 QUIET)
        if (TARGET SDL2::SDL2)
            target_link_libraries(multi_backend_demo PRIVATE SDL2::SDL2)
        elseif (TARGET SDL2::SDL2-static)
            target_link_libraries(multi_backend_demo PRIVATE SDL2::SDL2-static)
        else()
            find_package(PkgConfig REQUIRED)
            pkg_check_modules(SDL2 REQUIRED sdl2)
            target_include_directories(multi_backend_demo PRIVATE ${SDL2_INCLUDE_DIRS})
            target_link_libraries(multi_backend_demo PRIVATE ${SDL2_LIBRARIES})
            target_compile_options(multi_backend_demo PRIVATE ${SDL2_CFLAGS_OTHER})
            target_link_options(multi_backend_demo PRIVATE ${SDL2_LDFLAGS_OTHER})
        endif()
    endif()
endif()
