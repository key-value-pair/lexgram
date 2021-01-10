include_directories(../lexgram)
include_directories(tools)

aux_source_directory(. TEST_SRCS)

add_library(test_tool SHARED tools/test_tool.cpp)

add_executable(test_all ${TEST_SRCS})
target_link_libraries(test_all lexgram_lib)
target_link_libraries(test_all test_tool)
