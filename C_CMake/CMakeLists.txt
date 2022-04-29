cmake_minimum_required( VERSION 3.0 )

project( IKE )

set(SRC mylib.cpp) #设置变量

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_BUILD_TYPE Debug) 
message(STATUS "生成--开头的INFO级信息显示变量SRC=${SRC}") 
include_directories(${C_MAKE_SOURCE_DIR}/include) 
#add_executable(main src/main.cpp src/mylib.cpp) #生成可执行文件
#install(FILES src/README.rd DESTINATION /tmp/)
#----以上示例１

add_subdirectory(src/one_module one_output) #引用子目录有CMakeLists.txt 文件,可选的增加第二个参数输入目录,会自动创建
add_executable(main src/main.cpp src/mylib.cpp) #生成可执行文件
link_directories(one_output) #相当于g++  -L
target_link_libraries(main one) #相当于g++  -l
message(STATUS "变量CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}") 

#install(FILES ${CMAKE_BINARY_DIR}/main ${CMAKE_BINARY_DIR}/one_output/libone.so 
#        DESTINATION /tmp/
#        PERMISSIONS OWNER_READ OWNER_EXECUTE
#        )
#---或者       
#这名也可写在子模块中,DESTINATION应该为相对目录在PREFIX下
install(TARGETS one_static one
        ARCHIVE DESTINATION ar
        LIBRARY DESTINATION lib
        PERMISSIONS OWNER_READ 
        )
install(TARGETS main PERMISSIONS OWNER_READ OWNER_EXECUTE )   


