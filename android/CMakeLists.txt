project(ReactNativeGeolocationJsi)
cmake_minimum_required(VERSION 3.9.0)

set (PACKAGE_NAME "cpp")
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 11)

file(TO_CMAKE_PATH "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp" libPath)

include_directories(
  ../cpp
  "${NODE_MODULES_DIR}/react-native/React"
  "${NODE_MODULES_DIR}/react-native/React/Base"
  "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
)
add_library(geolocationjsi # Library name
  SHARED
  ${libPath}
  ../cpp/react-native-geolocation-jsi.cpp
  ../cpp/react-native-geolocation-jsi.h
  cpp-adapter.cpp
  )


# Configure C++ 17
set_target_properties(
        geolocationjsi PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON
)

# find_package(ReactAndroid REQUIRED CONFIG)

target_link_libraries(
  geolocationjsi
  android
  )
