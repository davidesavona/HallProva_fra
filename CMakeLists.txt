cmake_minimum_required(VERSION 3.0.0)
project(hallProva VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(hallProva main.cpp hallsensor.cpp hallsensor.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(hallProva pthread wiringPi jsoncpp )
include(CPack)
