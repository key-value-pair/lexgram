include_directories(../lexgram)

add_executable(test_RegExp1 test_RegExp1.cpp)
target_link_libraries(test_RegExp1 lexgram_lib)
add_test(NAME test_RegExp1 COMMAND ./test_RegExp1)

add_executable(test_RegExp2 test_RegExp2.cpp)
target_link_libraries(test_RegExp2 lexgram_lib)
add_test(NAME test_RegExp2 COMMAND ./test_RegExp2)
