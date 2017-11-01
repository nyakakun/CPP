# Минимальная версия CMake: 3.8
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Имя проекта: sfml-lab-2
project(sfml-lab-4)

# Подкаталог 00 содержит ещё один CMakeLists.txt
add_subdirectory(workshop1)
add_subdirectory(workshop2)
add_subdirectory(workshop3)
add_subdirectory(workshop4)