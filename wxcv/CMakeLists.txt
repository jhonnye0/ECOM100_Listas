cmake_minimum_required(VERSION 3.17)

include_directories("$ENV{OPENCV_DIR}/include" "$ENV{WX_WIDGETS_DIR}/include" "$ENV{WX_WIDGETS_DIR}/lib/gcc_dll/mswu")
link_directories("$ENV{OPENCV_DIR}/lib" "$ENV{WX_WIDGETS_DIR}/lib/gcc_dll")

project(wxcv)
add_executable(wxcv src/main.cpp src/wxCvResizeDialog.cpp)
target_link_libraries(wxcv -lopencv_core450 -lopencv_imgcodecs450 -lopencv_imgproc450 -lwxmsw31u_core -lwxbase31u)