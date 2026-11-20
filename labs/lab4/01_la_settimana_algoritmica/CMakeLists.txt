cmake_minimum_required(VERSION 3.20)

project(la_settimana_algoritmica C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
list(REMOVE_ITEM MODULE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

file(GLOB FRAMEWORK_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/framework/*.c"
)

add_library(aads_console STATIC
    framework/aads_console/aads_console.c
    framework/aads_console/aads_console_platform.c
)
target_include_directories(aads_console PUBLIC framework/aads_console)

add_library(magazine_modules ${MODULE_SOURCES} ${FRAMEWORK_SOURCES})
target_include_directories(magazine_modules PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/framework"
)

target_link_libraries(magazine_modules PRIVATE aads_console)

add_executable(la_settimana_algoritmica src/main.c)
target_link_libraries(la_settimana_algoritmica PRIVATE magazine_modules)

enable_testing()

add_library(unity STATIC
    tests/unity/unity.c
)
target_include_directories(unity PUBLIC tests/unity)

add_executable(la_settimana_algoritmica_tests
    tests/test_settimana_algoritmica.c
    tests/support/allocation_tracker.c
)
target_include_directories(la_settimana_algoritmica_tests PRIVATE
    src
    tests
)
target_link_libraries(la_settimana_algoritmica_tests PRIVATE
    unity
    magazine_modules
)
target_link_options(la_settimana_algoritmica_tests PRIVATE
    -Wl,--wrap=malloc -Wl,--wrap=calloc -Wl,--wrap=realloc
    -Wl,--wrap=free -Wl,--wrap=strdup
)

add_test(
    NAME la_settimana_algoritmica_tests
    COMMAND la_settimana_algoritmica_tests
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

set(STAFF_TEST_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/staff/test_framework.c"
)

if(EXISTS "${STAFF_TEST_SOURCE}")
    add_executable(la_settimana_algoritmica_staff_tests "${STAFF_TEST_SOURCE}")
    target_include_directories(la_settimana_algoritmica_staff_tests PRIVATE
        src
        tests
    )
    target_link_libraries(la_settimana_algoritmica_staff_tests PRIVATE
        unity
        magazine_modules
    )

    add_test(
        NAME la_settimana_algoritmica_staff_tests
        COMMAND la_settimana_algoritmica_staff_tests
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )

    add_executable(la_settimana_algoritmica_console_tests
        tests/staff/test_console.c
        framework/aads_console/aads_console.c
    )
    target_include_directories(la_settimana_algoritmica_console_tests PRIVATE
        framework/aads_console
    )
    target_link_libraries(la_settimana_algoritmica_console_tests PRIVATE unity)

    add_test(
        NAME la_settimana_algoritmica_console_tests
        COMMAND la_settimana_algoritmica_console_tests
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    )
endif()
