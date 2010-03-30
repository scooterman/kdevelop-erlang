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

void TestParser::functionDeclaration()
{
    erlang::ParseSession session;
    session.setContents("my_func(VariableA, atom_b) -> ok.");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));
}

void TestParser::functionClausesDeclaration()
{
    erlang::ParseSession session;
    session.setContents("my_func(VariableA, atom_b) -> ok;  my_func(VariableA, atom_c) -> then.");
    FormAst* ast = 0;

    QVERIFY(session.parse(&ast));
}

void TestParser::list()
{
    {
        erlang::ParseSession session;
        session.setContents("test_list() -> X = [].");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        FormAst* ast = 0;
        session.setContents("test_list() -> X = []].");
        QVERIFY(session.parse(&ast) == false);
    }

    {
        erlang::ParseSession session;
        FormAst* ast = 0;

        session.setContents("test_list() -> X = [[]].");
        QVERIFY(session.parse(&ast) == true);
    }
}

void TestParser::testNumeric()
{
    {
        erlang::ParseSession session;
        session.setContents("test_list() -> X = 1.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        session.setContents("test_list() -> X = 11234512345235634745745623543244523.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }

    {
        erlang::ParseSession session;
        session.setContents("test_list() -> X = 1..");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast) == false);
    }

}

void TestParser::testVariable()
{
    {
        erlang::ParseSession session;
        session.setContents("test_variable() -> X = 123, @10 = 1.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast) == false);
    }
}

void TestParser::testRecord()
{
    {
        erlang::ParseSession session;
        session.setContents("-record(test, { a, b, c = 1, d = gb_trees::new() }).");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("test_record() -> X = #record_definition{}.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("test_record() -> X = #record_definition{ r_var1 = val1, r_var2 =  Y }.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
    {
        erlang::ParseSession session;
        session.setContents("test_record() -> X = Y#record_definition.value.");
        FormAst* ast = 0;

        QVERIFY(session.parse(&ast));
    }
    
}



}
