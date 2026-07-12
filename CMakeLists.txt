# Поддержка правил CMake 4.4
cmake_minimum_required(VERSION 3.13...4.4)

# Задаем имя проекта через переменную
set(PROJECT_NAME WW)
project(${PROJECT_NAME})

# Отключаем всё лишнее в GLFW перед его сборкой
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Подключаем папку с исходниками GLFW
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} src/main.cpp)

# Линкуем проект с библиотеками
target_link_libraries(${PROJECT_NAME} glfw glad)