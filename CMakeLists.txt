cmake_minimum_required(VERSION 2.8)
project( display_image )
find_package( OpenCV REQUIRED )

add_executable( display_image display_image.cpp )
target_link_libraries( display_image ${OpenCV_LIBS} )

add_executable( display_image_01 display_image_01.cpp )
target_link_libraries( display_image_01 ${OpenCV_LIBS} )

add_executable( modify_img_01 modify_img_01.cpp )
target_link_libraries( modify_img_01 ${OpenCV_LIBS} )

add_executable( mat_001 mat_001.cpp )
target_link_libraries( mat_001 ${OpenCV_LIBS} )
