cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FlappyBird)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем путь к SFML
# Замените путь на тот, где вы распаковали SFML
set(SFML_DIR "external/SFML-2.6.1/lib/cmake/SFML")

# Подключаем SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Указываем исполняемый файл
add_executable(
    FlappyBird 
    src/main.cpp
    src/Resourses/ResourceManager.h
    src/Resourses/ResourceManager.cpp
    src/Resourses/Animation.h
    src/Resourses/Animation.cpp
    src/GameElements/Bird.h
    src/GameElements/Bird.cpp
    src/GameElements/Hitbox.h
    src/GameElements/Hitbox.cpp
    src/GameElements/Pipe.h
    src/GameElements/Pipe.cpp
    )

# Подключаем библиотеки SFML
target_link_libraries(FlappyBird sfml-graphics sfml-window sfml-system)

# Копирование DLL в папку с исполняемым файлом
if(WIN32)
    # Определяем путь к DLL
    set(SFML_BIN_DIR "external/SFML-2.6.1/bin")

    # Перечислите все необходимые DLL
    file(GLOB DLLS "${SFML_BIN_DIR}/*.dll")

    # Цикл для копирования DLL
    foreach(DLL ${DLLS})
        add_custom_command(TARGET FlappyBird POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL}"
            $<TARGET_FILE_DIR:FlappyBird>)
    endforeach()
endif()


# Помещаем /res в папку с исполняемым файлом
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)