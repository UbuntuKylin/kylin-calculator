#ifndef __INPUT_JUDGMENT_GRAPH__
#define __INPUT_JUDGMENT_GRAPH__

#include <QString>
#include <QVector>
#include <QMap>

#include "InputSymbols.h"
class InputJudgmentGraph : public InputSymbols
{
public :

    InputJudgmentGraph();
    bool getStatus    (QString needGet);
    bool find         (QString needFind);
    void update       (QString needUpdate, int flag);
    void updateAllSon (QString needUpdate, int flag);
    void print        ();

    
private:

    void addEdge    (QString fromNode, QString toNode);
    void addNode    (QString nodeName);
    bool dfs        (QString needFind, int now, bool flag);
    void creatGraph ();
    int nodeCnt = 0;

    class GraphNode
    {
    public:
        GraphNode() {};
        int          idx;
        QString      name;
        bool         status;
        QVector<int> to;
    };
    QVector<GraphNode> node;
    QMap<QString, int> nodeIdx;
};

#endif