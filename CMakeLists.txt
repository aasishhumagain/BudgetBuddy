cmake_minimum_required(VERSION 3.16)

project(BudgetBuddy_2 VERSION 0.1 LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------- Find Required Qt Modules --------
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)

# -------- All Source Files --------
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    databasemanager.cpp databasemanager.h
    login.cpp login.h login.ui
    signup.cpp signup.h signup.ui
    homepage.cpp homepage.h homepage.ui
    transactions.cpp transactions.h transactions.ui
    monthlygoals.cpp monthlygoals.h monthlygoals.ui
    viewtransactions.cpp viewtransactions.h viewtransactions.ui
    analyzereport.cpp analyzereport.h analyzereport.ui
    forgotpassword.cpp forgotpassword.h

)

# -------- Add Executable --------
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BudgetBuddy_2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        forgotpassword.h forgotpassword.cpp
    )
else()
    add_executable(BudgetBuddy_2 ${PROJECT_SOURCES})
endif()

# -------- Link Required Qt Libraries --------
target_link_libraries(BudgetBuddy_2
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts
)

# -------- macOS/iOS Configuration (Optional) --------
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BudgetBuddy_2)
endif()

set_target_properties(BudgetBuddy_2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# -------- Installation --------
include(GNUInstallDirs)
install(TARGETS BudgetBuddy_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# -------- Finalize for Qt6 --------
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BudgetBuddy_2)
endif()
