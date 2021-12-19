# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("SAE921-GRP4100-Box2D")
message("SOLUTION/PROJECT CMAKING " ${CMAKE_PROJECT_NAME})

set(EXECUTABLE_CUSTOM_NAME "MoonMace")
add_subdirectory ("MoonMace")
