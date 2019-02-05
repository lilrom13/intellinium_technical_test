cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(intellinium_technical_test)

target_sources(app PRIVATE src/main.c src/mpu6050_driver.c)
target_include_directories(app PRIVATE include)
