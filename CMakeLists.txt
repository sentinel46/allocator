cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")

set(VER 0.0.1)
if($ENV{TRAVIS_BUILD_NUMBER})
    set(VER 0.0.$ENV{TRAVIS_BUILD_NUMBER})
endif()
project(allocator VERSION ${VER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
    main.cpp)

set(HEADERS
    allocator.h
    factorial.h
    linkedlist.h)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})

add_executable(test_${PROJECT_NAME}
    ${HEADERS}
    newdelete.h
    newdelete.cpp
    test_${PROJECT_NAME}.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)


set_target_properties(test_${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
#add_compile_options(-Wall -Wextra)


install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT altdaedroth@gmail.com)

include(CPack)

enable_testing()

add_test(test_${PROJECT_NAME} test_${PROJECT_NAME})
