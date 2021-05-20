#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream f("mergeheap.in");
ofstream g("mergeheap.out");

struct nod
{
    int inf;
    nod *left, *next;
    nod(int);
};
nod::nod(int n)
{
    this->inf=n;
    this->left=NULL;
    this->next=NULL;
}
class pairing_heap
{
    nod *radacina;
public:
        pairing_heap();
        ~pairing_heap(){this->radacina=NULL;}
        pairing_heap(int);
        int top(){return radacina->inf;}
        nod* mergePH(pairing_heap);
        void push(int);
        void pop();
        void build(vector<int>);
        void displayUtil(nod*);
        void display();
        nod* mergeDelete(nod*);
        nod* mergePH(nod*,nod*);
        void mergeUtil(pairing_heap&);
};
pairing_heap::pairing_heap()
{
    this->radacina=NULL;
}
pairing_heap::pairing_heap(int inf)
{
    this->radacina=new nod(inf);
}
nod* pairing_heap::mergePH(pairing_heap p)
{
    if(this->radacina==NULL)
    {
        this->radacina=p.radacina;
        return this->radacina;
    }
    else if(p.radacina==NULL)
        return this->radacina;
    if(this->radacina->inf>p.radacina->inf)
    {
        //cout<<this->radacina->inf;
        swap(this->radacina,p.radacina);
        //cout<<p.radacina->inf;
    }
    p.radacina->next=this->radacina->left;
    this->radacina->left=p.radacina;
    /*if(this->radacina->inf<p.radacina->inf)
    {
        swap(this->radacina,p.radacina);
    }*/
    p.radacina=NULL;
    return this->radacina;
}
void pairing_heap::push(int n)
{
    this->radacina=this->mergePH(pairing_heap(n));
}
nod* pairing_heap::mergePH(nod* a,nod* b)
{
        if(a==NULL)
        {
            a=b;
            return a;
        }
        if(b==NULL)
            return a;

        if(a->inf>b->inf)
            swap(a,b);

        b->next=a->left;
        a->left=b;

        return a;
}
nod* pairing_heap::mergeDelete(nod *temp)
{
        if(temp==NULL || temp->next==NULL)
            return temp;

        nod *a, *b, *c;

        a=temp;
        b=temp->next;
        c=b->next;

        a->next=b->next=NULL;

        return mergePH(mergePH(a,b),mergeDelete(c));
}
void pairing_heap::pop()
{
    nod *temp=this->radacina;
    this->radacina=mergeDelete(this->radacina->left);
    delete temp;
}
void pairing_heap::build(vector<int>v)
{
    for(auto x:v)
        push(x);
}
void pairing_heap::displayUtil(nod *temp)
{
    if(temp!=NULL)
    {
        if(temp->left!=NULL)
            cout<<"\nStanga lui "<<temp->inf<<" este: "<<temp->left->inf;
        if(temp->next!=NULL)
            cout<<"\nNext lui "<<temp->inf<<" este: "<<temp->next->inf;
        if(temp->left!=NULL)
            displayUtil(temp->left);
        if(temp->next!=NULL)
            displayUtil(temp->next);
    }
}
void pairing_heap::display()
{
    displayUtil(this->radacina);
}
void pairing_heap::mergeUtil(pairing_heap &p)
{
    this->mergePH(p);
    p.radacina=NULL;
}
int main()
{
    pairing_heap a;
    vector<int>v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(7);
    v.push_back(12);
    a.build(v);
    a.push(3);
    a.display();
    cout<<"\n";

    pairing_heap b;
    b.push(4);
    b.push(7);
    b.push(8);
    b.push(9);
    b.display();
    cout<<"\n";
    b.mergeUtil(a);
    b.display();
    cout<<"\n";
    b.pop();
    b.display();
    //a.display();

}
