#include <bits/stdc++.h>

using namespace std;

class node
{
    bool isleaf;
    vector<int> keys;
    vector<node *> ptr;
    friend class bptree;
};

class bptree
{
    int dsize, isize;
    node *root;
    int ci = 0, cd = 0;
    void insertinternal(int, node *, node *);
    node *findparent(node *, node *);
    void dis(node *);

public:
    bptree(int dsize, int isize);
    int insert(int);
    void display();
};

bptree::bptree(int dsize, int isize)
{
    this->dsize = dsize;
    this->isize = isize;
    root = nullptr;
}

node *bptree::findparent(node *cursor, node *child)
{
    node *parent;
    if (cursor->isleaf || cursor->ptr[0]->isleaf)
    {
        return (nullptr);
    }
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }
        else
        {
            parent = findparent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

void bptree::insertinternal(int n, node *cursor, node *newleaf)
{
    if (cursor->keys.size() < 2 * isize + 1)
    {
        node *dump = new node;
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i + 1] = newleaf;
    }
    else
    {
        node *newinter = new node;
        cursor->keys.push_back(n);
        node *dump = new node;
        newinter->isleaf = false;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = find(cursor->keys.begin(), cursor->keys.end(), n);
        int i1 = it - cursor->keys.begin();
        cursor->ptr.push_back(dump);
        for (int j = cursor->ptr.size() - 1; j > i1 + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->ptr[i1 + 1] = newleaf;
        auto k = cursor->keys.begin() + isize + 1;
        for (auto i = k; i != cursor->keys.end(); i++)
        {
            newinter->keys.push_back(*i);
        }

        cursor->keys.erase(k, cursor->keys.end());
        k = cursor->keys.begin() + isize;
        int no = *k;
        cursor->keys.erase(k);

        auto it2 = cursor->ptr.begin() + isize + 1;
        for (auto i = it2; i != cursor->ptr.end(); i++)
        {
            newinter->ptr.push_back(*i);
        }
        cursor->ptr.erase(it2, cursor->ptr.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(no);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newinter);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(no, findparent(root, cursor), newinter);
        }
        ci++;
    }
}

int bptree::insert(int n)
{
    if (root == nullptr)
    {
        root = new node();
        root->keys.push_back(n);
        root->isleaf = true;
        cd++;
        return (1);
    }
    node *cursor = root;
    node *parent;
    while (cursor->isleaf == false)
    {
        parent = cursor;
        for (int i = 0; i < cursor->keys.size(); i++)
        {
            if (n < cursor->keys[i])
            {
                cursor = cursor->ptr[i];
                break;
            }
            if (i == cursor->keys.size() - 1)
            {
                cursor = cursor->ptr[i + 1];
                break;
            }
        }
    }
    if (cursor->keys.size() < 2 * dsize)
    {
        cursor->keys.push_back(n);
        sort(cursor->keys.begin(), cursor->keys.end());
    }
    else
    {
        node *newleaf = new node;
        cursor->keys.push_back(n);
        newleaf->isleaf = true;
        sort(cursor->keys.begin(), cursor->keys.end());
        auto it = cursor->keys.begin() + dsize;
        for (auto i = it; i != cursor->keys.end(); i++)
        {
            newleaf->keys.push_back(*i);
        }
        cursor->keys.erase(it, cursor->keys.end());
        if (cursor == root)
        {
            node *newroot = new node;

            newroot->keys.push_back(newleaf->keys[0]);
            newroot->ptr.push_back(cursor);
            newroot->ptr.push_back(newleaf);
            newroot->isleaf = false;
            root = newroot;
            ci++;
        }
        else
        {
            insertinternal(newleaf->keys[0], parent, newleaf);
        }
        cd++;
    }
    return (1);
}

