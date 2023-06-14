cmake_minimum_required(VERSION 3.25)
project(firmaSoft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/culbec/Qt/6.5.0/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(firmaSoft main.cpp headers/soft.h tester.cpp tester.h sources/soft.cpp headers/repo.h sources/repo.cpp headers/service.h sources/service.cpp headers/GUI.h headers/Observer.h headers/Observable.h sources/GUI.cpp headers/TableModel.h)
target_link_libraries(firmaSoft
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

