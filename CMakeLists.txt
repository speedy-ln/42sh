cmake_minimum_required(VERSION 3.4)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used
project(42sh C)
FILE(GLOB MyCSources *.c libft/*.c)
set(SOURCE_FILES echo.c extras.c new.c func.c help.c)
add_executable(minishell main.c ${MyCSources})
