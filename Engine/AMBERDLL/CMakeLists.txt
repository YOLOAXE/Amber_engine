CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
PROJECT(AMBERDLL)

# Param�tres

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/BuildDLL)
SET(BUILD_FRAMEWORK 1)

# Compiler detection
IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    # Using GNU GCC
    SET(AMBER_USE_GCC 1)

    IF(WIN32)
        SET(COMPILER_DEPENDENCIES ${MINGW_DEPENDENCIES} -lpsapi)
    ELSE()
        SET(COMPILER_DEPENDENCIES ${GCC_DEPENDENCIES})
    ENDIF()

    ADD_DEFINITIONS(-D AMBER_USE_GCC)
    MESSAGE(STATUS "Detected Compiler : GCC")

    # For GCC, setting flags
    SET(CXX_RELEASE_FLAGS   "-Wall -O3")
    SET(CXX_DEBUG_FLAGS   "-Wall -Wextra -g -Wdouble-promotion -Wno-attributes")

ELSEIF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    # Using Visual Studio C++
    SET(AMBER_USE_MSVC 1)
    SET(COMPILER_DEPENDENCIES ${MVSC_DEPENDENCIES})
    ADD_DEFINITIONS(-D AMBER_USE_MSVC)
    MESSAGE(STATUS "Compilateur d�tect� : MSVC")

    # No flags for MVSC
    # For GCC, setting flags
    # SET(CXX_RELEASE_FLAGS "")
    # SET(CXX_DEBUG_FLAGS   "")

ELSE()

    # TODO
    SET(COMPILER_DEPENDENCIES)
    MESSAGE(FATAL_ERROR "Compilateur d�tect� : Inconnu, veuillez utiliser GCC ou MSVC.")

ENDIF()

#Detection de l'os
IF(WIN32)

    #Windows
    SET(AMBER_WINDOWS 1)
    SET(PLATFORM_DEPENDENCIES ${WIN32_DEPENDENCIES})
    ADD_DEFINITIONS(-D AMBER_WINDOWS)
    MESSAGE(STATUS "Plateforme d�tect�e : Windows")

ELSEIF(UNIX)

    #Unix OS
    SET(AMBER_UNIX 1)
    SET(PLATFORM_DEPENDENCIES ${UNIX_DEPENDENCIES})
    ADD_DEFINITIONS(-D AMBER_UNIX)
    MESSAGE(STATUS "Plateforme d�tect�e : Unix")

ELSEIF(APPLE)

    #Mac os
    SET(AMBER_APPLE 1)
    SET(PLATFORM_DEPENDENCIES ${APPLE_DEPENDENCIES})
    ADD_DEFINITIONS(-D AMBER_APPLE)
    MESSAGE(STATUS "Plateforme d�tect�e : Apple")

ELSE()

    #Non support�
    SET(PLATFORM_NOT_SUPORTED 0)
    SET(PLATFORM_DEPENDENCIES)
    ADD_DEFINITIONS(-D PLATFORM_NOT_SUPORTED)
    MESSAGE(FATAL_ERROR "Cette plateforme n'est actuellement pas prise en charge")

ENDIF()

# Compilation mode
IF(${CMAKE_BUILD_TYPE} MATCHES Debug)

    # Debug
    ADD_DEFINITIONS(-D AMBER_DEBUG)
    SET(AMBER_BIN_OUTPUT ${AMBER_BIN_DIR_DBG})
    SET(AMBER_LIB_OUTPUT ${AMBER_LIB_DIR_DBG})

    MESSAGE(STATUS "Compilation mode  : Debug")
    MESSAGE(STATUS "Project binary  output : ${AMBER_BIN_OUTPUT}")
    MESSAGE(STATUS "Project library output : ${AMBER_LIB_OUTPUT}")

    # Param�tres flags
    IF(COMPILER_GCC)
        # GCC
        set(CMAKE_CXX_FLAGS_DEBUG ${CXX_DEBUG_FLAGS} CACHE STRING "DBG" FORCE)
    ENDIF()
ELSEIF(${CMAKE_BUILD_TYPE} MATCHES Release)

    # Release mode
    ADD_DEFINITIONS(-D AMBER_RELEASE)
    SET(AMBER_BIN_OUTPUT ${AMBER_BIN_DIR_REL})
    SET(AMBER_LIB_OUTPUT ${AMBER_LIB_DIR_REL})

    MESSAGE(STATUS "Compilation mode  : Release")
    MESSAGE(STATUS "Project binary  output : ${AMBER_BIN_OUTPUT}")
    MESSAGE(STATUS "Project library output : ${AMBER_LIB_OUTPUT}")

    # Param�tres flags
    IF(COMPILER_GCC)
        # GCC
        set(CMAKE_CXX_FLAGS_DEBUG ${CXX_RELEASE_FLAGS} CACHE STRING "REL" FORCE)
    ENDIF()
ELSE()

    # No mode
    MESSAGE(FATAL_ERROR "Pas de mode de compilation exemple debug ou release.")

ENDIF()

#ls -1 sources/*.cpp
INCLUDE_DIRECTORIES(${CMAKE_DLL_OUTPUT_DIRECTORY}/Header)
INCLUDE_DIRECTORIES(${CMAKE_DLL_OUTPUT_DIRECTORY}/Scene/Header)
INCLUDE_DIRECTORIES(${CMAKE_DLL_OUTPUT_DIRECTORY}/Script/Header)
INCLUDE_DIRECTORIES(${AMBER_SOURCE}/Header/Struct)
INCLUDE_DIRECTORIES(${AMBER_SOURCE}/Header/InterfaceDll)


FILE(GLOB_RECURSE DLL_SOURCES *.cpp *.c)
FILE(GLOB_RECURSE DLL_HEADERS *.hpp *.h *.inl)
FILE(GLOB_RECURSE STRUCT_HEADERS ${AMBER_SOURCE}/Header/Struct/*.hpp)

IF(WIN32)
ADD_LIBRARY(AMBERDLL SHARED ${DLL_SOURCES} ${DLL_HEADERS} ${STRUCT_HEADERS} AMBERDLL_Debug.def)
ELSEIF(UNIX)
ADD_LIBRARY(AMBERDLL SHARED ${DLL_SOURCES} ${DLL_HEADERS} ${STRUCT_HEADERS})
ELSE()
    #Non supporte
    MESSAGE(FATAL_ERROR "Cette plateforme n'est actuellement pas prise en charge")
ENDIF()
