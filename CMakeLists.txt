# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(rlog CXX)

# Требуем C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# По умолчанию — более строгие предупреждения
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Указываем, где искать заголовочные файлы
include_directories(
    src
    src/common
    src/core
    src/interface
    src/io
    src/storage
    # Поддержка nlohmann/json без установки (если лежит в include/json/)
    include
)

# Список всех исходников
set(SOURCES
    src/main.cpp
    src/core/rlog_core.cpp
    src/storage/json_topic_storage.cpp
    # сюда можно добавить io/console_io.cpp, если будешь использовать
)

# Создаём исполняемый файл
add_executable(rlog ${SOURCES})

# Если используешь nlohmann/json как header-only (что вероятно)
# Положи json.hpp в: include/nlohmann/json.hpp
# Тогда ничего дополнительно линковать не нужно.

# Опционально: установка
install(TARGETS rlog DESTINATION bin)