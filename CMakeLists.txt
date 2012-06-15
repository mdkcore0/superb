cmake_minimum_required(VERSION 2.6)
project(superb)

set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_CXX_FLAGS "-Wall")

find_package(Qt4 REQUIRED)
 
include(${QT_USE_FILE})

set(superb_H
	mainwindow.h
	environment.h
	lifeworld.h
	)
set(superb_UI)
set(superb_RES)

qt4_wrap_cpp(superb_MOC_CPP ${superb_H})
qt4_wrap_ui(superb_UI_CPP ${superb_UI})
qt4_add_resources(superb_RES_H ${superb_RES})

#include_directories(.)

set(superb_SRCS
	main.cpp
	mainwindow.cpp
	environment.cpp
	lifeworld.cpp
	${superb_MOC_CPP}
	${superb_UI_CPP}
	${superb_RES_H}
	)

set(superb_LIB ${QT_LIBRARIES})

add_executable(superb ${superb_SRCS})
target_link_libraries(superb ${superb_LIB})
#install_targets(/bin superb)

# reference: http://blog.cor-net.org/hello-world-in-qt-using-cmake-and-openembedded/2/

