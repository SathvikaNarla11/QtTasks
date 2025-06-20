# set(PROJECT_SOURCES
#         main.cpp
#         mainwindow.cpp
#         mainwindow.h
#         mainwindow.ui
# )

# qt_add_executable(CarDashboard
#     MANUAL_FINALIZATION
#     ${PROJECT_SOURCES}
# )

# target_link_libraries(CarDashboard
#     PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
#     DashboardServices
# )

# qt_finalize_executable(CarDashboard)















# add_library(DashboardUI STATIC
#     DashboardUI.cpp
#     DashboardUI.h
# )

# target_include_directories(DashboardUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# set(PROJECT_SOURCES
#     DashboardUI.cpp
#     DashboardUI.h
# )

# add_library(DashboardUI STATIC
#     ${PROJECT_SOURCES}
# )

# target_include_directories(DashboardUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(DashboardUI PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
