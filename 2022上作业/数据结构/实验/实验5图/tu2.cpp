#include<iostream>
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MaxInt 32767
#define MVNum 100

using namespace std;

typedef int VertexType;
typedef int ArcType;
typedef int SElemType;
typedef int Status;
typedef int QElemType;
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr fron;
    QueuePtr rear;
}LinkQueue;
typedef struct{
    SElemType *base;
    SElemType *top;
    int satcksize;
}SqStack;

typedef struct{
    VertexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum,arcnum;
}AmGraph;

//初始化栈
Status InitStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.satcksize=MAXSIZE;
    return OK;
}

//入栈
Status Push(SqStack &S,SElemType e){
    if(S.top-S.base==S.satcksize)
        return ERROR;
    *S.top++=e;
    return OK;
}
//出栈
Status Pop(SqStack &S,SElemType &e){
    if (S.top==S.base){
        return ERROR;
    }
    e=*(--S.top);
    return OK;
}

//取栈顶元素
SElemType GetTop(SqStack S){
    if (S.top==S.base){
        return ERROR;
    }
    SElemType e = *(S.top-1);
    return e;
}

//销毁栈
Status DestoryStack(SqStack &S){
    if(S.base){
        delete[] S.base;
        S.satcksize = 0;
        S.base = S.top = NULL;

    }
    return OK;
}

//清空栈
Status ClearStack(SqStack &S){
    if(S.base){
        S.top=S.base;
    }
    return OK;
}
//判断栈空
bool StackEmpty(SqStack S){
    if(S.top==S.base)
        return true;
    else
        return false;
}

//返回栈的长度
int StackLength(SqStack S){
    return S.top-S.base;
}

//输出栈内元素
Status ShowStack(SqStack S){
    if (S.base==S.top){
        return ERROR;
    }
    while(S.top!=S.base){
        S.top--;
        cout<<*S.top<<" ";
    }
    cout<<endl;
    return OK;
}

//创建并输入栈元素
Status CreateStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.satcksize=MAXSIZE;
    int n;
    cout<<"请输入栈元素：";
    while(cin>>n){

        if(S.top-S.base==MAXSIZE){
            cout<<"超过最大长度"<<endl;
            return ERROR;
        }
        *S.top = n;
        S.top++;
        if(cin.get()=='\n')
                    break;

    }
    return OK;
}

//构造空队列
Status InitQueue(LinkQueue &Q){
    Q.fron = Q.rear = new QNode;
    Q.fron->next = NULL;
    return OK;
}

//2.销毁队列
Status DestoryQueue(LinkQueue &Q){
    while(Q.fron){
        Q.rear = Q.fron->next;
        delete Q.fron;
        Q.fron = Q.rear;
    }
    return OK;
}

//清空队列
Status ClearQueue(LinkQueue &Q){
    Q.fron->next = Q.rear;
    Q.rear->data=NULL;
    return OK;
}

//判断链队列是否为空
bool QueueEmpty(LinkQueue Q){
    return(Q.fron==Q.rear);
}

//求链队列的队头元素
Status GetHead(LinkQueue Q,QElemType &e){
    if(Q.fron==Q.rear)
        return ERROR;
    e = Q.fron->next->data;
    return OK;
}

