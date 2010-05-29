PROJECT(erlang)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${erlang_SOURCE_DIR}/cmake)

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

#Don't error out if the FindXXX are missing for these two
find_package(KDevelop-PG-Qt REQUIRED)

include_directories(
    ${CMAKE_BINARY_DIR}/parser
    ${KDEVPGQT_INCLUDE_DIR}
)

add_subdirectory(parser)
add_subdirectory(app_templates)

set(kdeverlanglanguagesupport_PART_SRCS
    erlanglanguagesupport.cpp
    #completion/model.cpp
    #completion/contentassistdata.cpp
    parsejob.cpp
    duchain/builders/contextbuilder.cpp
    duchain/builders/declarationbuilder.cpp
    duchain/declarations/functiondeclaration.cpp
    duchain/declarations/variabledeclaration.cpp
    #navigation/fieldnavigationcontext.cpp
    #navigation/navigationwidget.cpp
    #navigation/valuenavigationcontext.cpp
)

kde4_add_plugin(kdeverlanglanguagesupport ${kdeverlanglanguagesupport_PART_SRCS})

target_link_libraries(kdeverlanglanguagesupport
    ${KDE4_KDEUI_LIBS}
    ${KDEVPLATFORM_INTERFACES_LIBRARIES}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
    kdev4erlangparser
)

install(TARGETS kdeverlanglanguagesupport DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES kdeverlangsupport.desktop DESTINATION ${SERVICES_INSTALL_DIR})

### next target
#set(completionmodeltest_SRCS
#     completion/test/modeltest.cpp
#     completion/model.cpp
#     completion/contentassistdata.cpp
# )
# kde4_add_unit_test(completionmodeltest ${completionmodeltest_SRCS})
# target_link_libraries(completionmodeltest
#     kdev4erlangparser
#     ${KDE4_KDEUI_LIBS}
#     ${KDE4_KTEXTEDITOR_LIBS}
#     ${QT_QTGUI_LIBRARY}
#     ${QT_QTTEST_LIBRARY}
# )
# 
# 
### next target
set(duchaintest_SRCS
    duchain/tests/duchain.cpp
    duchain/tests/duchaintestbase.cpp
    duchain/builders/contextbuilder.cpp
    duchain/builders/declarationbuilder.cpp
)
kde4_add_unit_test(duchaintest ${duchaintest_SRCS})

target_link_libraries(duchaintest
    kdev4erlangparser
    ${KDE4_KDEUI_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTTEST_LIBRARY}
)

# 
# 
# ### next target
# set(parsejobtest_SRCS
#     duchain/tests/parsejobtest.cpp
# )
# kde4_add_unit_test(parsejobtest ${parsejobtest_SRCS})
# target_link_libraries(parsejobtest
#     ${KDEVPLATFORM_INTERFACES_LIBRARIES}
#     ${KDEVPLATFORM_TESTS_LIBRARIES}
#     ${QT_QTTEST_LIBRARY}
# )


add_subdirectory(debug)