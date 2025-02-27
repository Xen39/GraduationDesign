file(GLOB SOURCES "./*.cpp")

add_library(uiLib ${SOURCES})

target_link_libraries(uiLib ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets programLib)

target_include_directories(uiLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})