cmake_minimum_required (VERSION 2.8.11)
project(MPU6050)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Sensors)

file(GLOB SOURCE_FILES *.cpp)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_PLUGIN)

add_library(
    mpu6050 SHARED
    ${SOURCE_FILES}
)

target_link_libraries(mpu6050
    Qt5::Sensors
)

install(
    TARGETS mpu6050
    DESTINATION sensors
)
