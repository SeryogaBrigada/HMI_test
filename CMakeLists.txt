cmake_minimum_required(VERSION 3.1)

project(HMI_test LANGUAGES CXX)
add_subdirectory("aktualizr")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "provider.cpp" "provider.h" "updater.cpp" "updater.h" "qml.qrc")
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick PUBLIC aktualizr_static_lib ${AKTUALIZR_EXTERNAL_LIBS} )
set_property(GLOBAL PROPERTY JOB_POOL_COMPILE 4)
set_property(GLOBAL PROPERTY JOB_POOL_LINK 4)
