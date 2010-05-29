#add_subdirectory(test)

set(parser_STAT_SRCS
    erlanglexer.cpp
    editorintegrator.cpp
    parsesession.cpp
    )

kdevpgqt_generate(_kdevpgList erlang NAMESPACE erlang TOKEN_TEXT BEAUTIFUL_CODE
    "${erlang_SOURCE_DIR}/parser/erlang.g"
    "${erlang_SOURCE_DIR}/parser/erlanglexer.h"
)

set( parser_SRCS
    ${_kdevpgList}
)

kde4_add_library( kdev4erlangparser SHARED ${parser_SRCS} ${parser_STAT_SRCS} )
target_link_libraries( kdev4erlangparser
    ${KDE4_KDECORE_LIBS}
    ${KDEVPLATFORM_LANGUAGE_LIBRARIES}
    ${KDE4_KTEXTEDITOR_LIBS}
)

kde4_add_executable( erlang-parser main.cpp )
target_link_libraries(erlang-parser ${QT_QTCORE_LIBRARY} kdev4erlangparser)

install(TARGETS kdev4erlangparser DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS})

### next target
set(parsertest_SRCS tests/parsertest.cpp)
kde4_add_unit_test(parsertest ${parsertest_SRCS})
target_link_libraries(parsertest kdev4erlangparser ${QT_QTTEST_LIBRARY})

