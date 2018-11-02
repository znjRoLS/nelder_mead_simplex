add_library(nelder_mead nelder_mead.cpp)

add_executable(main main.cpp)
target_link_libraries(main nelder_mead)