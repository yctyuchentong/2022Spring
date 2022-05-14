#include<iostream>
#include<cstring>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE  100

using namespace std;



typedef int Status;

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
    cout<<"������a-z�Ϳո�ͳ���Ƶ��:"<<endl;
    for(int i=0;i<27;i++){
        cin>>frequency[i];
    }

}

Status InitHuffmanTree(HuffmanTree &HT,int n,int * frequency){
    int m = 2*n-1;
    HT = new HTNode[m+1];
    HT[0].weight = 10000;
    HT[0].lchild = -1;
    HT[0].rchild = -1;
    HT[0].parent = -1;
    for(int i=1;i<n+1;i++){
        HT[i].weight = frequency[i-1];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for(int i=n+1;i<=m;i++){
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    return OK;
}


Status CreateHuffmanTree(HuffmanTree &HT,int n){
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
    return OK;
}


Status CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
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
    return OK;
}

void OutPutHuffmanCode(HuffmanCode HC,int n){
    for(int i=1;i<n;i++){
        cout<<(char)(i-1+'a')<<":"<<HC[i]<<endl;
    }
    cout<<" :"<<HC[n]<<endl;
}

string HuffmanCodeToChar(HuffmanCode HC,string code,int n){
    string str="";
    string curcode = "";
    for(int i=0;i<code.length();i++){
        if(code[i]=='%'){
            return str;
        }
        curcode += code[i];
        for(int i=1;i<=n;i++){
            if(curcode==HC[i]){
                if(i==n){
                    str+=" ";
                }
                else{
                    str+=(char)(i-1+'a');
                }
                curcode="";
            }
        }
    }
    return "����Ĺ�������������";

}

string CharToHuffmanCode(string str,HuffmanCode HC,int n){

    int len = str.length();
    string code="";
    for(int i=0;i<len-1;i++){
        if(str[i]==' '){
            code+=HC[n];
        }else{
            code+=HC[str[i]-'a'+1];
        }

    }
    return code;

}

int main(){
    HuffmanTree HT ;
    int frequency[27];
    int n=27;
    while(1){
        HuffmanCode HC;
        cout << "****************************************************************" << endl;
        cout << "***********   1.����HuffmanTree�Ĳ���           ****************" << endl;
        cout << "***********   2.��ʼ��HuffmanTree����           ****************" << endl;
        cout << "***********   3.����HuffmanTree�ͱ����         ****************" << endl;
        cout << "***********   4.��������                      ****************" << endl;
        cout << "***********   5.������룬������Ϊ�ַ�          ****************" << endl;
        cout << "***********   6.�����ַ�����ʵ��ת��            ****************" << endl;
        cout << "***********   7.�˳�                            ****************" << endl;
        cout << "****************************************************************" << endl;
        cout << "���������ѡ��" ;
        int a;
        cin>>a;
        switch(a){
            case 1:
                InputHaffmanTree(frequency);
                break;
            case 2:
                if(InitHuffmanTree(HT,n,frequency)){
                    cout<<"��ʼ���ɹ�"<<endl;
                }
                else{
                    cout<<"��ʼ��ʧ��"<<endl;
                }
                break;
            case 3:
                if(CreateHuffmanTree(HT,n)){
                    cout<<"Huffman�������ɹ�"<<endl;
                }
                else{
                    cout<<"Huffman������ʧ��"<<endl;
                }
                if(CreateHuffmanCode(HT,HC,n)){
                    cout<<"Huffman���봴���ɹ�"<<endl;

                }else{
                    cout<<"Huffman���봴��ʧ��"<<endl;
                }
                break;
            case 4:
                OutPutHuffmanCode(HC,n);
                break;
            case 5:
                {
                    string code;
                    cout<<"���������������:";
                    cin>>code;
                    cout<<HuffmanCodeToChar(HC,code,n)<<endl;
                    break;
                }
            case 6:{
                string str;
                cout<<"�������ַ���:";
                char ch = cin.get();
                getline(cin,str);
                cout<<str<<endl;
                for(int i=0;i<str.size();i++){
                    str[i] = tolower(str[i]);
                }
                cout<<CharToHuffmanCode(str,HC,n)<<endl;
                break;
            }
            case 7:
                break;
            default:
                cout<<"������������������"<<endl;

        }
    }

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
