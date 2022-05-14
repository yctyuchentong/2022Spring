#include<iostream>

#define TRUE 1
#define FASLE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 1000

using namespace std;

typedef char TElemtype;
typedef int Status;
typedef struct BiTNode{
    TElemtype data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef BiTree SElemType;
typedef struct{
    SElemType *base;
    SElemType *top;
    int satcksize;
}SqStack;

typedef BiTree QElemType;
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
    QueuePtr fron;
    QueuePtr rear;
}LinkQueue;


//stack
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
bool StackEmpty(SqStack S){
    if(S.top==S.base)
        return true;
    else
        return false;
}


//队列操作
//构造空队列
Status InitQueue(LinkQueue &Q){
    Q.fron = Q.rear = new QNode;
    Q.fron->next = NULL;
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
//判断链队列是否为空
bool QueueEmpty(LinkQueue Q){
    return(Q.fron==Q.rear);
}



//创建二叉树
void CreateBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if (ch=='$'){
        T = NULL;
    }
    else{
    T = new BiTNode;
    T->data = ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
    }

}

//先序遍历二叉树
void PreOrderTraverse(BiTree T){
    if(T){
        cout<<T->data<<" ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

//递归中序遍历二叉树
void InOrderTraverse1(BiTree T){
    if(T){
        InOrderTraverse1(T->lchild);
        cout<<T->data<<" " ;
        InOrderTraverse1(T->rchild);
    }
}

//利用栈实现中序遍历
void InOrderTraverse2(BiTree T){
    SqStack S;
    InitStack(S);
    BiTree p = T;
    BiTree q;
    while(p||!StackEmpty(S)){
        if(p){
            Push(S,p);
            p = p->lchild;
        }
        else{
            Pop(S,q);
            cout<<q->data<<" ";
            p = q->rchild;
        }
    }

}

//后序遍历
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data<<" ";
    }
}

//层序遍历
void LayerOrderTraverse(BiTree T){
    BiTree tr = T;
    LinkQueue q;
    InitQueue(q);
    EnQueue(q,tr);
    while(!QueueEmpty(q)){
        DeQueue(q,tr);
        cout<<tr->data<<" ";
        if(tr->lchild)
            EnQueue(q,tr->lchild);
        if(tr->rchild)
            EnQueue(q,tr->rchild);
    }

}

//深度
int DepthTree(BiTree T){
    if(!T){
       return 0;
    }
    int m = DepthTree(T->lchild);
    int n = DepthTree(T->rchild);
    if(m>=n){
        return m+1;
    }
    else{
        return n+1;
    }
}

//判断完全二叉树

bool isWholeT(BiTree T){
    if(T==NULL){
        return true;
    }
    BiTree tr = T;
    bool leaf=false;
    LinkQueue q;
    InitQueue(q);
    EnQueue(q,tr);
    while(!QueueEmpty(q)){
        DeQueue(q,tr);
        if((leaf&&(tr->lchild!=NULL||tr->rchild!=NULL))||(tr->lchild==NULL&&tr->rchild!=NULL))
            return false;
        if(tr->lchild)
            EnQueue(q,tr->lchild);
        if(tr->rchild)
            EnQueue(q,tr->rchild);
    }
    return true;

}

int main(){

    BiTree T;
    while(1){
        cout<<"****************************************"<<endl;
        cout<<"********** 1.创建二叉树       **********"<<endl;
        cout<<"********** 2.先序遍历二叉树   **********"<<endl;
        cout<<"********** 3.中序遍历二叉树1  **********"<<endl;
        cout<<"********** 4.中序遍历二叉树2  **********"<<endl;
        cout<<"********** 5.后序遍历二叉树   **********"<<endl;
        cout<<"********** 6.层序遍历二叉树   **********"<<endl;
        cout<<"********** 7.求二叉树的深度   **********"<<endl;
        cout<<"********** 8.退出             **********"<<endl;
        cout<<"****************************************"<<endl;

        int n;
        cin>>n;

        if (n==1){
            CreateBiTree(T);
            cout<<"创建成功"<<endl;
        }
        if(n==2){
            PreOrderTraverse(T);
        }
        if(n==3){
            InOrderTraverse1(T);
        }
        if(n==4){
            InOrderTraverse2(T);
        }
        if(n==5){
            PostOrderTraverse(T);
        }
        if(n==6){
            LayerOrderTraverse(T);
        }
        if(n==7){
            cout<<"二叉树的深度为:"<<DepthTree(T)<<endl;
        }
        if(n==8){
            break;
        }
        cout<<endl;
    }

    return 0;
}

/*
A
B
C
$
$
D
E
$
G
$
$
F
$
$
$

A
B
C


D
E

G


F






a
b
d
#
#
e
#
#
c
f
#
#
g
#
#

*/
