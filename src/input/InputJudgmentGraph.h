/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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