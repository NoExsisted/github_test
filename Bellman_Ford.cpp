#include <iostream>
using namespace std;
const int MAX = 510;
const int MAXE = 100010;
const int INF = 1000010;
int dis[MAX];
struct Edge             
{
    int start;   
    int end;
    int weight;  
};

class Graph
{
private:
    int vexnum;//结点
    int arcnum;//边数
    Edge info[MAXE];//结点信息
    int dis[MAX];//邻接矩阵（权重）
public:
    Graph();
    void initialize();
    void relax(Edge x);
    bool Bellman_Ford();
    void print();
};

Graph::Graph()
{
    cin >> vexnum >> arcnum;
    for (int i = 1; i <= vexnum; i++)
    {
        dis[i] = INF;
    }
    dis[1] = 0; 
}

void Graph::initialize()
{
    int i, j;
    for (i = 1; i <= arcnum; i++)
    {
        cin >> info[i].start >> info[i].end >> info[i].weight;
        if (info[i].start == info[i].end) //自环
        {
            info[i].weight = 0;
        }
        if (info[i].start == 1) 
        {
            dis[info[i].end] = info[i].weight;
        }
    }
}

void Graph::relax(Edge x)
{
    if (dis[x.end] > dis[x.start] + x.weight)
    {
        dis[x.end] = dis[x.start] + x.weight;
    }
}

bool Graph::Bellman_Ford()
{
    initialize();
    int i, j;
    for(i = 1; i < vexnum; i++)
    {
        int flag1 = 0;
        for (j = 1; j <= arcnum; j++)
        {
            if (dis[info[j].start] != INF)
            {
                relax(info[j]);
                flag1 = 1;
            }
        }
        if (!flag1) 
        {
            break;
        }
    }
    for (int i = 1; i <= arcnum; i++)//检查负环
    {
        if (dis[info[i].end] > dis[info[i].start] + info[i].weight)
        {
            return false;
        }
    }
    if (dis[vexnum] == INF) 
    {
        return false;
    }
    return true;
}

void Graph::print()
{
    cout<<dis[vexnum]<<endl;
}

int main()
{
    Graph graph;
    if(graph.Bellman_Ford())
    {
        graph.print();
    }
    else
    {
        cout<<-1<<endl;
    }
    return 0;
}