enable_testing()

find_package(GTest QUIET)

if (GTEST_FOUND)

    add_executable(run-unittests
                   GladiatorTest.cpp
                   ProjectileTest.cpp
                   WorldTest.cpp
                   ExplosionTest.cpp)

    target_link_libraries(run-unittests
                          sim GTest::GTest GTest::Main)

    add_test(UnitTests run-unittests)

endif (GTEST_FOUND)
