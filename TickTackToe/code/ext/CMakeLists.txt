cmake_minimum_required(VERSION 3.8)
include(ExternalProject)

ExternalProject_Add(clipp
GIT_REPOSITORY      https://github.com/muellan/clipp.git
GIT_TAG             v1.2.3
GIT_SHALLOW         true
CONFIGURE_COMMAND   ""
BUILD_COMMAND       ""
INSTALL_COMMAND     ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/include ${CMAKE_CURRENT_BINARY_DIR}/include)

ExternalProject_Add(json
GIT_REPOSITORY      https://github.com/nlohmann/json.git
GIT_TAG             v3.6.1
GIT_SHALLOW         true
CMAKE_ARGS          -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}
                    -DJSON_MultipleHeaders=ON
                    -DBUILD_TESTING=OFF)

add_custom_target(dependencies
    DEPENDS
        clipp
        json)
