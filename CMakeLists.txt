# ==============================================================================
# Project to test CMake BundleUtilities
# ------------------------------------------------------------------------------
SET(PROJECT_NAME Ray)
PROJECT (${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)

# ==============================================================================
# Use c++11
# ------------------------------------------------------------------------------
SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

# ==============================================================================
# Add our cmake module dir to the module path
# ------------------------------------------------------------------------------
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# ==============================================================================
# Source files
# ------------------------------------------------------------------------------
INCLUDE(${PROJECT_NAME})

# ==============================================================================
# Create executable
# ------------------------------------------------------------------------------
ADD_EXECUTABLE( ${PROJECT_NAME} MACOSX_BUNDLE WIN32
  ${RAY_SRCS} # TODO : Make this generic
)

# ==============================================================================
# Copy resources to where they need to be
# ------------------------------------------------------------------------------
IF (APPLE)
  SET(RESOURCE_LOCATION $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources)
ELSE (APPLE)
  SET(RESOURCE_LOCATION $<TARGET_FILE_DIR:${PROJECT_NAME}>)
ENDIF(APPLE)
ADD_CUSTOM_COMMAND(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${PROJECT_SOURCE_DIR}/Data ${RESOURCE_LOCATION}
)

# ==============================================================================
# Link target specific way of finding resource path
# ------------------------------------------------------------------------------
IF (WIN32)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} Shlwapi.lib)
ENDIF(WIN32)
IF (APPLE)
  FIND_LIBRARY(FOUNDATION_FRAMEWORK Foundation)
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${FOUNDATION_FRAMEWORK})
ENDIF(APPLE)

# ==============================================================================
# Find and link SFML
# ------------------------------------------------------------------------------
IF (WIN32)
  FIND_PACKAGE(SFML 2.3 COMPONENTS system window graphics network audio main)
ELSE (WIN32)
  FIND_PACKAGE(SFML 2.3 COMPONENTS system window graphics network audio)
ENDIF(WIN32)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SFML_LIBRARIES})

# ==============================================================================
# Find and link TimGameLib
# ------------------------------------------------------------------------------
SET(TIM_GAME_LIB_ROOT "$ENV{TIM_GAME_LIB_ROOT}")
IF (NOT TIM_GAME_LIB_ROOT)
  MESSAGE(FATAL_ERROR "TIM_GAME_LIB_ROOT not defined")
ENDIF()
LIST(APPEND CMAKE_MODULE_PATH "${TIM_GAME_LIB_ROOT}/cmake")
INCLUDE(TimGameLib)
INCLUDE_DIRECTORIES(${TIM_GAME_LIB_ROOT}/Source)
ADD_LIBRARY(TimGameLib ${TIM_GAME_LIB_SOURCES})
ADD_DEPENDENCIES(${PROJECT_NAME} TimGameLib)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} TimGameLib)

# ==============================================================================
# Use cotire for precompiled headers
# ------------------------------------------------------------------------------
INCLUDE(cotire)
SET_TARGET_PROPERTIES(
  ${PROJECT_NAME} 
  PROPERTIES 
  COTIRE_CXX_PREFIX_HEADER_INIT 
  "Source/${PROJECT_NAME}-Prefix.pch"
)
COTIRE(${PROJECT_NAME})
SET_TARGET_PROPERTIES(
  TimGameLib 
  PROPERTIES 
  COTIRE_CXX_PREFIX_HEADER_INIT 
  "${TIM_GAME_LIB_ROOT}/Source/TimGameLib_Prefix.pch"
)
COTIRE(TimGameLib)

# ==============================================================================
# HACK
# Copy the sfml frameworks/dlls into the app after the build
# Theoretically BundleUtilities should be able to take care of this but no 
# amount of trying different configurations could get it to work
# ------------------------------------------------------------------------------
GET_FILENAME_COMPONENT(SFML_LOCATION ${SFML_INCLUDE_DIR} DIRECTORY)
IF(APPLE)
  FILE(GLOB SFML_FRAMEWORKS ${SFML_LOCATION}/sfml-*.framework)
  # Add framweworks sfml depends on
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/freetype.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/FLAC.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/ogg.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/vorbis.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/vorbisenc.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/vorbisfile.framework)
  LIST(APPEND SFML_FRAMEWORKS ${SFML_LOCATION}/OpenAL.framework)
  SET(FRAMEWORK_APP_DIR $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Frameworks)

  FOREACH(SFML_FRAMEWORK ${SFML_FRAMEWORKS})
    GET_FILENAME_COMPONENT(SFML_FRAMEWORK_NAME ${SFML_FRAMEWORK} NAME)
    ADD_CUSTOM_COMMAND(
      TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E
        copy_directory ${SFML_FRAMEWORK} ${FRAMEWORK_APP_DIR}/${SFML_FRAMEWORK_NAME}
    )
  ENDFOREACH(SFML_FRAMEWORK)

  # And set the rpath to inside the app so we can load them
  SET_TARGET_PROPERTIES(
    ${PROJECT_NAME} 
    PROPERTIES 
    XCODE_ATTRIBUTE_LD_RUNPATH_SEARCH_PATHS
    @loader_path/../Frameworks
  )
ENDIF(APPLE)
IF (WIN32)
  SET(SFML_DLL_LOCATION ${SFML_LOCATION}/bin)
  ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${SFML_DLL_LOCATION} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
ENDIF(WIN32)