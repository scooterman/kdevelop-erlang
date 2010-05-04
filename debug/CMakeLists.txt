add_definitions( -DKDE_DEFAULT_DEBUG_AREA=9046 )

enable_testing()
find_package(KDE4 REQUIRED)
find_package(KDevPlatform REQUIRED)

include_directories(
    ${KDEVPLATFORM_INCLUDE_DIR}
    ${KDE4_INCLUDES}
    ${QT4_INCLUDES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

########### next target ###############

set(kdeverldebugcore_PART_SRCS
    debugger.cpp
    debugsession.cpp
    debugjob.cpp
    framestackmodel.cpp
    breakpointcontroller.cpp
    messages.cpp
    launchconfig.cpp
    variablecontroller.cpp
    variable.cpp
    stringhelpers.cpp
)

set(kdeverldebug_PART_SRCS
    debugplugin.cpp
    launchconfig.cpp
    #launchconfigurationpage.cpp
)

set(kdevelerlang_UI_PARTS
  debug_config.ui)

kde4_add_ui_files(kdeverldebugcore_PART_SRCS ${kdevelerlang_UI_PARTS})
kde4_add_plugin(kdeverldebug ${kdeverldebugcore_PART_SRCS} ${kdeverldebug_PART_SRCS})

target_link_libraries(kdeverldebug 
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_DEBUGGER_LIBRARIES}
    ${KDEVPLATFORM_OUTPUTVIEW_LIBRARIES}
    ${KDEVPLATFORM_PROJECT_LIBRARIES}
    ${KDEVPLATFORM_UTIL_LIBRARIES}
)

install(TARGETS kdeverldebug DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES debug_interpreter.erl DESTINATION ${DATA_INSTALL_DIR}/kdeverlangsupport)


########### next target ###############

set(erlangdebuggertests_SRCS
    tests/debuggertests.cpp
)

kde4_add_unit_test(erlangdebuggertests ${erlangdebuggertests_SRCS} ${kdeverldebugcore_PART_SRCS} ${kdeverldebug_PART_SRCS})

target_link_libraries(erlangdebuggertests
    ${kdeverldebug}
    ${QT_QTTEST_LIBRARY}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_TESTSHELL_LIBRARIES}
    ${KDEVPLATFORM_DEBUGGER_LIBRARIES}
    ${KDEVPLATFORM_TESTS_LIBRARIES}
)



########### install files ###############

install(FILES kdeverldebug.desktop DESTINATION ${SERVICES_INSTALL_DIR})
