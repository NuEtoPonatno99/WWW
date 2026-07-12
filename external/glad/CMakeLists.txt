# Указываем современный диапазон версий
cmake_minimum_required(VERSION 3.13...4.4)

# Имя проекта библиотеки
project(glad)

# Создаем статическую библиотеку, указывая заголовочные файлы и исходный код
add_library(glad STATIC 
    include/glad/glad.h 
    src/glad.c
)

# Указываем путь к заголовочным файлам, чтобы другие файлы проекта их видели
target_include_directories(glad PUBLIC include/)