include_directories(../lexgram)
add_executable(test1 test1.cpp)
link_libraries(test1 lexgram_lib)
add_test(NAME test1 COMMAND ./test1)