//入队操作
Status EnQueue(LinkQueue &Q,QElemType e){
    QueuePtr p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//出队操作
Status DeQueue(LinkQueue &Q,QElemType &e){
    if(Q.fron==Q.rear){
        return ERROR;
    }
    QueuePtr p = Q.fron->next;
    e = p->data;
    Q.fron->next = p->next;

    if(Q.rear==p){
        Q.rear=Q.fron;
        delete p;
        return OK;
    }
}

//创建队列
Status CreatQueue(LinkQueue &Q){
    Q.fron =Q.rear=new QNode;
    Q.fron->next = NULL;
    QElemType e;
    cout<<"请输入要的元素："<<endl;
    while(cin>>e){
        EnQueue(Q,e);
        if(cin.get()=='\n'){
                    break;
                }
    }
    return OK;
}

//返回队列中元素的个数
int NumQueue(LinkQueue Q){
    int n = 0;
    while(Q.fron->next){
        n++;
        Q.fron = Q.fron->next;
    }
    return n;

}

//返回队头元素
QElemType GetQueueFront(LinkQueue Q){
    if(Q.fron==Q.rear){
        return ERROR;
    }
    return Q.fron->next->data;
}


//显示队列中的元素
Status ShowQueue(LinkQueue Q){
    if(QueueEmpty(Q)){
        return ERROR;
    }
    while(Q.fron->next){
        Q.fron = Q.fron->next;
        cout<<Q.fron->data<<" ";
    }
    cout<<endl;
    return OK;
}








int LocateVex(AmGraph G,VertexType u){
    int i ;
    for(int i=0;i<G.vexnum;i++){
        if(u==G.vexs[i]){
            return i;
        }
    }
    return -1;
}



Status CreateUDN(AmGraph &G){
    cout<<"请输入总顶点数：";
    cin>>G.vexnum;
    cout<<"请输入总边数";
    cin>>G.arcnum;
    for(int i=0;i<G.vexnum;i++){
        cout<<"请输入顶点信息:";
        cin>>G.vexs[i];
    }
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j] = 0;
        }
    }
    VertexType v1,v2;
    for(int k=0;k<G.arcnum;k++){
        cout<<"请输入第"<<k<<"条边依附的顶点：";
        cin>>v1>>v2;
        int i = LocateVex(G,v1);
        int j = LocateVex(G,v2);
        G.arcs[i][j] = 1;
        G.arcs[j][i] = 1;
    }
    return OK;

}

Status CreateUDN2(AmGraph &G){
    G.vexnum = 6;
    G.arcnum = 8;
    for(int i=0;i<G.vexnum;i++){
        G.vexs[i] = i+1;
    }
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j] = 0;
        }
    }
    VertexType v1,v2;
    int i,j;
    v1 = 1;
    v2 = 2;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 1;
    v2 = 6;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;


    v1 = 2;
    v2 = 3;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 2;
    v2 = 4;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 3;
    v2 = 4;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 3;
    v2 = 5;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 4;
    v2 = 5;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;

    v1 = 6;
    v2 = 5;
    i = LocateVex(G,v1);
    j = LocateVex(G,v2);
    G.arcs[i][j] = 1;
    G.arcs[j][i] = 1;


    return OK;

}

void OutPutUDN(AmGraph G){
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            cout<<G.arcs[i][j]<<" ";
        }
        cout<<endl;
    }
}

void DFS_AM(AmGraph G,int v,bool *visit){
    cout<<v+1<<" ";
    visit[v] = true;
    for(int w=0;w<G.vexnum;w++){
        if((G.arcs[v][w]!=0)&&(!visit[w]))
            DFS_AM(G,w,visit);
    }
}

void BFS_AM(AmGraph G,int v){
    OutPutUDN(G);
    LinkQueue q;
    InitQueue(q);
    EnQueue(q,v);
    bool visit[G.vexnum] = {0};
    while(!QueueEmpty(q)){
        QElemType e;

        DeQueue(q,e);
        visit[e] = true;
//        cout<<"value:"<<e+1<<" ";
        for(int i=0;i<G.vexnum;i++){
//            cout<<"e:"<<e<<"i:"<<i<<"visit:"<<visit[i]<<"G.arcs:"<<G.arcs[e][i]<<endl;
            if(!visit[i]&&(G.arcs[e][i]==1)){
                QElemType e2 = i;
                EnQueue(q,e2);
            }
        }
    }


}




int  main(){

    AmGraph G;
    CreateUDN2(G);
    OutPutUDN(G);
    bool visit[G.vexnum] = {0};
    DFS_AM(G,0,visit);
    cout<<endl;
    BFS_AM(G,0);
    return 0;
}
