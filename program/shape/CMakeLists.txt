add_library(shapeLib
        Arc.cpp Circle.cpp ConnectedPolyline.cpp ContourCurve.cpp InfiniteLine.cpp LineSegment.cpp Parallelogram.cpp
        Polyline.cpp Rectangle.cpp Shape.cpp ShapeContainer.cpp ShapeFactory.cpp ShapeType.cpp)

target_link_libraries(shapeLib ${OpenCV_LIBS} Qt${QT_VERSION_MAJOR}::Widgets utilLib)

target_include_directories(shapeLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})