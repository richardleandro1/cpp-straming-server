cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO")

include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Threads
find_package(Threads REQUIRED)

# Boost
find_package(Boost REQUIRED COMPONENTS system)

# SFML
find_package(SFML REQUIRED COMPONENTS system)

# Localizar pacotes FFmpeg
find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT libavformat REQUIRED)
pkg_check_modules(AVCODEC libavcodec REQUIRED)
pkg_check_modules(AVUTIL libavutil REQUIRED)
pkg_check_modules(SWSCALE libswscale REQUIRED)
pkg_check_modules(AVDEVICE libavdevice REQUIRED)

message(AVFORMAT "LIBRARY_OUTPUT_PATH: ${AVFORMAT_LIBRARIES}")

# Incluir diretórios de cabeçalhos do BOOST
include_directories(${Boost_INCLUDE_DIRS})

# Incluir diretórios de cabeçalhos do SFML
include_directories(${SFML_INCLUDE_DIR})

# Incluir diretórios de cabeçalhos do FFmpeg
include_directories(${AVFORMAT_INCLUDE_DIRS})
include_directories(${AVCODEC_INCLUDE_DIRS})
include_directories(${AVUTIL_INCLUDE_DIRS})
include_directories(${SWSCALE_INCLUDE_DIRS})

# Adicionar o executável do seu projeto
add_executable(Server main.cpp)

# Vincular bibliotecas do FFmpeg ao seu projeto
target_link_libraries(Server ${AVFORMAT_LIBRARIES})
target_link_libraries(Server ${AVCODEC_LIBRARIES})
target_link_libraries(Server ${AVUTIL_LIBRARIES})
target_link_libraries(Server ${SWSCALE_LIBRARIES})
target_link_libraries(Server ${AVDEVICE_LIBRARIES})

target_link_libraries(Server  sfml-window
    sfml-system
    sfml-network
    sfml-graphics
    sfml-audio
    Threads::Threads
    ${Boost_LIBRARIES}
    "/opt/homebrew/lib/libavcodec.dylib"
    "/opt/homebrew/lib/libavformat.dylib"
    "/opt/homebrew/lib/libavutil.dylib"
    "/opt/homebrew/lib/libswscale.dylib"
    )

enable_testing()
add_executable(testMyApp tests/test_main.cpp)
add_test(NAME MyTest COMMAND testMyApp)
