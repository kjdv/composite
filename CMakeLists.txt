cmake_minimum_required(VERSION 3.10)

project(composite)
set(CMAKE_CXX_STANDARD 17)

include(GoogleTest)
find_package(GTest MODULE REQUIRED)
find_library(GMOCK_LIBRARIES gmock)
enable_testing()


add_subdirectory(lib)
add_subdirectory(test)

# install rules
install(TARGETS composite
        EXPORT CompositeConfig
        ARCHIVE DESTINATION lib COMPONENT lib
        PUBLIC_HEADER DESTINATION include/composite COMPONENT dev
)

export(TARGETS composite NAMESPACE Composite:: FILE ${CMAKE_CURRENT_BINARY_DIR}/CompositeConfig.cmake)
install(EXPORT CompositeConfig DESTINATION share/composite NAMESPACE Composite::)
