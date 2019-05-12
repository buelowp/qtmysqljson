project(dbinterface)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core)

include_directories(${Qt5Core_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

set(dbinterface_SRCS dbinterface.cpp main.cpp)

set( CMAKE_AUTOMOC ON )
add_executable(dbinterface ${dbinterface_SRCS})
target_link_libraries(dbinterface ${Qt5Core_LIBRARIES})

install(TARGETS dbinterface RUNTIME DESTINATION bin)
