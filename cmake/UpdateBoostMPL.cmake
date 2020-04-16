find_package(Python2 REQUIRED)
get_filename_component(Python2_DIRECTORY ${Python2_EXECUTABLE} DIRECTORY)

#find_file(Python_2to3_SCRIPT NAMES 2to3.py HINTS "${Python_DIRECTORY}\\Tools\\scripts" REQUIRED)

# Get root directory of Qt installation
string(FIND ${Qt5_DIR} "Qt" POS)
string(SUBSTRING ${Qt5_DIR} 0 ${POS} Qt5_ROOT)
string(SUBSTRING ${Qt5_DIR} ${POS} 2 Qt5_ROOT_SUFFIX)
string(APPEND Qt5_ROOT ${Qt5_ROOT_SUFFIX})
message(STATUS ${Qt5_ROOT})

# Set path to MinGW bin folder containing gcc executable
set(MinGW_DIR ${Qt5_ROOT}/Tools/mingw730_64/bin)

# Get Python and MinGW directories in native path format to add them to %PATH% variable
file(TO_NATIVE_PATH ${MinGW_DIR} MinGW_DIR)
file(TO_NATIVE_PATH ${Python2_DIRECTORY} Python2_DIRECTORY)

add_custom_target(OpenInfraPlatform.Commands.UpdateBoostMPL
	COMMAND set PYTHON_PATH=${Python2_DIRECTORY}
	COMMAND set GCC_PATH=${MinGW_DIR}
	COMMAND set PATH=%GCC_PATH%\;%PYTHON_PATH%\;%PATH%;
	COMMAND echo %PATH%
	COMMAND ${Python2_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/fix_boost_mpl_preprocess.py ${Boost_INCLUDE_DIR}
	COMMAND ${Python2_EXECUTABLE} ${Boost_INCLUDE_DIR}/libs/mpl/preprocessed/boost_mpl_preprocess.py --sequence-type=both --num-elements=100 ${Boost_INCLUDE_DIR}
)
set_target_properties(OpenInfraPlatform.Commands.UpdateBoostMPL PROPERTIES FOLDER "OpenInfraPlatform/Commands")