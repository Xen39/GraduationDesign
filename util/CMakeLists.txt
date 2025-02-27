file(GLOB SOURCES "./*.cpp")

add_library(utilLib ${SOURCES})

target_link_libraries(utilLib ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(utilLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})