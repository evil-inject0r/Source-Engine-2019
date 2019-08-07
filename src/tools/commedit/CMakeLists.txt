#
#
# Project script for actbusy
#
#
project(commedit C CXX)

# Platform specific sources 
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

set(SRCS	commeditdoc.cpp
            commedittool.cpp
            commentarynodebrowserpanel.cpp
            commentarypropertiespanel.cpp
            dmecommentarynodeentity.cpp
            ${PUBLIC_INCLUDE}/interpolatortypes.cpp
            ${PUBLIC_INCLUDE}/registry.cpp
            ${PUBLIC_INCLUDE}/vgui_controls/vgui_controls.cpp)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ *.c *.cpp)
list(APPEND SRCS ${SOURCES})

# Preprocessor defs
set(DEFINES			-DCOMMEDIT_EXPORTS)

# Platform-specific preprocessor defines
set(WIN32_DEFINES	)	
set(POSIX32_DEFINES	)
set(WIN64_DEFINES	)
set(POSIX64_DEFINES	)
set(WINDOWS_DEFINES	)
set(POSIX_DEFINES	)

set(PLATFORM_64BIT_DEFINES	)
set(PLATFORM_32BIT_DEFINES 	)

# Links dirs to search for link libs in
set(LINK_DIRS	)
set(WINDOWS_LINK_DIRS	)
set(POSIX_LINK_DIRS		)
set(WIN32_LINK_DIRS		)
set(WIN64_LINK_DIRS		)
set(POSIX32_LINK_DIRS	)
set(POSIX64_LINK_DIRS	)

# Generic libs to link against
set(LINK_LIBS			)

# Other projects this one depends on
set(DEPENDENCIES vstdlib tier0)

# Platform specific link libs
set(WINDOWS_LINK_LIBS	ws2_32.lib DK2WIN32.LIB)
set(WIN32_LINK_LIBS		)
set(WIN64_LINK_LIBS		)
set(POSIX32_LINK_LIBS	)
set(POSIX64_LINK_LIBS	)

# Generic include dirs
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/tier1 ${PUBLIC_INCLUDE}/tier0 ${PUBLIC_INCLUDE}/vstdlib)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET commedit)

# Set the output file name
set(OUTPUT_FILE_NAME commedit)

# If this is a shared lib
set(SHARED_LIB 1)

# If this is a static lib
set(STATIC_LIB 0)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/library-base.cmake)
