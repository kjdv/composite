add_executable(composite_test
    access.cc
    composite.cc
    deduce.cc
    make.cc
    sample.hh
)
target_link_libraries(composite_test
    PRIVATE
      composite
      gtest
)
add_test(composite_test composite_test)
