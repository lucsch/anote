cmake_minimum_required(VERSION 3.0)
project(Anote)

# cmake magical command for conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# using git version
set(${PROJECT_NAME}_MAJOR_VERSION "3")
set(${PROJECT_NAME}_MINOR_VERSION "1")
include(cmake_modules/version.cmake)

#search all source files
FILE (GLOB SRC_FILES src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# osx icon
set(MACOSX_BUNDLE_ICON_FILE anote_icon.icns)
set(ICON_PATH "${CMAKE_SOURCE_DIR}/art/anote_icon.icns")
set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

include_directories(include)
add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
		${SRC_FILES}
		${CMAKE_BINARY_DIR}/version.cpp
		${ICON_PATH}
		src/resource.rc)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})


