add_library(composite
    composite.hh
    composite.cc
)
target_include_directories(composite
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
