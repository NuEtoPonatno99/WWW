# Переписано на современный синтаксис с поддержкой правил CMake 4.4
cmake_minimum_required(VERSION 3.13...4.4)

# Задаем имя проекта через переменную, как в вашем гайде
set(PROJECT_NAME WW)
project(${PROJECT_NAME})

# Отключаем всё лишнее в GLFW перед его сборкой (все 4 опции автора)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Подключаем папку с исходниками GLFW
add_subdirectory(external/glfw)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} src/main.cpp)

# Линкуем проект с библиотекой GLFW
target_link_libraries(${PROJECT_NAME} glfw)