
enable_testing()
find_package(GTest REQUIRED)
add_executable(test1 test.cpp)
target_include_directories(test1 PUBLIC ${DEPEN_DIR})
target_link_libraries(test1 GTest::GTest GTest::Main SORUCE_LIB)
add_test(test-1 test1)

