cmake_minimum_required (VERSION 3.9)
project (Fritz)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(OpenCV_DIR "/home/me/libs/opencv/release/share/OpenCV")

find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)

include_directories(/home/me/libs/cfitsio/include /home/me/libs/cfitsio/lib ${OpenCV_INCLUDE_DIRS})
link_directories(/usr/local/lib /home/me/libs/cfitsio/lib /home/me/libs/)

add_executable(fritz ./src/fritzio.cc)

target_link_libraries(fritz cfitsio ${OpenCV_LIBS})
