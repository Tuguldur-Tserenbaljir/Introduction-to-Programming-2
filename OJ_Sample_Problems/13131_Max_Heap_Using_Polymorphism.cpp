#include <iostream>
#include <math.h>
using namespace std;

class MAX_HEAP{
public:
    MAX_HEAP():Count(0){}
    virtual ~MAX_HEAP() {}
    virtual void PUSH(const int &) = 0;
    virtual int MAX() const = 0;
    virtual int POP() = 0;
    int count() const { return Count; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Count;
};

class Array_MAX_HEAP : public MAX_HEAP{
public:
    Array_MAX_HEAP();
    virtual ~Array_MAX_HEAP() {}
    virtual void PUSH(const int &) override; //root node is stored at index 1.
    virtual int MAX() const override;
    virtual int POP() override;

private:
    int array[1025];
};

Array_MAX_HEAP::Array_MAX_HEAP():MAX_HEAP::MAX_HEAP(){}
//Array_MAX_HEAP::~Array_MAX_HEAP() {}
void Array_MAX_HEAP::PUSH(const int &a){
    Count++;
    array[Count] = a;
    for(int i=Count;i>1;i/=2){
        if(array[i] > array[i/2]){
            int temp = array[i];
            array[i] = array[i/2];
            array[i/2] = temp;
        }else{
            return;
        }    
    }
}
 //root node is stored at index 1.
int Array_MAX_HEAP::MAX()const{
    if(Count == 0){
        return -1;
    }
    return array[1];
}
int Array_MAX_HEAP::POP(){
    int return_root = array[1];
    array[1]= array[Count];
    // Count--;
    if(Count == 0){
        return -1;
    }
    else if (Count == 1){
        array[1] = -1;
    }
    else{
        for(int i = 1; i<Count;){
            if(i*2 > Count){
                break;
            }
            else if(i*2+1 > Count){ // if(i*2 == Count){
                if(array[i] > array[2*i]){
                    break;
                }else{
                    int temp = array[i];
                    array[i] = array[i*2];
                    array[i*2] = temp;
                    i = i*2;
                }
            }

            else{
                if(array[2*i] > array[2*i+1]){
                    if(array[2*i] > array[i]){
                        int temp = array[2*i];
                        array[2*i] = array[i];
                        array[i] = temp;
                        i= 2*i;
                    }
                    else{
                        break;
                    }
                }
                else{
                    if(array[2*i+1] > array[i]){
                        int temp = array[2*i+1];
                        array[2*i+1] = array[i];
                        array[i] = temp;
                        i = 2*i+1;
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
    Count--;
    return return_root;
}

class ListNode{
    friend class List_MAX_HEAP; //make List_BST a friend

public:
    ListNode(const int &info):value( info ),left( NULL ),right( NULL ), parent(NULL) //constructor
    {
    }//end ListNode constructor

private:
    int value;
    ListNode *left;
    ListNode *right;
    ListNode *parent;
};//end class ListNode

class List_MAX_HEAP : public MAX_HEAP{
public:
    List_MAX_HEAP();
    virtual ~List_MAX_HEAP()
    {
        deleteTree(root);
    }
    virtual void PUSH(const int &) override;
    virtual int MAX() const override;
    virtual int POP() override;

private:
    ListNode *root;
    /* clean a tree.*/
    void deleteTree(ListNode *root);
    ListNode* findparent(int cnt, ListNode* root){//find the parent of node cnt
        if(cnt <= 1) return root;
        string s = "";
        while(cnt !=0){
            s += cnt%2 +'0';
            cnt/=2;
        }ListNode *now = root;
        for(int i = 1; i < s.size()-1; i++){
            if(s[i] == '0'){
                now = now->left;
            }else{
                now = now->right;
            }
        }return now;
    }
};

void List_MAX_HEAP::deleteTree(ListNode *root){
        if(root == nullptr)return;
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
}
List_MAX_HEAP::List_MAX_HEAP(){
    root = nullptr;
    Count = 0;
}
void List_MAX_HEAP::PUSH(const int &b){
    //ListNode *temp = new ListNode(b);
    if(Count == 0){
        Count++;
        root = new ListNode(b);
    }
    else{
        Count++;
        ListNode *temp = new ListNode(b);
        ListNode *par = this->findparent(this->Count,this->root);
        if(par->left){
            par->right = new ListNode(b);
            temp = par->right;
            temp->parent = par;
        }else{
            par->left = new ListNode(b);
            temp = par->left;
            temp->parent = par; 
        }
            while (temp->parent != nullptr)
            {
                if(temp->value > temp->parent->value){
                    int temp2 = temp->value;
                    temp->value = temp->parent->value;
                    temp->parent->value = temp2;
                    temp = temp->parent;
                }
                else{
                    break;
                }
            }
        }   
    }
int List_MAX_HEAP::MAX() const{
    if(Count == 0){
        return -1;
    }
    return root->value;
}
int List_MAX_HEAP::POP(){
    //int return_value = root->value;
    if(Count == 0) return -1;
    else if(Count == 1) {
        Count = 0;
        int stored_value = root->value;
        root = nullptr;
        return stored_value;
    }
    else{
        ListNode *par = this->findparent(this->Count, this->root);
        int stored_value = root->value;
        if(par->right != nullptr){//there is a right
            root->value = par->right->value;
            par->right = nullptr;
        }
        else if(par->left != nullptr){
            root->value = par->left->value;
            par->left = nullptr;
        }
        ListNode *now = root;
        while(1){
            if(now->right == nullptr && now->left == nullptr){
                Count--;
                return stored_value;
            }
            else if(now->right ==nullptr){
                if(now->left != nullptr){
                     if(now->left->value > now->value){
                        int temp = now->left->value;
                        now->left->value = now->value;
                        now->value = temp;
                        now = now->left;
                    }
                    else{
                        Count--;
                        return stored_value;
                    }
                }
            }
            else if(now->left == nullptr){
                Count--;
                return stored_value;
                }
            else if(now->right != nullptr && now->left != nullptr){
                if(now->left->value > now->right->value){
                    if(now->left->value > now->value){
                        int temp = now->left->value;
                        now->left->value = now->value;
                        now->value = temp;
                        now = now->left;
                    }
                    else{
                        Count--;
                        return stored_value;
                    }
                }
                else if(now->right->value > now->left->value){
                    if(now->right->value > now->value){
                        int temp = now->right->value;
                        now->right->value = now->value;
                        now->value = temp;
                        now = now->right;
                    }
                    else{
                        Count--;
                        return stored_value;
                    }
                }

            }
        }
    }
}