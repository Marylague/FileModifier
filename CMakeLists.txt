cmake_minimum_required(VERSION 3.19)
project(FileModifier LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Test)

qt_standard_project_setup()

qt_add_executable(FileModifier
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    fileprocessor.cpp
    fileprocessor.h
    mainwindow.ui


)

target_link_libraries(FileModifier
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS FileModifier
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET FileModifier
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

if(QT_BUILD_TESTS)

    qt_add_executable(unit_tests
        test_fileprocessor.cpp
    )

    target_link_libraries(unit_tests
        PRIVATE
            Qt::Core
            Qt::Test
    )
    target_sources(unit_tests
        PRIVATE
            fileprocessor.cpp
    )

    qt_add_test(unit_tests unit_tests)
endif()
add_subdirectory(FileModifierTestProject)
