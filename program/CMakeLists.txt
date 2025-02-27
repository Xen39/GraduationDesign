add_subdirectory(shape)

add_library(programLib Processor.cpp)

target_link_libraries(programLib ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets shapeLib)

target_include_directories(programLib PUBLIC .)