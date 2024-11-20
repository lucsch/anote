cmake_minimum_required(VERSION 3.19)
project(Anote)

# using git version
set(${PROJECT_NAME}_MAJOR_VERSION "3")
set(${PROJECT_NAME}_MINOR_VERSION "1")
include(cmake_modules/version.cmake)

find_package(wxWidgets CONFIG REQUIRED)

#search all source files
FILE (GLOB SRC_FILES src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# osx icon
if(APPLE)
	set(MACOSX_BUNDLE_ICON_FILE anote_icon.icns)
	set(ICON_PATH "${CMAKE_SOURCE_DIR}/art/anote_icon.icns")
	set_source_files_properties(${ICON_PATH} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif(APPLE)

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
		${SRC_FILES}
		${CMAKE_BINARY_DIR}/version.cpp
		${ICON_PATH}
		src/resource.rc)
target_link_libraries(${PROJECT_NAME} wx::core wx::base)

install(TARGETS ${PROJECT_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION bin
		BUNDLE DESTINATION .)
if(UNIX AND NOT APPLE)
	INSTALL(FILES install/anote.desktop DESTINATION share/applications)
	INSTALL(FILES art/Anote_icon.png DESTINATION share/icons)
endif(UNIX AND NOT APPLE)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "lucsch") #required for debian packages
SET(CPACK_DEBIAN_PACKAGE_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${GIT_NUMBER})
SET(CPACK_DEBIAN_FILE_NAME ${PROJECT_NAME}-${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${GIT_NUMBER}-Linux.deb)
include(CPack)
