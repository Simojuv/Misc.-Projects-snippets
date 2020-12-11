file(GLOB_RECURSE SRC_LIST *.cpp *.h)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_options(${PROJECT_NAME} 
    PRIVATE 
        -Wall -Wextra -pedantic -Wconversion
        -Wsign-conversion -Wshadow=local -fconcepts)
