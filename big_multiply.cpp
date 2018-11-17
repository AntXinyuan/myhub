#include <iostream>
#include <cstring>
#include <algorithm>

#define M 100

typedef struct
{
    int s[M];//从高位开始存储数字
    int l;//存储数字长度
    int c;//存储指数
} Node, * pNode;

using namespace std;

void input(Node & num);
void output(Node & num);
void cp(pNode src,pNode des,int st,int l);
void add(pNode pa,pNode pb,pNode ans);
void mul(pNode pa,pNode pb,pNode ans);
int main()
{
    Node a,b,ans;
    input(a);input(b);
    cin.get();
    switch(cin.get())
    {
        case '+':
            add(&a,&b,&ans);break;
        case '*':
            mul(&a,&b,&ans);break;
    }
    output(ans);
    return 0;
}

void input(Node & num)
{
    char * str=new char[1000];
    cin>>str;
    num.c=0,num.l=strlen(str);
    for(int i=0;i<num.l;i++)
        num.s[i]=str[num.l-i-1]-'0';
    delete [] str;

}

void output(Node & num)
{
    for(int i=0;i<num.l;i++)
        cout<<num.s[num.l-i-1];
    for(int i=0;i<num.c;i++)
        cout<<0;
}

void cp(pNode src,pNode des,int st,int l)
{
    int i,j;
    for(i=st,j=0;i<st+l;i++,j++)
        des->s[j]=src->s[i];
    des->l=l;
    des->c=src->c+st;
}

void add(pNode pa,pNode pb,pNode ans)
{
    int alen,blen,len,ta,tb,cc,k,i;
    //cc为进位，ta、tb为本位数字，k为末位补零数
    if(pa->c < pb->c)
    {
        pNode temp=pa;
        pa=pb;
        pb=temp;
    }
    ans->c = pb->c;
    k=pa->c - pb->c;
    alen=pa->l+pa->c;
    blen=pb->l+pb->c;
    len=alen<blen?blen:alen;
    len-=ans->c;
    ans->l=len;
    cc=0;
    for(i=0;i<len;i++)
    {
        if(i<k || i>=pa->l+k)
            ta=0;
        else
            ta=pa->s[i-k];
        if(i<pb->l)
            tb=pb->s[i];
        else
            tb=0;
        ans->s[i]=(ta+tb+cc)%10;
        cc=(ta+tb+cc)/10;
    }
    if(cc)
    {
        ans->s[i]=cc;
        ans->l++;
    }
}

void mul(pNode pa,pNode pb,pNode ans)
{
    int i;
    int ma=pa->l/2,mb=pb->l/2;
    Node al,ah,bl,bh;
    Node t1,t2,t3,t4,z;
    if(!ma || !mb)
    {
        if(!ma)//保证pb是长度为1的
        {
            pNode temp=pa;
            pa=pb;
            pb=temp;
        }
        ans->c=pa->c+pb->c;
        ans->l=pa->l;
        int cc=0;
        for(i=0;i<pa->l;i++)
        {
            ans->s[i]=(pb->s[0]*pa->s[i]+cc)%10;
            cc=(pb->s[0]*pa->s[i]+cc)/10;
        }
        if(cc)
        {
            ans->s[i]=cc;
            ans->l++;
        }
        return;
    }
    cp(pa,&al,0,ma);
    cp(pa,&ah,ma,pa->l-ma);
    cp(pb,&bl,0,mb);
    cp(pb,&bh,mb,pb->l-mb);

    mul(&al,&bl,&t1);
    mul(&al,&bh,&t2);
    mul(&ah,&bl,&t3);
    mul(&ah,&bh,&t4);

    add(&t1,&t2,ans);
    add(ans,&t3,&z);
    add(&z,&t4,ans);
}
