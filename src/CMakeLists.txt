add_library(class1 class1.cpp)
add_library(class2 class2.cpp)

add_executable(binary1 binary1.cpp)
target_link_libraries(binary1 class1 class2)