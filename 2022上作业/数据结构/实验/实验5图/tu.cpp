#include<iostream>
#define MaxInt 32767
#define MVNum 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

using namespace std;

typedef char VertexType;
typedef int ArcType;
typedef int Status;

typedef struct{
    VertexType vexs[MVNum];//¶¥µã±í
    ArcType arcs[MVNum][MVNum];//ÁÚ½Ó¾ØÕó
    int vexnum,arcnum;
}AmGraph;

int LocateVex(AmGraph G,VertexType u){
    int i ;
    for(int i=0;i<G.vexnum;i++){
        if(u==G.vexs[i]){
            return i;
        }
    }
    return -1;
}



int  main(){

    return 0;
}
