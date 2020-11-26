#include <cstdio>
#include <iostream>

#include <QDebug>

#include "InputJudgmentGraph.h"

using namespace std;

InputJudgmentGraph::InputJudgmentGraph()
{
    creatGraph();
}

bool InputJudgmentGraph::getStatus(QString needGet)
{
    return node[nodeIdx[needGet]].status;
}

bool InputJudgmentGraph::find(QString needFind)
{
    if ( dfs(needFind, nodeIdx[ROOT], 0) )
        return true;
    else
        return false;
    return false;
}

void InputJudgmentGraph::update(QString needUpdate, int flag)
{
    node[nodeIdx[needUpdate]].status = flag;
    return ;
}

void InputJudgmentGraph::updateAllSon(QString needUpdate, int flag)
{
    update(needUpdate, flag);
    int u = nodeIdx[needUpdate];
    for (int i = 0; i <= node[u].to.size(); i++) {
        int v = node[u].to[i];
        update(node[v].name, flag);
    }
    return ;
}

void InputJudgmentGraph::print()
{
    for (int i = 0; i < node.size(); i++) {
        qDebug() << node[i].name;
        for (int j = 0; j < node[i].to.size(); j++) {
            cout << node[node[i].to[j]].name.toStdString() << ' ';
        }
        cout << endl;
        cout << "***********" << endl;
    }
    return ;
}

void InputJudgmentGraph::addEdge(QString fromNode, QString toNode)
{
    node[nodeIdx[fromNode]].to.append(nodeIdx[toNode]);
    return ;
}

void InputJudgmentGraph::addNode(QString nodeName)
{
    GraphNode t;
//    cout << nodeName.toStdString() << ' ' << nodeCnt << endl;
    t.idx         = nodeCnt;
    t.name        = nodeName;
    t.status      = true;
    t.to.clear();
    node.append(t);
    nodeIdx.insert(nodeName, nodeCnt);
    nodeCnt++;
    return ;
}

bool InputJudgmentGraph::dfs(QString needFind, int now, bool flag)
{
    if (flag)
        return flag;
    if (!node[now].status)
        return flag;
    if ( node[now].name == needFind ) {
        flag = true;
        return flag;
    }
    for (int i = 0 ; i < node[now].to.size(); i++) {
        int v = node[now].to[i];
        if ( dfs(needFind, v, flag) ) {
            return true;
        }
    }
    return flag;
}

void InputJudgmentGraph::creatGraph()
{
    addNode(ROOT);

    addNode(STANDARD);   addEdge(ROOT, STANDARD);
    addNode(SCIENTIFIC); addEdge(ROOT, SCIENTIFIC);
    addNode(CLEAN);      addEdge(ROOT, CLEAN);
    addNode(BACKSPACE);  addEdge(ROOT, BACKSPACE);

    addNode(ERROR);      addEdge(STANDARD, ERROR);
    addNode(ERROR_INF);  addEdge(SCIENTIFIC, ERROR_INF);
    addNode(ERROR_NAN);  addEdge(ERROR_INF, ERROR_NAN);

    addNode(TRANS);    addEdge(ERROR_NAN, TRANS);
    addNode(FUNCTION); addEdge(ERROR_NAN, FUNCTION);
    addNode(SCI_NUM);  addEdge(ERROR_NAN, SCI_NUM);

    addNode(BRACKET_L); addEdge(ERROR_NAN, BRACKET_L);
    addNode(BRACKET_R); addEdge(ERROR_NAN, BRACKET_R);

    addNode(ZERO);  addEdge(ERROR, ZERO);  addEdge(ERROR_NAN, ZERO);  
    addNode(ONE);   addEdge(ERROR, ONE);   addEdge(ERROR_NAN, ONE);
    addNode(TWO);   addEdge(ERROR, TWO);   addEdge(ERROR_NAN, TWO);
    addNode(THREE); addEdge(ERROR, THREE); addEdge(ERROR_NAN, THREE); 
    addNode(FOUR);  addEdge(ERROR, FOUR);  addEdge(ERROR_NAN, FOUR);
    addNode(FIVE);  addEdge(ERROR, FIVE);  addEdge(ERROR_NAN, FIVE);
    addNode(SIX);   addEdge(ERROR, SIX);   addEdge(ERROR_NAN, SIX);
    addNode(SEVEN); addEdge(ERROR, SEVEN); addEdge(ERROR_NAN, SEVEN);
    addNode(EIGHT); addEdge(ERROR, EIGHT); addEdge(ERROR_NAN, EIGHT);
    addNode(NINE);  addEdge(ERROR, NINE);  addEdge(ERROR_NAN, NINE);
    addNode(PERCENT);     addEdge(ERROR, PERCENT);      addEdge(ERROR_NAN, PERCENT);
    addNode(POINT);       addEdge(PERCENT, POINT);
    addNode(DOUBLE_ZERO); addEdge(ERROR, DOUBLE_ZERO); addEdge(ERROR_NAN, DOUBLE_ZERO);
    
    addNode(ADD);   addEdge(ERROR, ADD);   addEdge(ERROR_NAN, ADD);
    addNode(SUB);   addEdge(ERROR, SUB);   addEdge(ERROR_NAN, SUB);
    addNode(MUL);   addEdge(ERROR, MUL);   addEdge(ERROR_NAN, MUL);
    addNode(DIV);   addEdge(ERROR, DIV);   addEdge(ERROR_NAN, DIV);
    addNode(EQUAL); addEdge(ERROR, EQUAL); addEdge(ERROR_NAN, EQUAL);



    addNode(SIN);    addEdge(FUNCTION, SIN);
    addNode(COS);    addEdge(FUNCTION, COS);
    addNode(TAN);    addEdge(FUNCTION, TAN);
    addNode(ARCSIN); addEdge(FUNCTION, ARCSIN);
    addNode(ARCCOS); addEdge(FUNCTION, ARCCOS);
    addNode(ARCTAN); addEdge(FUNCTION, ARCTAN);
    addNode(LOG);    addEdge(FUNCTION, LOG);
    addNode(LN);     addEdge(FUNCTION, LN);

    addNode(RECIPROCAL);  addEdge(TRANS, RECIPROCAL);
    addNode(SQUARE);      addEdge(TRANS, SQUARE);
    addNode(CUBE);        addEdge(TRANS, CUBE);
    addNode(POWER);       addEdge(TRANS, POWER);
    addNode(SQUARE_ROOT); addEdge(TRANS, SQUARE_ROOT);
    addNode(CUBE_ROOT);   addEdge(TRANS, CUBE_ROOT);
    addNode(POWER_ROOT);  addEdge(TRANS, POWER_ROOT);
    addNode(FACTORIAL);   addEdge(TRANS, FACTORIAL);

    addNode(PI);  addEdge(SCI_NUM, PI);
    addNode(E);   addEdge(SCI_NUM, E);
    addNode(ANS); addEdge(SCI_NUM, ANS);

    return ;
}
