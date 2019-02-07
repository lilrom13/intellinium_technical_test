cmake_minimum_required(VERSION 3.13.1)

FILE(GLOB MyCSources src/*.c)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(intellinium_technical_test)

target_sources(app PRIVATE ${MyCSources})
target_include_directories(app PRIVATE include)
