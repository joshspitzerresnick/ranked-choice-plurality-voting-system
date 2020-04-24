cmake_minimum_required(VERSION 2.6)

set(Sources
    logger.cc
)

add_executable(runTests 
    ${Sources} 
    logger_UT.cc) 
    
target_link_libraries(runTests pthread)
