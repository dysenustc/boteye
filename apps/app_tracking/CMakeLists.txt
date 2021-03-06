cmake_minimum_required(VERSION 2.8.11)
# ============================================
#  Example tracking App
# ============================================
project(app_tracking)

# Check if we have Opencv_viz lib
list(FIND OpenCV_LIBS "opencv_viz" find_index)
if (find_index GREATER -1)
  message(STATUS "Found libopencv_viz")
  add_definitions(-DHAS_OPENCV_VIZ)
else()
  message(STATUS "Couldn't find libopencv_viz")
endif()
#add_definitions(-DSHOW_POSE_2D)

add_executable(${PROJECT_NAME}
 plotting_utils.h
 plotting_utils.cpp
 app_tracking.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${XP_INCLUDE_DIR}
 ${OpenCV_INCLUDE_DIRS}
 /usr/local/include
)
target_link_libraries(${PROJECT_NAME}
 ${GLOG_LIBRARY}
 ${GFLAGS_LIBRARY}
 ${XP_LIBRARY}
 ${OpenCV_LIBRARIES}
)

# Set recognition option
if(EnableRecognition)
  target_include_directories(${PROJECT_NAME} PUBLIC
    ${FREETYPE_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
  )
  target_link_libraries(${PROJECT_NAME}
    ${JSON_LIBRARY}
    ${FREETYPE_LIBRARY}
    ${CURL_LIBRARY}
    ${CRYPTO_LIBRARY}
)
endif()
# ============================================
# Example UDP pose receiver
# ============================================
add_executable(pose_receiver
 plotting_utils.h
 plotting_utils.cpp
 app_pose_receiver.cpp
)

target_include_directories(pose_receiver PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${XP_INCLUDE_DIR}  # for pose_packet.h
 ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(pose_receiver
 ${GLOG_LIBRARY}
 ${GFLAGS_LIBRARY}
 ${XP_LIBRARY}
 ${OpenCV_LIBRARIES}
)
# ============================================
# Example UDP guide message receiver
# ============================================
add_executable(guide_receiver
 app_guide_receiver.cpp
)

target_include_directories(guide_receiver PUBLIC
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${XP_INCLUDE_DIR}  # for pose_packet.h
 /usr/local/include
)
