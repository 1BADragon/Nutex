

function(nutex_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_link_libraries(${TEST_NAME} nutex)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

nutex_test(lock_test lock_test.cpp)
nutex_test(spinlock_test spinlock_test.cpp)
