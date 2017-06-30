cmake_minimum_required(VERSION 3.1.0)
project(QSimpleUpdater)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	../../Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	../../Release)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG 	    ../../Debug)
set(CMAKE_PDB_OUTPUT_DIRECTORY_RELEASE 	    ../../Release)

set(CMAKE_DEBUG_POSTFIX  "d")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_definitions(${QT_DEFINITIONS})

set(SOURCES
  src/qsimpleupdater.cpp
  src/dialogs/download_dialog.cpp
)

set(MOC_HEADERS
  src/qsimpleupdater.h
  src/dialogs/download_dialog.h
)

set(UIS
  src/dialogs/download_dialog.ui
)

qt5_wrap_ui(UI_HEADERS ${UIS})

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)
add_library(QSimpleUpdater STATIC ${SOURCES} ${MOC_HEADERS} ${MOC_SOURCES} ${UIS})

# Use the Widgets module from Qt 5.
qt5_use_modules(QSimpleUpdater Widgets Network)