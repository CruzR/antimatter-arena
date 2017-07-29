enable_testing()

find_package(GTest REQUIRED)

add_executable(run-unittests GladiatorTest.cpp)
target_link_libraries(run-unittests sim GTest::GTest GTest::Main)

add_test(UnitTests run-unittests)
