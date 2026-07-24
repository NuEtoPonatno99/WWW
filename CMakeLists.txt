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

# Подключаем папку с исходниками библиотек
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

# Создаем исполняемый файл и указываем зависимости
add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
    src/Debug/callback.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Renderer.h
    src/ManagerRes/ResourceManager.cpp
    src/ManagerRes/ResourceManager.h
    src/ManagerRes/stb_image.h
    src/Renderer/Texture2D.cpp
    src/Renderer/Texture2D.h
    src/Renderer/Sprite.cpp
    src/Renderer/Sprite.h
    )

# Подключаем заголовочные файлы GLM (так как это header-only библиотека)
target_include_directories(${PROJECT_NAME} PRIVATE external/glm)
# Стандарт плюсов
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Линкуем проект с библиотеками
target_link_libraries(${PROJECT_NAME} glfw glad)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Копирование ресурсов в папку с проектом
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)