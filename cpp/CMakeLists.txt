cmake_minimum_required(VERSION 3.10)
project(TechTest)

# Default to C++17, but candidates may change to 20 or 23 if preferred
set(CMAKE_CXX_STANDARD 17)

# Export compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)

if (ENABLE_SANITIZERS)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-fno-omit-frame-pointer -g)
        add_link_options(-fno-omit-frame-pointer)

        add_compile_options(-fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    else()
        message(WARNING "Sanitizers not supported for this compiler.")
    endif()
endif()

# Models library
# Make Models a static library so translation-unit implementations
# (e.g. ScalarResults.cpp) are compiled and linked.
add_library(Models STATIC
    Models/ScalarResults.cpp
)

target_include_directories(Models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Loaders library
add_library(Loaders
    Loaders/ITradeLoader.h
    Loaders/BondTradeLoader.h
    Loaders/BondTradeLoader.cpp
    Loaders/FxTradeLoader.h
    Loaders/FxTradeLoader.cpp
)

target_include_directories(Loaders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Loaders Models)

# Pricers library
add_library(Pricers
    Pricers/BasePricingEngine.h
    Pricers/BasePricingEngine.cpp
    Pricers/GovBondPricingEngine.h
    Pricers/CorpBondPricingEngine.h
    Pricers/FxPricingEngine.h
)

target_include_directories(Pricers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Pricers Models)

# RiskSystem library
add_library(RiskSystem
    RiskSystem/PricingEngineConfigItem.h
    RiskSystem/PricingEngineConfig.h
    RiskSystem/PricingConfigLoader.h
    RiskSystem/PricingConfigLoader.cpp
    RiskSystem/SerialPricer.h
    RiskSystem/SerialPricer.cpp
    RiskSystem/SerialTradeLoader.h
    RiskSystem/SerialTradeLoader.cpp
    RiskSystem/StreamingTradeLoader.h
    RiskSystem/StreamingTradeLoader.cpp
    RiskSystem/ParallelPricer.h
    RiskSystem/ParallelPricer.cpp
    RiskSystem/ScreenResultPrinter.h
    RiskSystem/ScreenResultPrinter.cpp
)

target_include_directories(RiskSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RiskSystem Models Loaders Pricers)

# Find and link threading library (required for Exercise 8)
find_package(Threads REQUIRED)
target_link_libraries(RiskSystem Threads::Threads)

# ConsoleApp executable
add_executable(ConsoleApp
    ConsoleApp/main.cpp
)

target_link_libraries(ConsoleApp Models Loaders Pricers RiskSystem)

# Tests executable
# Note: Test .cpp files are included in main.cpp, so they shouldn't be listed here
add_executable(Tests
    Tests/TestFramework.h
    Tests/main.cpp
)

target_link_libraries(Tests Models Loaders Pricers RiskSystem)

# Copy data files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/Loaders/TradeData DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Loaders/TradeData DESTINATION ${CMAKE_BINARY_DIR}/Loaders)
file(COPY ${CMAKE_SOURCE_DIR}/RiskSystem/PricingConfig DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/RiskSystem/PricingConfig DESTINATION ${CMAKE_BINARY_DIR}/RiskSystem)

