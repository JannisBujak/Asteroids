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

# set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
	set(SFML_PATH "${PROJECT_SOURCE_DIR}/lib/MSVC/SFML-2.5.1-windows-vc15-64-bit")
endif (MSVC)

if (UNIX)
	set(SFML_PATH "${PROJECT_SOURCE_DIR}/lib/UNIX/SFML_2.6.0_Linux")
	message("UNIX")
endif (UNIX)

# target_compile_options(Asteroids PUBLIC "/Zc:__cplusplus")

target_include_directories(Asteroids PRIVATE "${SFML_PATH}/include")
# target_include_directories(Asteroids PRIVATE "$ENV{QTDIR}/include")

list(APPEND CMAKE_PREFIX_PATH "${SFML_PATH}")
# list(APPEND CMAKE_PREFIX_PATH "$ENV{QTDIR}")

# message("$ENV{QTDIR}/lib/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${SFML_PATH}/bin")

# Link SFML libraries
target_link_libraries(Asteroids sfml-graphics sfml-window sfml-system)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
# find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)

target_link_libraries(Asteroids sfml-graphics sfml-audio)
# target_link_libraries(Asteroids Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Concurrent)


