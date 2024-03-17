cmake_minimum_required(VERSION 3.28.1)
project(demo)

include(cmake/VendorLatebit.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
option(WASM "Build for WebAssembly" OFF)

if (WASM)
  set(SYSTEM_NAME "wasm")
else()
  set(SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
endif()

fetch_latebit("v0.1.0-rc.4" ${SYSTEM_NAME})

if (WASM)
  set(OUTPUT "public/index.html")
  
  file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/public)
  set(EMSCRIPTEN_FLAGS
    "-sUSE_SDL=2"
    "-sUSE_SDL_TTF=2"
    "-sUSE_SDL_MIXER=2"
    "-sSDL2_MIXER_FORMATS=[wav,mp3]"
  )
  
  foreach(FLAG ${EMSCRIPTEN_FLAGS})
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
  endforeach()

  add_executable(index.html main.cpp ${SRC_FILES})
  set_target_properties(index.html PROPERTIES LINK_FLAGS "-sSTACK_SIZE=5MB --preload-file assets")
  target_link_libraries(index.html PRIVATE latebit)
else()
  add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})
  target_link_libraries(${PROJECT_NAME} PRIVATE latebit)
  
  add_custom_target(run
      COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
      DEPENDS ${PROJECT_NAME}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif()