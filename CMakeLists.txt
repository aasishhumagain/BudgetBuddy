cmake_minimum_required(VERSION 3.16)

project(BudgetBuddy_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Required Qt modules ----
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Charts)

# ---- Source files ----
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
)

# ---- Executable ----
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BudgetBuddy_2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(BudgetBuddy_2 ${PROJECT_SOURCES})
endif()

# ---- Link libraries ----
target_link_libraries(BudgetBuddy_2
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Charts   # ✅ Charts for PieChart
)

# ---- macOS/iOS bundle settings ----
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BudgetBuddy_2)
endif()

set_target_properties(BudgetBuddy_2 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ---- Installation paths ----
include(GNUInstallDirs)
install(TARGETS BudgetBuddy_2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ---- Qt6 specific finalization ----
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BudgetBuddy_2)
endif()
