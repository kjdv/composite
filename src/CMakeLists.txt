set(HEADERS
    include/composite/access.hh
    include/composite/builder.hh
    include/composite/composite.hh
    include/composite/deduce.hh
    include/composite/make.hh
    include/composite/traits.hh
    include/composite/types.hh
    include/composite/visitor.hh)

add_library(composite
    ${HEADERS}
    builder.cc
    composite.cc
    types.cc
    visitor.cc
)
target_include_directories(composite
    PUBLIC BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(APPLE)
    target_compile_options(composite PUBLIC -mmacosx-version-min=10.14)
    target_link_libraries(composite PUBLIC -mmacosx-version-min=10.14)
endif()


# install rules
install(FILES ${HEADERS} DESTINATION include/composite)
install(TARGETS composite DESTINATION lib)
