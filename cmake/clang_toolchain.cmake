# Set the name of the toolchain
set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})

# Set the compiler to Clang
find_program(CLANG_EXECUTABLE NAMES clang)
find_program(CLANGXX_EXECUTABLE NAMES clang++)
if(CLANG_EXECUTABLE AND CLANGXX_EXECUTABLE)
    set(CMAKE_C_COMPILER ${CLANG_EXECUTABLE})
    set(CMAKE_CXX_COMPILER ${CLANGXX_EXECUTABLE})
else()
    message(FATAL_ERROR "Clang compiler not found.")
endif()

# Set the path to the compiler
set(CMAKE_FIND_ROOT_PATH /path/to/clang/installation)

# Set other compiler flags as needed
set(CMAKE_C_FLAGS 
    -Waddress
    -Waggregate-return
    -Wformat-nonliteral
    -Wformat-security
    -Wformat
    -Winit-self
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wno-multichar
    -Wno-parentheses
    -Wno-type-limits
    -Wno-unused-parameter
    -Wunreachable-code
    -Wwrite-strings
    -Wpointer-arith
    # -Werror
    -Wall
    -pedantic
    -Wall
    -Wfatal-errors
    -Wextra
    -Wno-unused-parameter
    -Wno-unused-variable
)


set(CMAKE_CXX_FLAGS 
    -Waddress
    -Waggregate-return
    -Wformat-nonliteral
    -Wformat-security
    -Wformat
    -Winit-self
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wno-multichar
    -Wno-parentheses
    -Wno-type-limits
    -Wno-unused-parameter
    -Wunreachable-code
    -Wwrite-strings
    -Wpointer-arith
    # -Werror
    -Wall
    -pedantic
    -Wall
    -Wfatal-errors
    -Wextra
    -Wno-unused-parameter
    -Wno-unused-variable
)
