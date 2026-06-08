cmake_minimum_required(VERSION 3.22)

project(RedstarDesigner VERSION 0.1.0)

# Path to your local JUCE clone — adjust if yours differs
set(JUCE_DIR "C:/Users/harry/Dev/JUCE" CACHE PATH "Path to JUCE source")
add_subdirectory(${JUCE_DIR} JUCE)

juce_add_gui_app(RedstarDesigner
    PRODUCT_NAME "Redstar Designer"
    COMPANY_NAME "HarryMoss")

juce_generate_juce_header(RedstarDesigner)

target_sources(RedstarDesigner PRIVATE
    Source/Main.cpp
    Source/MainComponent.cpp
    Source/Domain/AmpState.cpp
    Source/UI/ParameterPanel.cpp
    Source/Domain/PresetLibrary.cpp
    Source/UI/PatchBrowser.cpp)

target_include_directories(RedstarDesigner PRIVATE Source)

target_compile_features(RedstarDesigner PRIVATE cxx_std_17)

target_link_libraries(RedstarDesigner PRIVATE
    juce::juce_gui_extra
    juce::juce_data_structures
    juce::juce_events
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags)

target_compile_definitions(RedstarDesigner PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)