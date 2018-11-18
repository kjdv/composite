add_library(composite
    access.hh
    builder.hh
    builder.cc
    composite.hh
    composite.cc
    deduce.hh
    make.hh
    traits.hh
    types.cc
    types.hh
    visitor.hh
    visitor.cc
)
target_include_directories(composite
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

if(APPLE)
    target_compile_options(composite PUBLIC -mmacosx-version-min=10.14)
    target_link_libraries(composite PUBLIC -mmacosx-version-min=10.14)
endif()
