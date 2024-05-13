# Add a testing executable

add_executable(init init.c)
target_link_libraries(init ccurser)
add_test(NAME Initialization COMMAND init)

add_executable(num num.c)   
target_link_libraries(num ccurser)
add_test(NAME Numeric COMMAND num)

add_executable(types types.c)   
target_link_libraries(types ccurser)
add_test(NAME ExtraTypes COMMAND types)

add_executable(str str.c)   
target_link_libraries(str ccurser)
target_compile_options(str PRIVATE -g -O0)
add_test(NAME StringTests COMMAND str)

add_executable(extn extn.c)   
target_link_libraries(extn ccurser)
target_compile_options(extn PRIVATE -g -O0)
add_test(NAME Extension COMMAND extn)