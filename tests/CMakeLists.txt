# Add a testing executable

add_executable(init init.c)
target_link_libraries(init ccursor)
add_test(NAME Initialization COMMAND init)

add_executable(num num.c)   
target_link_libraries(num ccursor)
add_test(NAME Numeric COMMAND num)

add_executable(types types.c)   
target_link_libraries(types ccursor)
add_test(NAME ExtraTypes COMMAND types)

add_executable(str str.c)   
target_link_libraries(str ccursor)
add_test(NAME StringTests COMMAND str)

add_executable(extn extn.c)   
target_link_libraries(extn ccursor)
add_test(NAME Extension COMMAND extn)

add_executable(error error.c)   
target_link_libraries(error ccursor)
add_test(NAME Error COMMAND error)