add_library(composite
    access.hh
    composite.hh
    composite.cc
    deduce.hh
    make.hh
    traits.hh
    types.cc
    types.hh
)
target_include_directories(composite
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
