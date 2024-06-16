cmake_minimum_required(VERSION 3.13)

project(vsomeip_project LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_FLAGS "-g -std=c++0x")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package (vsomeip3 3.4.10 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

if(ANDROID)
  add_library(vsomeip_project SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    engine.h
    engine.cpp
    service.h
    service.cpp
  )
else()
  add_executable(vsomeip_project
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    engine.h
    engine.cpp
    service.h
    service.cpp
  )
endif()

target_link_libraries(vsomeip_project PRIVATE Qt5::Widgets vsomeip3 ${Boost_LIBRARIES})
