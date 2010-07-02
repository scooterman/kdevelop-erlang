#include "parsertest.h"

#include <QTest>

#include "../parsesession.h"
#include "../editorintegrator.h"

QTEST_MAIN(erlang::TestParser)

namespace erlang
{

TestParser::TestParser()
{
}

#ifdef disabled
void TestParser::functionDeclaration()
{
    erlang::ParseSession session;
    session.setContents("my_func(VariableA, atom_b) -> ok.");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));
}

void TestParser::functionClausesDeclaration()
{
  {
    erlang::ParseSession session;
    session.setContents("-module(test).\n my_func(VariableA, atom_b) -> ok;  my_func(VariableA, atom_c) -> then.");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));
  }
  {
    erlang::ParseSession session;
    session.setContents("-module(test).\n my_func(VariableA, atom_b) -> ok;  my_func() -> other_func().");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));    
  }  
}
#endif

void TestParser::textExport()
{
  {
    erlang::ParseSession session;
    session.setContents("-module(test).\n -export([start/0, start_loop/0]). function() -> ok.");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));
  }  
}

#ifdef disabled
void TestParser::list()
{
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_list() -> X = [].");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    /*TODO: problempointer is crashing?
    {
        erlang::ParseSession session;
        FormAst* ast = 0;
        session.setContents("-module(test).\ntest_list() -> X = []].");
        QVERIFY(session.parse(&ast) == false);
    }*/

    {
        erlang::ParseSession session;
        FormAst* ast = 0;

        session.setContents("-module(test).\ntest_list() -> X = [[]].");
        QVERIFY(session.parse(&ast) == true);
    }
}

void TestParser::testDefine()
{
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\n-define(MACRO, io:format(\"teste\",[])).\ntest_func() -> ?MACRO, ?MACRO, ?MACRO.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
}
#endif

void TestParser::testNumeric()
{
    {
        erlang::ParseSession session;
        session.setContents("-module(teste_sup). \n teste(- 1 ) ->  ok.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_list() -> X = 1.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_list() -> X = 11234512345235634745745623543244523.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_list() -> X = - 11234512345235634745745623543244523.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }


    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_list() -> X = 1..");
        FormAst* ast = 0;

        //QVERIFY(session.parse(&ast) == false);
    }

}

#if defined disabled
void TestParser::testVariable()
{
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_variable() -> X = 123, @10 = 1.");
        FormAst* ast = 0;

        //QVERIFY(session.parse(&ast) == false);
    }
}

void TestParser::testRecord()
{
    /*{
        erlang::ParseSession session;
        session.setContents("-module(test).\n-record(test, { a, b, c = 1, d = gb_trees::new() }).");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_record() -> X = #record_definition{}.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_record() -> X = #record_definition{ r_var1 = val1, r_var2 =  Y }.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("-module(test).\ntest_record() -> X = Y#record_definition.value.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }*/
    
}
#endif


}
