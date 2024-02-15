cmake_minimum_required(VERSION 3.13)

set(PACKAGE_NAME ATM)
set(PACKAGE_VERSION 0.0.1)

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest)

add_library(BANK
  src/bank_api.cpp
  src/account.cpp
)
target_include_directories(BANK PUBLIC
  include
)
add_library(ATM
  src/atm.cpp
)
target_include_directories(ATM PUBLIC
  include
)
target_link_libraries(ATM PUBLIC BANK)

add_executable(console_app executable/main.cpp)
target_link_libraries(console_app PRIVATE ATM)

if (GTest_FOUND)
  message(STATUS "Found GTest.")
  set(GTEST_INCLUDE_PATH ${GTEST_INSTALL_PATH}/include)
  set(GTEST_LIBS GTest::gtest)
  include_directories(${GTEST_INCLUDE_PATH})

  add_executable(all_test
    test/main.cpp
    test/bank_api.cpp
  )
  target_link_libraries(all_test
    BANK
    ${GTEST_LIBS}
  )
  add_test(all_test
    all_test
    --gtest_color=yes
  )
endif()