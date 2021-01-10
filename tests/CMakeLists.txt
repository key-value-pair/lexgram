include_directories(../lexgram)

add_executable(test1 test1.cpp)
link_libraries(test1 lexgram_lib)
add_test(NAME test1 COMMAND ./test1)

add_executable(test_RegExp1 test_RegExp1.cpp)
link_libraries(test_RegExp1 lexgram_lib)
add_test(NAME test_RegExp1 COMMAND ./test_RegExp1)
