# For make-based builds, defines make target named test.
# For Visual Studio builds, defines Visual Studio project named RUN_TESTS.
enable_testing()

# Google Test
set(gtest_force_shared_crt ON CACHE INTERNAL "")

include_directories(
	${GTEST_INCLUDE_DIR}
)

file(GLOB OpenInfraPlatform_UnitTests_Source src/OpenInfraPlatform/UnitTests/*.*)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DArbitraryCurve)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DArc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DClothoid)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/HorizontalAlignmentElement2DLine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/OkstraExportImport)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/OpenInfraPlatform/UnitTests/Infrastructure/TrafficSign)
