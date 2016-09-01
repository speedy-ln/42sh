cmake_minimum_required(VERSION 3.4)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(42sh C)
FILE(GLOB MyCSources *.c libft/*.c)
set(SOURCE_FILES *.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ltermcap")
add_executable(42sh main.c ${MyCSources} libft/ft_first_occur.c test.c libft/ft_strarr_append.c libft/ft_words.c redirection_support.c)
target_link_libraries(42sh termcap)