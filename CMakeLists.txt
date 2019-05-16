project(dbinterface)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(dbinterface_SRCS main.cpp dbinterface.cpp)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Sql)
add_executable(dbinterface ${dbinterface_SRCS})
target_link_libraries(dbinterface ${Qt5Core_LIBRARIES} ${Qt5Sql_LIBRARIES})

install(TARGETS dbinterface RUNTIME DESTINATION bin)
