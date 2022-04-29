MESSAGE(STATUS "在模块one") 
add_library(one SHARED async_job.cpp)# 生成动态库(.so)  使用指定的文件列表
target_link_libraries(one pthread) #相当于g++  -l

add_library(one_static STATIC async_job.cpp)
target_link_libraries(one_static pthread)
set_target_properties(one_static PROPERTIES OUTPUT_NAME "one")#设置多个属性 


 


