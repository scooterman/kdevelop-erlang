#add_subdirectory(test)

set(parser_STAT_SRCS
    erlanglexer.cpp
    editorintegrator.cpp
    )

if(KDEVPGQT_FOUND)
     kdevpgqt_generate(_kdevpgList erlang NAMESPACE Erlang DEBUG_VISITOR TOKEN_TEXT
        "${erlang_SOURCE_DIR}/parser/erlang.g"
        "${erlang_SOURCE_DIR}/parser/erlanglexer.h"
    )
    set( parser_SRCS
       ${_kdevpgList}
   )
else(KDEVPGQT_FOUND)
   message(STATUS "Assuming existence of generated parser files")
   set(parser_SRCS
       generated/erlangparser.cpp
       generated/erlangvisitor.cpp
       generated/erlangdefaultvisitor.cpp
       editorintegrator.cpp
       erlanglexer.cpp
       parsesession.cpp)

endif(KDEVPGQT_FOUND)


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

add_custom_target( copy-generated
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${php_BINARY_DIR}/parser/erlangparser.cpp" "${erlang_SOURCE_DIR}/parser/generated/erlangparser.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangparser.h" "${erlang_SOURCE_DIR}/parser/generated/erlangparser.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangast.h" "${erlang_SOURCE_DIR}/parser/generated/erlangast.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangvisitor.h" "${erlang_SOURCE_DIR}/parser/generated/erlangvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangvisitor.cpp" "${erlang_SOURCE_DIR}/parser/generated/erlangvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangdefaultvisitor.h" "${erlang_SOURCE_DIR}/parser/generated/erlangdefaultvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangdefaultvisitor.cpp" "${erlang_SOURCE_DIR}/parser/generated/erlangdefaultvisitor.cpp"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangdebugvisitor.h" "${erlang_SOURCE_DIR}/parser/generated/erlangdebugvisitor.h"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${erlang_BINARY_DIR}/parser/erlangtokentext.h" "${erlang_SOURCE_DIR}/parser/generated/erlangtokentext.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangparser.cpp"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangparser.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangvisitor.cpp"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangvisitor.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangdefaultvisitor.cpp"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangdefaultvisitor.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangast.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangdebugvisitor.h"
    DEPENDS "${erlang_BINARY_DIR}/parser/erlangtokentext.h"
    )
