#include <iostream>
#include <algorithm>

#define _Wait() std::cout << "\nPress enter to continue..."; std::cin.get()
#define _New(count) for (int i = 0; i < count; i++) std::cout << '\n';

template<typename Object>
struct TreeNode
{
    TreeNode() : element{ Object{  } }, firstChild{ nullptr }, nextSibling{ nullptr }, isRead{ false } {}

    TreeNode(Object&& elm, TreeNode* child = nullptr, TreeNode* sib = nullptr) : element{ std::move(elm) }, firstChild{ child }, nextSibling{ sib }, isRead{ false } {}

    Object element;
    TreeNode* firstChild;
    TreeNode* nextSibling;

    bool isRead;
};

int Introduction()
{
    TreeNode<int> A { 1, nullptr, nullptr };
    TreeNode<int> B { 2, nullptr, nullptr };
    TreeNode<int> C { 3, nullptr, nullptr };
    TreeNode<int> D { 4, nullptr, nullptr };
    TreeNode<int> E { 5, nullptr, nullptr };
    TreeNode<int> F { 6, nullptr, nullptr };
    TreeNode<int> G { 7, nullptr, nullptr };
    TreeNode<int> H { 8, nullptr, nullptr };

    TreeNode<int>* stack[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    int top = -1;

    int treeSize = 8;

    A.firstChild  = &B;
    B.nextSibling = &C;
    C.firstChild  = &D;
    D.nextSibling = &E;
    C.nextSibling = &F;
    F.nextSibling = &G;
    G.firstChild  = &H;

    TreeNode<int>* itr = &A;

    //while (itr != nullptr)
    //{
    //    std::cout << itr->element << "\n";
    //   
    //    if (itr->nextSibling == nullptr)
    //        itr = itr->firstChild;
    //    else itr = itr->nextSibling;
    //}

    while (itr != nullptr)
    {
        if (!itr->isRead)
            std::cout << itr->element << "\n";
        

        if (itr->firstChild != nullptr)
        {
            stack[++top] = itr;
            if (!itr->isRead)
            {
                itr->isRead = true;
                itr = itr->firstChild;
            }
            else itr = itr->nextSibling;
        }
        else if (itr->nextSibling != nullptr)
        {
            itr = itr->nextSibling;
        }
        else
        {
            itr = stack[top];
            stack[top] = nullptr;
            top--;
        }
     
    }

    _New(2);
    _Wait();
    return 0;
}

