cmake_minimum_required(VERSION 3.13)

# initialize pico-sdk from GIT
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
set(PICO_SDK_ROOT $ENV{HOME}/pico-sdk)
include(${PICO_SDK_ROOT}/external/pico_sdk_import.cmake)

project(RP2040_ILI9341_SI5351)
set(EXE ili9341_synthez)


# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(ili9341_synthez
    main.c
    ili9341.c
    ili9341.h
    ili9341_framebuffer.c
    ili9341_framebuffer.h
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${EXE} pico_stdlib hardware_spi)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${EXE})

