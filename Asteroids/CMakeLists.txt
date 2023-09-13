# CMakeList.txt : CMake project for QTProject, include source and define
# project specific logic here.
#

# Add source to this project's executable.
file(GLOB CPP . *.cpp)
file(GLOB HPP . *.h)

add_executable (Asteroids ${HPP} ${CPP})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Asteroids PROPERTY CXX_STANDARD 20)
endif()
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_CXX_STANDARD 17)
set(SFML_PATH "${PROJECT_SOURCE_DIR}/lib/SFML-2.5.1-windows-vc15-64-bit")

target_compile_options(Asteroids PUBLIC "/Zc:__cplusplus")
target_include_directories(Asteroids PRIVATE "${SFML_PATH}/include")

set(CMAKE_PREFIX_PATH "${SFML_PATH}/lib/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SFML_PATH}/bin")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

target_link_libraries(Asteroids sfml-graphics sfml-audio)