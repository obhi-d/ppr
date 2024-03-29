cmake_minimum_required(VERSION 3.1)

project(ppr VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

option(PPR_BUILD_TESTS               "Build the unit tests when BUILD_TESTING is enabled." ON)
option(PPR_USE_LIBCPP_CLANG          "Use libc++ for clang"                                ON)
option(PPR_USE_PRE_GENERATED_PARSERS "Use already generated parsers"                       ON)
set   (PPR_BISON                     "bison"                                               CACHE STRING "Bison execuatable")
set   (PPR_FLEX                      "flex"                                                CACHE STRING "Flex executable"  )

##
## CONFIGURATION
##
set(PPR_TARGET_NAME       ${PROJECT_NAME})
set(PPR_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include")
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

if (PPR_USE_PRE_GENERATED_PARSERS)

add_custom_command( 
	OUTPUT 
		"${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" 
    "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" 

   COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/detail"
	 COMMAND ${CMAKE_COMMAND} -E copy  "${PROJECT_SOURCE_DIR}/gen/ppr_eval.cxx" "${PROJECT_SOURCE_DIR}/gen/ppr_eval.hxx" "${PROJECT_SOURCE_DIR}/gen/ppr_tokenizer.cxx" "${CMAKE_CURRENT_BINARY_DIR}/detail"
	 DEPENDS 
		"${PROJECT_SOURCE_DIR}/include/detail/ppr_eval.yy"
 )

else(PPR_USE_PRE_GENERATED_PARSERS)

add_custom_command( 
	OUTPUT 
		"${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" 
   COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/detail"
	 COMMAND ${PPR_BISON} -o "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" --no-lines "${PROJECT_SOURCE_DIR}/include/detail/ppr_eval.yy"
   COMMAND ${CMAKE_COMMAND} -E copy  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.hxx" "${PROJECT_SOURCE_DIR}/gen"
	 DEPENDS 
		"${PROJECT_SOURCE_DIR}/include/detail/ppr_eval.yy"
 )

add_custom_command( 
	OUTPUT 
	"${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" 
   COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/detail"
	 COMMAND ${PPR_FLEX} -o "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" -L "${PROJECT_SOURCE_DIR}/include/detail/ppr_tokenizer.l"
   COMMAND ${CMAKE_COMMAND} -E copy  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" "${PROJECT_SOURCE_DIR}/gen"
	 DEPENDS 
		"${PROJECT_SOURCE_DIR}/include/detail/ppr_tokenizer.l"
    )

endif(PPR_USE_PRE_GENERATED_PARSERS)

add_custom_target(
  ${PPR_TARGET_NAME}.PreBuild DEPENDS
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" 
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" 
)
##
## TARGET
##
message("Target name: ${PPR_TARGET_NAME}")

add_library(${PPR_TARGET_NAME} STATIC 
  "src/ppr_sink.cxx"
  "src/ppr_tokenizer.cxx"
  "src/ppr_transform.cxx"
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx" 
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" 
  )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if (PPR_USE_LIBCPP_CLANG)
    target_compile_options(${PPR_TARGET_NAME} PUBLIC "-stdlib=libc++")
    target_link_options(${PPR_TARGET_NAME} PUBLIC "-stdlib=libc++")
  endif(PPR_USE_LIBCPP_CLANG)
endif()

add_dependencies(${PPR_TARGET_NAME} ${PPR_TARGET_NAME}.PreBuild)
add_library(${PROJECT_NAME}::${PPR_TARGET_NAME} ALIAS ${PPR_TARGET_NAME})
target_include_directories(
    ${PPR_TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${${PROJECT_NAME}_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

##
## TESTS
##
include(CTest) #adds option BUILD_TESTING (default ON)

if(BUILD_TESTING AND PPR_BUILD_TESTS)

  enable_testing()
  add_executable(
    unit_test
    ${PROJECT_SOURCE_DIR}/unit_tests/test.cpp
  )

  file(GLOB DATA_FILES ${PROJECT_SOURCE_DIR}/unit_tests/datasets/*.txt)

  add_custom_command( 
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/datasets/test.h
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/references/test.h
    DEPENDS ${CMAKE_SOURCE_DIR}/unit_tests/datasets/test.h
    DEPENDS ${CMAKE_SOURCE_DIR}/unit_tests/references/test.h
	   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/unit_tests/datasets/test.h ${CMAKE_CURRENT_BINARY_DIR}/datasets
     COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/unit_tests/references/test.h ${CMAKE_CURRENT_BINARY_DIR}/references
  )

  add_custom_target(
    unit_test_data
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/datasets/test.h
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/references/test.h
  )

  add_dependencies(unit_test unit_test_data)
  target_link_libraries(unit_test PRIVATE ${PPR_TARGET_NAME})
endif()

# Utility
add_executable(
  tokenizer_util
  ${PROJECT_SOURCE_DIR}/utility/tokenizer_util.cpp
)
target_link_libraries(tokenizer_util PRIVATE ${PPR_TARGET_NAME})

add_executable(
  preprocess
  ${PROJECT_SOURCE_DIR}/utility/transform_util.cpp
)
target_link_libraries(preprocess PRIVATE ${PPR_TARGET_NAME})

# INSTALL

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION lib
       )

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION
      cmake)


install(EXPORT ${PROJECT_NAME}_Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
              DESTINATION cmake)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
install(FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_tokenizer.cxx" 
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.hxx"
  "${CMAKE_CURRENT_BINARY_DIR}/detail/ppr_eval.cxx"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/detail)

