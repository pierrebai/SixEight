cmake_minimum_required(VERSION 3.7.0)

# The dak/six-eight library, solver and its tests.

project(six_eight)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

add_subdirectory(six_eight)
add_subdirectory(dak/utility)
add_subdirectory(QtAdditions)
add_subdirectory(six_eight_solver)
add_subdirectory(six_eight_solver_app)
add_subdirectory(six_eight_tests)

