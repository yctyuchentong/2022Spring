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

//��ʼ��ջ
Status InitStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.satcksize=MAXSIZE;
    return OK;
}

//��ջ
Status Push(SqStack &S,SElemType e){
    if(S.top-S.base==S.satcksize)
        return ERROR;
    *S.top++=e;
    return OK;
}
//��ջ
Status Pop(SqStack &S,SElemType &e){
    if (S.top==S.base){
        return ERROR;
    }
    e=*(--S.top);
    return OK;
}

//ȡջ��Ԫ��
SElemType GetTop(SqStack S){
    if (S.top==S.base){
        return ERROR;
    }
    SElemType e = *(S.top-1);
    return e;
}

//����ջ
Status DestoryStack(SqStack &S){
    if(S.base){
        delete[] S.base;
        S.satcksize = 0;
        S.base = S.top = NULL;

    }
    return OK;
}

//���ջ
Status ClearStack(SqStack &S){
    if(S.base){
        S.top=S.base;
    }
    return OK;
}
//�ж�ջ��
bool StackEmpty(SqStack S){
    if(S.top==S.base)
        return true;
    else
        return false;
}

//����ջ�ĳ���
int StackLength(SqStack S){
    return S.top-S.base;
}

//���ջ��Ԫ��
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

//����������ջԪ��
Status CreateStack(SqStack &S){
    S.base = new SElemType[MAXSIZE];
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.satcksize=MAXSIZE;
    int n;
    cout<<"������ջԪ�أ�";
    while(cin>>n){

        if(S.top-S.base==MAXSIZE){
            cout<<"������󳤶�"<<endl;
            return ERROR;
        }
        *S.top = n;
        S.top++;
        if(cin.get()=='\n')
                    break;

    }
    return OK;
}

//����ն���
Status InitQueue(LinkQueue &Q){
    Q.fron = Q.rear = new QNode;
    Q.fron->next = NULL;
    return OK;
}

//2.���ٶ���
Status DestoryQueue(LinkQueue &Q){
    while(Q.fron){
        Q.rear = Q.fron->next;
        delete Q.fron;
        Q.fron = Q.rear;
    }
    return OK;
}

//��ն���
Status ClearQueue(LinkQueue &Q){
    Q.fron->next = Q.rear;
    Q.rear->data=NULL;
    return OK;
}

//�ж��������Ƿ�Ϊ��
bool QueueEmpty(LinkQueue Q){
    return(Q.fron==Q.rear);
}

//�������еĶ�ͷԪ��
Status GetHead(LinkQueue Q,QElemType &e){
    if(Q.fron==Q.rear)
        return ERROR;
    e = Q.fron->next->data;
    return OK;
}

//��Ӳ���
Status EnQueue(LinkQueue &Q,QElemType e){
    QueuePtr p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

//���Ӳ���
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

//��������
Status CreatQueue(LinkQueue &Q){
    Q.fron =Q.rear=new QNode;
    Q.fron->next = NULL;
    QElemType e;
    cout<<"������Ҫ��Ԫ�أ�"<<endl;
    while(cin>>e){
        EnQueue(Q,e);
        if(cin.get()=='\n'){
                    break;
                }
    }
    return OK;
}

//���ض�����Ԫ�صĸ���
int NumQueue(LinkQueue Q){
    int n = 0;
    while(Q.fron->next){
        n++;
        Q.fron = Q.fron->next;
    }
    return n;

}

//���ض�ͷԪ��
QElemType GetQueueFront(LinkQueue Q){
    if(Q.fron==Q.rear){
        return ERROR;
    }
    return Q.fron->next->data;
}


//��ʾ�����е�Ԫ��
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
    cout<<"�������ܶ�������";
    cin>>G.vexnum;
    cout<<"�������ܱ���";
    cin>>G.arcnum;
    for(int i=0;i<G.vexnum;i++){
        cout<<"�����붥����Ϣ:";
        cin>>G.vexs[i];
    }
    for(int i=0;i<G.vexnum;i++){
        for(int j=0;j<G.vexnum;j++){
            G.arcs[i][j] = 0;
        }
    }
    VertexType v1,v2;
    for(int k=0;k<G.arcnum;k++){
        cout<<"�������"<<k<<"���������Ķ��㣺";
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
