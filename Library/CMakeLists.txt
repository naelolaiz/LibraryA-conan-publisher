cmake_minimum_required(VERSION 3.15)
project(Library CXX)

add_library(Library Library.cpp Library.h)

set_target_properties(Library PROPERTIES PUBLIC_HEADER "Library.h")
install(TARGETS Library DESTINATION "."
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
set_target_properties(Library PROPERTIES CXX_STANDARD 11)

set(CPACK_PACKAGE_NAME Library-${CMAKE_BUILD_TYPE})
include(CPack)


set(INCLUDE_INSTALL_DIR include/)
set(LIB_INSTALL_DIR lib/)
#set(SYSCONFIG_INSTALL_DIR etc/foo/ ... CACHE )
include(CMakePackageConfigHelpers)



file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/LibraryConfig.cmake.in
"set(FOO_VERSION 0.1)
@PACKAGE_INIT@
set_and_check(FOO_INCLUDE_DIR \"@PACKAGE_INCLUDE_INSTALL_DIR@\")
set_and_check(FOO_SYSCONFIG_DIR \"@PACKAGE_SYSCONFIG_INSTALL_DIR@\")
check_required_components(Foo)
)"
)

configure_package_config_file(${CMAKE_CURRENT_BINARY_DIR}/LibraryConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/LibraryConfig.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/Library/cmake)
	#  PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/LibraryConfigVersion.cmake
  VERSION 1.2.3
  COMPATIBILITY SameMajorVersion )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LibraryConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/LibraryConfigVersion.cmake
	      DESTINATION ${LIB_INSTALL_DIR}/Library/cmake )

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

#include(${CMAKE_BINARY_DIR}/conan.cmake)

#conan_cmake_configure(GENERATORS cmake_find_package)

#conan_cmake_autodetect(settings)

#conan_cmake_install(PATH_OR_REFERENCE .
#                    BUILD missing
#                    REMOTE conancenter
#                    SETTINGS ${settings})

