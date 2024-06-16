cmake_minimum_required(VERSION 3.5)

project(vsomeip_project_client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

if(ANDROID)
  add_library(vsomeip_project_client SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    client.cpp
    client.h
    engine.cpp
    engine.h
  )
else()
  add_executable(vsomeip_project_client
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    client.h
    client.cpp
    engine.cpp
    engine.h

  )
endif()
include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)


target_link_libraries(vsomeip_project_client PRIVATE Qt5::Widgets vsomeip3 ${Boost_LIBRARIES})
