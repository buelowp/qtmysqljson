project(qtmysqljson)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 COMPONENTS Core Sql qmqtt REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${Qt5Core_LIBRARIES} ${Qt5Sql_LIBRARIES} ${Qt5qmqtt_LIBRARIES})

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