void bptree::display()
{
    cout << ci << " " << cd << " ";
    for (auto i = root->keys.begin(); i != root->keys.end(); i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;
}

/*void bptree::dis(node *cursor)
{
    for (int i = 0; i < cursor->keys.size(); i++)
    {
        cout << cursor->keys[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < cursor->ptr.size(); i++)
    {
        dis(cursor->ptr[i]);
    }
}

void bptree::display()
{
    dis(root);
}*/

int main()
{
    int d, t;
    cin >> d;
    cin >> t;

    bptree bp(d, t);

    int mode;
    int j;
    while (mode != 3)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> j;
            bp.insert(j);
        }
        else if (mode == 2)
        {
            bp.display();
        }
    }
    /*bptree bp(2, 1);
    bp.insert(100);
    bp.insert(200);
    bp.insert(300);
    bp.insert(400);
    // bp.display();
    bp.insert(500);
    // bp.display();
    bp.insert(600);
    bp.insert(700);
    // bp.display();
    bp.insert(850);
    bp.insert(150);
    bp.insert(350);
    bp.insert(250);
    // bp.display();
    bp.insert(251);
    // bp.display();
    bp.insert(252);
    bp.insert(253);
    bp.insert(851);
    bp.insert(401);
    bp.insert(402);
    bp.display(); */
    return (0);
}


