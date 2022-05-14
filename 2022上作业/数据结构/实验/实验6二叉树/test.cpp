#include<iostream>
#include<cstring>


using namespace std;


typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;



void FindMin(HuffmanTree &HT,int i,int &min1,int &min2){

    for(int j = 1;j<i;j++){
        if(HT[j].parent==-1){
            if(HT[j].weight<HT[min1].weight){
                min1=j;
            }
        }
    }
    HT[min1].parent = 0;
    for(int j = 1;j<i;j++){
        if(HT[j].parent==-1){
            if(HT[j].weight<HT[min2].weight){
                min2=j;
            }
        }
    }
}

//0:a--25:z
void InputHaffmanTree(int *frequency){
    cout<<"请输入a-z和空格和出现频率:"<<endl;
    for(int i=0;i<27;i++){
        cin>>frequency[i];
    }

}

void InitHuffmanTree(HuffmanTree &HT,int n,int * frequency){
    HT[0].weight = 10000;
    for(int i=1;i<n+1;i++){
        HT[i].weight = frequency[i-1];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for(int i=n+1;i<=2*n-1;i++){
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
}


void CreateHuffmanTree(HuffmanTree &HT,int n){
    int m = 2*n-1;

    for(int i = n+1;i<m+1;i++){
        int min1 =0,min2=0;
        FindMin(HT,i,min1,min2);
        HT[min1].parent = i;
        HT[min2].parent = i;
        HT[i].weight = HT[min1].weight+HT[min2].weight;
        HT[i].lchild = min1;
        HT[i].rchild = min2;
    }
}


void CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
    HC = new char*[n+1];
    char *cd = new char[n];
    cd[n-1]= '\0';
    for(int i=1;i<=n;i++){
        int start = n-1;
        int c=i;
        int f =HT[i].parent;
        while(f!=-1){
            --start;
            if(HT[f].lchild==c){
                cd[start]='0';
            }else{
                cd[start]='1';
            }
            c=f;
            f=HT[f].parent;
        }
        HC[i] = new char[n-start];
        strcpy(HC[i],&cd[start]);

    }
    delete cd;
}

void OutPutHuffmanCode(HuffmanCode HC,int n){
    for(int i=1;i<n;i++){
        cout<<(char)(i-1+'a')<<":"<<HC[i]<<endl;
    }
    cout<<" :"<<HC[n]<<endl;
}

//string HuffmanCodeToChar(HuffmanCode HC,string code){
//
//
//}

//string CharToHuffmanCode(string str,HuffmanCode HC){
//    string code="";
//    int len = str.length();
//    for(int i=0;i<len;i++){
//        code+=HC[str[i]-'a'+1];
//    }
//    return code;
//}

int main(){
    char ch;
    cin.get(ch);
    cout<<int(ch)<<endl;
    return 0;

}

/*
64
13
22
32
103
21
15
47
57
1
5
32
20
57
63
15
1
48
51
80
23
8
18
1
16
1
168
*/
