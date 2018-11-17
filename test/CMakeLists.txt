add_executable(composite_test
    composite.cc
)
target_link_libraries(composite_test
    PRIVATE
      composite
      gtest
)
add_test(composite_test composite_test)
