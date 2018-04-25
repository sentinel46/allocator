cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(allocator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    main.cpp
    newdelete.cpp)

set(HEADERS
    allocator.h
    newdelete.h)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT altdaedroth@gmail.com)

include(CPack)