/* Reference Code
// C++ program for implementing B+ Tree
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int MAX = 3;

// BP node
class Node
{
    bool IS_LEAF;
    int *key, size;
    Node **ptr;
    friend class BPTree;

public:
    Node();
};

// BP tree
class BPTree
{
    Node *root;
    void insertInternal(int,
                        Node *,
                        Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node *);
    Node *getRoot();
};

// Constructor of Node
Node::Node()
{
    key = new int[MAX];
    ptr = new Node *[MAX + 1];
}

// Initialise the BPTree Node
BPTree::BPTree()
{
    root = NULL;
}

// Function to find any element
// in B+ Tree
void BPTree::search(int x)
{

    // If tree is empty
    if (root == NULL)
    {
        cout << "Tree is empty\n";
    }

    // Traverse to find the value
    else
    {

        Node *cursor = root;

        // Till we reach leaf node
        while (cursor->IS_LEAF == false)
        {

            for (int i = 0;
                 i < cursor->size; i++)
            {

                // If the element to be
                // found is not present
                if (x < cursor->key[i])
                {
                    cursor = cursor->ptr[i];
                    break;
                }

                // If reaches end of the
                // cursor node
                if (i == cursor->size - 1)
                {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        // Traverse the cursor and find
        // the node with value x
        for (int i = 0;
             i < cursor->size; i++)
        {

            // If found then return
            if (cursor->key[i] == x)
            {
                cout << "Found\n";
                return;
            }
        }

        // Else element is not present
        cout << "Not found\n";
    }
}

// Function to implement the Insert
// Operation in B+ Tree
void BPTree::insert(int x)
{

    // If root is null then return
    // newly created node
    if (root == NULL)
    {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    }

    // Traverse the B+ Tree
    else
    {
        Node *cursor = root;
        Node *parent;

        // Till cursor reaches the
        // leaf node
        while (cursor->IS_LEAF == false)
        {

            parent = cursor;

            for (int i = 0;
                 i < cursor->size;
                 i++)
            {

                // If found the position
                // where we have to insert
                // node
                if (x < cursor->key[i])
                {
                    cursor = cursor->ptr[i];
                    break;
                }

                // If reaches the end
                if (i == cursor->size - 1)
                {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }

        if (cursor->size < MAX)
        {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
            {
                i++;
            }

            for (int j = cursor->size;
                 j > i; j--)
            {
                cursor->key[j] = cursor->key[j - 1];
            }

            cursor->key[i] = x;
            cursor->size++;

            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }

        else
        {

            // Create a newLeaf node
            Node *newLeaf = new Node;

            int virtualNode[MAX + 1];

            // Update cursor to virtual
            // node created
            for (int i = 0; i < MAX; i++)
            {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;

            // Traverse to find where the new
            // node is to be inserted
            while (x > virtualNode[i] && i < MAX)
            {
                i++;
            }

            // Update the current virtual
            // Node to its previous
            for (int j = MAX + 1;
                 j > i; j--)
            {
                virtualNode[j] = virtualNode[j - 1];
            }

            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;

            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;

            cursor->ptr[cursor->size] = newLeaf;

            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];

            cursor->ptr[MAX] = NULL;

            // Update the current virtual
            // Node's key to its previous
            for (i = 0;
                 i < cursor->size; i++)
            {
                cursor->key[i] = virtualNode[i];
            }

            // Update the newLeaf key to
            // virtual Node
            for (i = 0, j = cursor->size;
                 i < newLeaf->size;
                 i++, j++)
            {
                newLeaf->key[i] = virtualNode[j];
            }

            // If cursor is the root node
            if (cursor == root)
            {

                // Create a new Node
                Node *newRoot = new Node;

                // Update rest field of
                // B+ Tree Node
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else
            {

                // Recursive Call for
                // insert in internal
                insertInternal(newLeaf->key[0],
                               parent,
                               newLeaf);
            }
        }
    }
}

// Function to implement the Insert
// Internal Operation in B+ Tree
void BPTree::insertInternal(int x,
                            Node *cursor,
                            Node *child)
{

    // If we doesn't have overflow
    if (cursor->size < MAX)
    {
        int i = 0;

        // Traverse the child node
        // for current cursor node
        while (x > cursor->key[i] && i < cursor->size)
        {
            i++;
        }

        // Traverse the cursor node
        // and update the current key
        // to its previous node key
        for (int j = cursor->size;
             j > i; j--)
        {

            cursor->key[j] = cursor->key[j - 1];
        }

        // Traverse the cursor node
        // and update the current ptr
        // to its previous node ptr
        for (int j = cursor->size + 1;
             j > i + 1; j--)
        {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }

        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }

    // For overflow, break the node
    else
    {

        // For new Interval
        Node *newInternal = new Node;
        int virtualKey[MAX + 1];
        Node *virtualPtr[MAX + 2];

        // Insert the current list key
        // of cursor node to virtualKey
        for (int i = 0; i < MAX; i++)
        {
            virtualKey[i] = cursor->key[i];
        }

        // Insert the current list ptr
        // of cursor node to virtualPtr
        for (int i = 0; i < MAX + 1; i++)
        {
            virtualPtr[i] = cursor->ptr[i];
        }

        int i = 0, j;

        // Traverse to find where the new
        // node is to be inserted
        while (x > virtualKey[i] && i < MAX)
        {
            i++;
        }

        // Traverse the virtualKey node
        // and update the current key
        // to its previous node key
        for (int j = MAX + 1;
             j > i; j--)
        {

            virtualKey[j] = virtualKey[j - 1];
        }

        virtualKey[i] = x;

        // Traverse the virtualKey node
        // and update the current ptr
        // to its previous node ptr
        for (int j = MAX + 2;
             j > i + 1; j--)
        {
            virtualPtr[j] = virtualPtr[j - 1];
        }

        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;

        cursor->size = (MAX + 1) / 2;

        newInternal->size = MAX - (MAX + 1) / 2;

        // Insert new node as an
        // internal node
        for (i = 0, j = cursor->size + 1;
             i < newInternal->size;
             i++, j++)
        {

            newInternal->key[i] = virtualKey[j];
        }

        for (i = 0, j = cursor->size + 1;
             i < newInternal->size + 1;
             i++, j++)
        {

            newInternal->ptr[i] = virtualPtr[j];
        }

        // If cursor is the root node
        if (cursor == root)
        {

            // Create a new root node
            Node *newRoot = new Node;

            // Update key value
            newRoot->key[0] = cursor->key[cursor->size];

            // Update rest field of
            // B+ Tree Node
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }

        else
        {

            // Recursive Call to insert
            // the data
            insertInternal(cursor->key[cursor->size],
                           findParent(root,
                                      cursor),
                           newInternal);
        }
    }
}

// Function to find the parent node
Node *BPTree::findParent(Node *cursor,
                         Node *child)
{
    Node *parent;

    // If cursor reaches the end of Tree
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
    {
        return NULL;
    }

    // Traverse the current node with
    // all its child
    for (int i = 0;
         i < cursor->size + 1; i++)
    {

        // Update the parent for the
        // child Node
        if (cursor->ptr[i] == child)
        {
            parent = cursor;
            return parent;
        }

        // Else recursively traverse to
        // find child node
        else
        {
            parent = findParent(cursor->ptr[i],
                                child);

            // If parent is found, then
            // return that parent node
            if (parent != NULL)
                return parent;
        }
    }

    // Return parent node
    return parent;
}

// Function to get the root Node
Node *BPTree::getRoot()
{
    return root;
}

// Driver Code
int main()
{
    BPTree node;

    // Create B+ Tree
    node.insert(6);
    node.insert(16);
    node.insert(26);
    node.insert(36);
    node.insert(46);

    // Function Call to search node
    // with value 16
    node.search(16);

    return 0;
}

*/
