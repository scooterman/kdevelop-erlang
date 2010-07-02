#ifndef ERLANG_PARSERTEST_H
#define ERLANG_PARSERTEST_H

#include <QObject>

namespace erlang
{

class TestParser : public QObject
{
    Q_OBJECT

public:
    TestParser();

private Q_SLOTS:   
    /*void functionDeclaration();
    void functionClausesDeclaration();
    void list();    
    void testVariable();
    void testRecord();
    void testDefine();*/
    void testNumeric();
    void textExport();
};

}

#endif