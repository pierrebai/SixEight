# Qt 5 stuff

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS WinExtras REQUIRED)

add_executable(six_eight_solver_app WIN32
   src/six_eight_solver_app.cpp
   src/main_window.cpp                  include/main_window.h

   resources/resource.rc                resources/resource.h

   "${PROJECT_SOURCE_DIR}/LICENSE"
   "${PROJECT_SOURCE_DIR}/README.md"
)

set_target_properties(six_eight_solver_app PROPERTIES OUTPUT_NAME "SixEight Solver")

target_link_libraries(six_eight_solver_app PUBLIC
   six_eight
   dak_utility
   QtAdditions
   Qt5::Widgets Qt5::Gui Qt5::Core Qt5::WinExtras
)

target_compile_features(six_eight_solver_app PUBLIC
   cxx_std_20
)

target_include_directories(six_eight_solver_app PUBLIC
   include
   resources
)

add_custom_command(TARGET six_eight_solver_app POST_BUILD
   COMMAND "${Qt5_DIR}/../../../bin/windeployqt.exe" --no-webkit2 --no-angle --no-system-d3d-compiler --no-opengl-sw "$<TARGET_FILE:six_eight_solver_app>"
)

install(
   DIRECTORY
   "$<TARGET_FILE_DIR:six_eight_solver_app>/"
   DESTINATION .
   COMPONENT application
   PATTERN "*.pdb" EXCLUDE 
   PATTERN "*.ilk" EXCLUDE 
)

install(
   DIRECTORY
   "${PROJECT_SOURCE_DIR}/six_eight_solver/puzzles"
   DESTINATION .
   COMPONENT application
)

set(CPACK_GENERATOR NSIS)
set(CPACK_PACKAGE_NAME "SixEightSolver")
set(CPACK_PACKAGE_VENDOR "Pierre Baillargeon")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SixEight Solver - An application to solve SixEight(tm) puzzles.")
set(CPACK_PACKAGE_VERSION "1.2.4")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "4")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "SixEight Solver")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

set(CPACK_NSIS_MUI_ICON "${PROJECT_SOURCE_DIR}/six_eight_solver_app/resources/icon.ico")
set(CPACK_NSIS_MUI_UNIICON "${PROJECT_SOURCE_DIR}/six_eight_solver_app/resources/icon.ico")
set(CPACK_NSIS_INSTALLED_ICON_NAME "SixEight Solver.exe")
set(CPACK_NSIS_DISPLAY_NAME "SixEight Solver")
set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\SixEight Solver.lnk' '$INSTDIR\\\\SixEight Solver.exe'"
)
set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$START_MENU\\\\SixEight Solver.lnk'"
)
INCLUDE(CPack)

