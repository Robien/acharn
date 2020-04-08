cmake_minimum_required(VERSION 2.6)
PROJECT(acharn)
set(CMAKE_CXX_FLAGS "")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
SET(CMAKE_USE_RELATIVE_PATHS "ON")


IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

IF(CMAKE_CXX_FLAGS_DEBUG)
   SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
ELSE(CMAKE_CXX_FLAGS_DEBUG)
   SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
ENDIF(CMAKE_CXX_FLAGS_DEBUG)


SET(CMAKE_CXX_FLAGS "-std=c++0x")

# Included stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Modules/")
# This is done here so that relative search paths are more reasonable
find_package(Irrlicht)
find_package(OpenAL)
find_package(LibSndFile)
find_package(OpenGL)

#Inclusion de Boost
include(FindBoost)
find_package(
	Boost
	1.39.0
	REQUIRED thread
)

link_directories(
${Boost_LIBRARY_DIRS}
)

INCLUDE_DIRECTORIES(
   ${X11_INCLUDE_DIR}
   ${PROJECT_SOURCE_DIR}/include
   ${PROJECT_SOURCE_DIR}
   ${Boost_INCLUDE_DIRS}
   ${IRRLICHT_INCLUDE_DIR}
   ${OPENAL_INCLUDE_DIR}
   ${OPENGL_INCLUDE_DIRS}
	ackCore/include/
	ackAudio/include/
	ackPerso/include/
	ackUtils/include/
	ackClient/include/
	ackInterface/include/
	ackTache/include/
	application/include/
)


file(
	GLOB
	source_files
	ackCore/src/*.cpp
	ackAudio/src/*.cpp
	ackPerso/src/*.cpp
	ackUtils/src/*.cpp
	ackClient/src/*.cpp
	ackInterface/src/*.cpp
	ackTache/src/*.cpp
	application/*.cpp
)

ADD_EXECUTABLE(
   acharn
   ${source_files}
)

TARGET_LINK_LIBRARIES(acharn
   ${Boost_LIBRARIES}
${OPENAL_LIBRARY}
${IRRLICHT_LIBRARY}
${LIBSNDFILE_LIBRARY}
)
