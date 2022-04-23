#include <iostream>

using namespace std;
template<class T>
class BSTNODE
{
public:
    T data;
    BSTNODE* left;
    BSTNODE* right;
    BSTNODE* parent;
    int color;
    BSTNODE()
    {
        left=right=parent=0;

    }
    BSTNODE(T& key,BSTNODE<T>* left=0,BSTNODE<T>* right=0,BSTNODE<T>* p=0)
    {
        this->data=key;
        this->left=left;
        this->right=right;
        this->parent=p;
    }
};
template<class T>
class rbt
{
    BSTNODE<T>* root;
public:
    rbt()
    {
        root=0;
    }
    void BSTinsert(BSTNODE<T>*& node)
    {
        BSTNODE<T>* cur=root,*prev=0;
        while(cur!=0)
        {
            prev=cur;
            if(node->data>cur->data)
                cur=cur->right;
            else
                cur=cur->left;
        }
        if(root==0)
            root=node;
        else if(node->data>prev->data)
            prev->right=node;
        else
            prev->left=node;

        node->parent=prev;
    }
    void leftrotate(BSTNODE<T>*& x)
    {
        BSTNODE<T>* y=x->right,*r;
        r=y->left;
        x->right=r;
        if(x->right!=0)
            x->right->parent=x;
        y->parent=x->parent;
        if(x->parent==0)
            root=y;
        else if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
        y->left=x;
        x->parent=y;
    }
    void rightrotate(BSTNODE<T>*& y)
    {
        BSTNODE<T>* x=y->left,*l;
        l=x->right;
        y->left=l;
        if(y->left!=0)
            y->left->parent=y;
        x->parent=y->parent;

        if(y->parent==0)
            root=x;
        else if(y==y->parent->left)
            y->parent->left=x;
        else
            y->parent->right=x;
        x->right=y;
        y->parent=x;
    }
    void insert(T d)
    {
        BSTNODE<T>* x=new BSTNODE<T>(d);
        BSTinsert(x);
        x->color=0;
        while(x!=root&&x->parent->color==0&&x->color==0)
        {
            BSTNODE<T>*p=x->parent,*Grand=x->parent->parent;
            if(x->parent==x->parent->parent->left)
            {

                BSTNODE<T>* y=x->parent->parent->right;
                if(y!=0&&y->color==0)
                {
                    y->color=1;
                    x->parent->color=1;
                    x->parent->parent->color=0;
                    x=x->parent->parent;
                }
                else  ///y->color is black
                {
                    if(x==x->parent->right)
                    {
                        x=x->parent;
                        leftrotate(p);
                    }
                    x->parent->color=1;
                    x->parent->parent->color=0;
                    rightrotate(Grand);
                    x=x->parent;
                }
            }
            else
            {
                BSTNODE<T>* y=x->parent->parent->left;
                if(y!=0&&y->color==0)
                {
                    y->color=1;
                    x->parent->color=1;
                    x->parent->parent->color=0;
                    x=x->parent->parent;
                }
                else  ///y->color is black
                {
                    if(x==x->parent->left)
                    {
                        x=x->parent;
                        rightrotate(p);
                    }
                    x->parent->color=1;
                    x->parent->parent->color=0;
                    leftrotate(Grand);
                    x=x->parent;
                }
            }
        }
        if(root->color==0)
        {
            root->color=1;
        }
    }
    BSTNODE<T>* Find(T d)
    {
        BSTNODE<T>*cur=root;
        while(cur->data!=d)
        {
            if(d>cur->data)
                cur=cur->right;
            else
                cur=cur->left;
        }
        return cur;
    }
    BSTNODE<T>* successor(BSTNODE<T>* s)
    {
        BSTNODE<T>*l=s->right;
        while(l->left!=0)
        {
            l=l->left;
        }
        return l;
    }
    void DeleteRBT(T d)
    {
        BSTNODE<T>*cur=Find(d);///making it leaf node
        while(cur->right!=0||cur->left!=0)
        {
            if(cur->right==0&&cur->left!=0)
            {
                swap(cur->data,cur->left->data);
                cur=cur->left;
            }
            else if(cur->right!=0&&cur->left==0)
            {
                swap(cur->data,cur->right->data);
                cur=cur->right;
            }
            else
            {
                BSTNODE<T>*k=successor(cur);
                swap(k->data,cur->data);
                cur=k;
            }
        }///case 1 red node
        if(cur->color==0)
        {
            cur->parent->right=cur->right;
            cur->parent->left=cur->left;
            delete cur;
            return;
        }///case 2 black node
        BSTNODE<T>*del=cur;
        cur->color=2;///double black
        BSTNODE<T>*y;
        do
        {
            if(cur==cur->parent->left)
                y=cur->parent->right;
            else
                y=cur->parent->left;
            if(y==0||y->color==1)
            {
                if(y==0)
                {
                    cur->color=1;
                    if(cur->parent->color==1)
                    {
                        cur->parent->color=2;
                        cur=cur->parent;///double black
                    }
                    else
                        cur->parent->color=1;
                }
                else if((y->left==0&&y->right==0)||(y->right->color==1&&y->left->color==1))
                {
                    cur->color=1;
                    if(cur->parent->color==1)
                    {
                        cur->parent->color=2;
                        cur=cur->parent;///double black
                    }
                    else
                        cur->parent->color=1;
                    y->color=0;

                }
                else if((cur==cur->parent->left)&&((y->right==0&&y->left->color==0)||(y->right->color==1&&y->left->color==0)))
                {
                    swap(y->left->color,y->color);
                    rightrotate(y);
                }
                else if((cur==cur->parent->left)&&((y->left==0&&y->right->color==0)||(y->left->color==1&&y->right->color==0)))
                {
                    swap(y->parent->color,y->color);
                    leftrotate(y->parent);
                    cur->color=1;
                    y->right->color=1;

                }
                else if((cur==cur->parent->right)&&((y->right==0&&y->left->color==0)||(y->right->color==1&&y->left->color==0)))
                {
                    swap(y->parent->color,y->color);
                    rightrotate(y->parent);
                    cur->color=1;
                    y->left->color=1;
                }
                else if((cur==cur->parent->right)&&((y->left==0&&y->right->color==0)||(y->left->color==1&&y->right->color==0)))
                {
                    swap(y->right->color,y->color);
                    leftrotate(y);
                }else if((cur==cur->parent->left)&&(y->right->color==0&&y->left->color==0)){
                    swap(y->left->color,y->color);
                    rightrotate(y);
                }else if((cur==cur->parent->right)&&(y->right->color==0&&y->left->color==0)){
                    swap(y->right->color,y->color);
                    leftrotate(y);
                }
            }
            else if(y!=0&&y->color==0)
            {
                swap(cur->parent->color,y->color);
                if(cur==cur->parent->left)
                    leftrotate(cur->parent);
                else
                    rightrotate(cur->parent);
            }
            if(cur==root)cur->color=1;
        }
        while(cur->color==2);
        if(del==del->parent->left)
            del->parent->left=0;
        else
            del->parent->right=0;
        delete del;
    }
    void inorder(BSTNODE<T>* p)
    {
        if(p!=0)
        {
            inorder(p->left);
            cout<<p->data<<" ";
            if(p->color==1)
                cout<<"BLACK"<<endl;
            else if(p->color==0)
                cout<<"RED"<<endl;
            inorder(p->right);
        }
    }
    void ClearAll(BSTNODE<T>* p){
     if(p!=0)
        {
            ClearAll(p->left);
            ClearAll(p->right);
            delete p;
        }

    }
    void Clear(){
    ClearAll(root);
    }
    void print()
    {
        inorder(root);
    }
};

int main()
{
    rbt<int> a;
    a.insert(47);
    a.insert(32);
    a.insert(71);
    a.insert(65);
    a.insert(93);
    a.insert(87);
    a.insert(82);
    a.DeleteRBT(32);
    a.DeleteRBT(65);
    //a.Clear();
    a.print();
    return 0;
}
