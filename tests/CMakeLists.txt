include_directories(../lexgram)

aux_source_directory(. TEST_SRCS)

add_executable(test_all ${TEST_SRCS})
