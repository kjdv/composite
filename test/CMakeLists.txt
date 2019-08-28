file(GLOB sources *.c *.cc *.cpp *.h *.hh)

add_executable(composite_test ${sources})
target_link_libraries(composite_test composite ${GMOCK_LIBRARIES} GTest::GTest GTest::Main)

gtest_discover_tests(composite_test)
