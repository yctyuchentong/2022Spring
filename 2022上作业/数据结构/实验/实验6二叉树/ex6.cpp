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
bool StackEmpty(SqStack S){
    if(S.top==S.base)
        return true;
    else
        return false;
}


//���в���
//����ն���
Status InitQueue(LinkQueue &Q){
    Q.fron = Q.rear = new QNode;
    Q.fron->next = NULL;
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
//�ж��������Ƿ�Ϊ��
bool QueueEmpty(LinkQueue Q){
    return(Q.fron==Q.rear);
}



//����������
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

//�������������
void PreOrderTraverse(BiTree T){
    if(T){
        cout<<T->data<<" ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

//�ݹ��������������
void InOrderTraverse1(BiTree T){
    if(T){
        InOrderTraverse1(T->lchild);
        cout<<T->data<<" " ;
        InOrderTraverse1(T->rchild);
    }
}

//����ջʵ���������
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

//�������
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data<<" ";
    }
}

//�������
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

//���
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

//�ж���ȫ������

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
        cout<<"********** 1.����������       **********"<<endl;
        cout<<"********** 2.�������������   **********"<<endl;
        cout<<"********** 3.�������������1  **********"<<endl;
        cout<<"********** 4.�������������2  **********"<<endl;
        cout<<"********** 5.�������������   **********"<<endl;
        cout<<"********** 6.�������������   **********"<<endl;
        cout<<"********** 7.������������   **********"<<endl;
        cout<<"********** 8.�˳�             **********"<<endl;
        cout<<"****************************************"<<endl;

        int n;
        cin>>n;

        if (n==1){
            CreateBiTree(T);
            cout<<"�����ɹ�"<<endl;
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
            cout<<"�����������Ϊ:"<<DepthTree(T)<<endl;
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
