# CMAKE BUILD FILE FOR Anote
# (c) LUCIEN SCHREIBER CREALP 2007
cmake_minimum_required(VERSION 2.6)


PROJECT (Anote)

#search all source files
FILE (GLOB SRC_FILES ../src/*.cpp)
SOURCE_GROUP (source FILES ${SRC_FILES})

# search all headers files
FILE (GLOB HEAD_FILES "../include/*.h")
SOURCE_GROUP (header FILES ${HEAD_FILES})


MESSAGE ("Build type is : " ${CMAKE_BUILD_TYPE})

# WXWIDGETS
# DEFINE ALL INCLUDES AND SO ON
 SET(WXWINDOWS_USE_GL 0)
 
 INCLUDE ("cmake/Use_wxWindows.cmake")


IF( APPLE )
	SET (APP_ICON "Anote_icon.icns")
	
	
	#bundle variables for compilation under Mac OS
	SET(MACOSX_BUNDLE_INFO_STRING "Program for doxygen compatible comments")
	SET(MACOSX_BUNDLE_ICON_FILE ${APP_ICON})
	#MACOSX_BUNDLE_GUI_IDENTIFIER
	#MACOSX_BUNDLE_LONG_VERSION_STRING
	SET(MACOSX_BUNDLE_BUNDLE_NAME "Anote")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "3.0")
	SET(MACOSX_BUNDLE_BUNDLE_VERSION "3.0")
	SET(MACOSX_BUNDLE_COPYRIGHT "Lucien Schreiber (c) CREALP 2007")
	
	# Need to copy the icon file
	 EXEC_PROGRAM( "mkdir -p       ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Anote.app/Contents/Resources")
	 EXEC_PROGRAM( "cp ${PROJECT_SOURCE_DIR}/../art/${APP_ICON} ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Anote.app/Contents/Resources")
ENDIF (APPLE)
 
# conditionnal compilation if windows needs ressource
IF (WIN32)

	SOURCE_GROUP (resource FILES ../src/anote.rc)
 	ADD_EXECUTABLE (Anote WIN32 ${SRC_FILES} ${HEAD_FILES} ../src/anote.rc)
 	TARGET_LINK_LIBRARIES (Anote ${WXWINDOWS_LIBS})

ELSE (WIN32)
 
 	ADD_EXECUTABLE (Anote MACOSX_BUNDLE ${SRC_FILES} ${HEAD_FILES})
 	#TARGET_LINK_LIBRARIES (shapecheck)
	IF(UNIX)
		#make the .desktop file
		EXEC_PROGRAM( "sh ${PROJECT_SOURCE_DIR}/../install/linux/create_desktop_file.sh Anote ${CMAKE_INSTALL_PREFIX}")
		# install the program and add an icon
		INSTALL(TARGETS Anote RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
		INSTALL(FILES "${PROJECT_BINARY_DIR}/Anote.desktop" DESTINATION ${CMAKE_INSTALL_PREFIX} PERMISSIONS WORLD_WRITE WORLD_READ WORLD_EXECUTE)
		INSTALL(FILES "${PROJECT_BINARY_DIR}/Anote.desktop" DESTINATION /usr/share/applications)
		INSTALL(FILES "${PROJECT_SOURCE_DIR}/../art/Anote_icon.png" DESTINATION /usr/share/pixmaps RENAME Anote.png)
	ENDIF(UNIX)
ENDIF (WIN32)


# SHOULD WE USE THE MT VERSION FOR DEFAULT 
# COMPATIBILITY WITH < WINXP
IF (WIN32)
	INCLUDE ("cmake/Use_visualstudioMT.cmake")
ENDIF (WIN32)


