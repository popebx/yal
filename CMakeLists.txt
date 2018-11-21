cmake_minimum_required(VERSION 3.10)
project(yal)


option(BUILD_SHARED "Build ${PROJECT_NAME} as Shared Library or Static Library" ON)
option(BUILD_EXAMPLE "Build Examples" ON)
option(BUILD_TESTS "Build Tests" ON)

set(${PROJECT_NAME}_src include/yal/yal.hpp include/yal/yal_singleton.hpp include/yal/yal_c_iface.h include/yal/yal_export.h
                        src/yal.cpp         src/yal_singleton.cpp         src/yal_c_iface.cpp)
set(${PROJECT_NAME}_example_src_singleton example/yal_singleton.cpp)
set(${PROJECT_NAME}_example_src example/yal.cpp)
set(${PROJECT_NAME}_tests_src tests/yal.cpp)


if(BUILD_SHARED)
    add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_src})
else(BUILD_SHARED)
    add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_src})
endif(BUILD_SHARED)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)


if(WIN32)
    if(BUILD_SHARED)
        target_compile_definitions(${PROJECT_NAME} PRIVATE EXPORT_YAL)
    endif(BUILD_SHARED)
endif(WIN32)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 
        /w14242 /w14254 /w14263 /w14265 /w14287
        /we4289 /w14296 /w14311 /w14545 /w14546
        /w14547 /w14549 /w14555 /w14619 /w14640
        /w14826 /w14905 /w14906 /w14928 )
endif(MSVC)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_executable(${PROJECT_NAME}_tests ${${PROJECT_NAME}_tests_src})
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES CXX_STANDARD 17)
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} GTest::GTest GTest::Main)
endif(BUILD_TESTS)

if(BUILD_EXAMPLE)
    add_executable(example_${PROJECT_NAME}_singleton ${${PROJECT_NAME}_example_src_singleton})
    target_link_libraries(example_${PROJECT_NAME}_singleton PRIVATE ${PROJECT_NAME})
    set_target_properties(example_${PROJECT_NAME}_singleton PROPERTIES CXX_STANDARD 17)
    add_executable(example_${PROJECT_NAME} ${${PROJECT_NAME}_example_src})
    target_link_libraries(example_${PROJECT_NAME} PRIVATE ${PROJECT_NAME})
    set_target_properties(example_${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
endif(BUILD_EXAMPLE)