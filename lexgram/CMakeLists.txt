include_directories(.)
aux_source_directory(. LEXGRAM_SRCS)
add_library(lexgram_lib ${LEXGRAM_SRCS})
