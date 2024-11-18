# Minimum CMake version required for ESP-IDF
cmake_minimum_required(VERSION 3.16)

# Retrieve the current target platform (e.g., ESP32)
idf_build_get_property(target IDF_TARGET)

# Special configuration for Linux target
if(${target} STREQUAL "linux")
    # Register a header-only library for Linux builds
    idf_component_register(
        INCLUDE_DIRS include
        SRCS protocol_examples_utils.c
    )
    return()
endif()

# Set source files for the component
set(srcs 
    "stdin_out.c"
    "addr_from_stdin.c"
    "connect.c"
    "wifi_connect.c"
    "protocol_examples_utils.c"
    "main.c"
)

# Add additional source files based on configuration options
if(CONFIG_EXAMPLE_PROVIDE_WIFI_CONSOLE_CMD)
    list(APPEND srcs "console_cmd.c")
endif()

if(CONFIG_EXAMPLE_CONNECT_ETHERNET)
    list(APPEND srcs "eth_connect.c")
endif()

if(CONFIG_EXAMPLE_CONNECT_PPP)
    list(APPEND srcs "ppp_connect.c")
endif()

# Register the component with its dependencies
idf_component_register(
    SRCS "${srcs}"
    INCLUDE_DIRS "include"
    PRIV_REQUIRES esp_netif driver esp_wifi vfs console esp_eth nvs_flash esp_http_client 
)

# Conditionally include optional dependencies
if(CONFIG_EXAMPLE_PROVIDE_WIFI_CONSOLE_CMD)
    idf_component_optional_requires(PRIVATE console)
endif()

if(CONFIG_EXAMPLE_CONNECT_ETHERNET)
    idf_component_optional_requires(PUBLIC esp_eth)
endif()

if(CONFIG_EXAMPLE_CONNECT_PPP)
    idf_component_optional_requires(PRIVATE esp_tinyusb espressif__esp_tinyusb)
endif()
