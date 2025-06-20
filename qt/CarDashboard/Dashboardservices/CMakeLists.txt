add_library(DashboardServices STATIC
    DashboardServices.cpp
    DashboardServices.h
)

target_include_directories(DashboardServices PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(DashboardServices PUBLIC Qt${QT_VERSION_MAJOR}::Core)

