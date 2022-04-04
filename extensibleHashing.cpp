#include <bits/stdc++.h>
using namespace std;

class bucket
{
    int localDepth, capacity;
    vector<int> b;

public:
    bucket(int localDepth, int capacity);
    int isEmpty();
    int isFull();
    int insert(int);
    int search(int);
    int remove(int);
    int getLocalDepth(void);
    int incrdepth(void);
    int decrdepth(void);
    int display(void);
    vector<int> copy(void);
    void clr(void);
    int getcapacity();
};

bucket::bucket(int localDepth, int capacity)
{
    this->localDepth = localDepth;
    this->capacity = capacity;
}

int bucket::isEmpty()
{
    if (b.capacity() == 0)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int bucket::isFull()
{
    if (b.capacity() == capacity)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int bucket::insert(int n)
{
    if (!isFull())
    {
        b.push_back(n);
        return (1);
    }
    else
    {
        return (0);
    }
}

int bucket::search(int n)
{
    vector<int>::iterator it;
    it = find(b.begin(), b.end(), n);
    if (it != b.end())
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int bucket::remove(int n)
{
    vector<int>::iterator it;
    it = find(b.begin(), b.end(), n);
    if (it != b.end())
    {
        b.erase(it);
        return (1);
    }
    else
    {
        return (0);
    }
}

int bucket::getLocalDepth()
{
    return (localDepth);
}

int bucket::incrdepth()
{
    localDepth++;
    return (localDepth);
}

int bucket::decrdepth()
{
    localDepth--;
    return (localDepth);
}

int bucket::display()
{
    vector<int>::iterator it;
    for (it = b.begin(); it != b.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
    return (1);
}

vector<int> bucket::copy()
{
    vector<int> temp(b.begin(), b.end());
    return (temp);
}

void bucket::clr()
{
    b.clear();
}

int bucket::getcapacity()
{
    return (b.capacity());
}

class directory
{
    int globalDepth, bucketCapacity;
    vector<bucket *> b;
    vector<int> bno;
    int hash(int, int);
    int split(int);
    int pairIndex(int, int);

public:
    directory(int globalDepth, int bucketCapacity);
    int insert(int);
    void display();
    int search(int);
    int remove(int);
};

directory::directory(int globalDepth, int bucketCapacity)
{
    this->globalDepth = globalDepth;
    this->bucketCapacity = bucketCapacity;
    for (int i = 0; i < (1 << globalDepth); i++)
    {
        bno.push_back(i);
        b.push_back(new bucket(globalDepth, bucketCapacity));
    }
}

int directory::hash(int n, int depth)
{
    return (n & ((1 << depth) - 1));
}

int directory::pairIndex(int bucket_no, int depth)
{
    return bucket_no ^ (1 << (depth - 1));
}

int directory::split(int n)
{
    int localDepth, pi, id, d;
    vector<int> temp;
    localDepth = b[n]->incrdepth();
    if (localDepth > globalDepth)
    {
        for (int i = 0; i < (1 << globalDepth); i++)
        {
            b.push_back(b[i]);
        }
        globalDepth++;
    }
    if (globalDepth > 20)
    {
        return (0);
    }
    pi = pairIndex(n, localDepth);
    bno.push_back(pi);
    b[pi] = new bucket(localDepth, bucketCapacity);
    temp = b[n]->copy();
    b[n]->clr();
    id = 1 << localDepth;
    d = 1 << globalDepth;
    for (int i = pi - id; i >= 0; i -= id)
    {
        b[i] = b[pi];
    }
    for (int i = pi + id; i < d; i += id)
    {
        b[i] = b[pi];
    }
    for (auto i = temp.begin(); i != temp.end(); i++)
    {
        insert(*i);
    }
    return (1);
}

int directory::insert(int n)
{
    int no;
    int depth = globalDepth;
    while (depth >= 0)
    {
        no = hash(n, depth);
        auto j = find(bno.begin(), bno.end(), no);
        if (j != bno.end())
        {
            break;
        }
        else
        {
            depth--;
        }
    }
    int con = b[no]->insert(n);
    if (con == 0)
    {
        split(no);
        insert(n);
    }
    return (1);
}

int directory::search(int n)
{

    for (auto i = bno.begin(); i != bno.end(); i++)
    {
        int j = b[*i]->search(n);
        if (j == 1)
        {
            return (*i);
        }
    }
    return (-1);
}

int directory::remove(int n)
{
    int j = search(n);
    if (j != -1)
    {
        b[j]->remove(n);
        return (1);
    }
    return (0);
}

void directory::display()
{
    cout << globalDepth << endl;
    cout << bno.capacity() << endl;
    for (auto i = bno.begin(); i != bno.end(); i++)
    {
        int localDepth = b[*i]->getLocalDepth();
        cout << b[*i]->getcapacity() << " ";
        cout << localDepth << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
    int globalDepth, capacity;
    cin >> globalDepth;
    cin >> capacity;
    
    directory D(globalDepth, capacity);
    
    int choice;
    int key;

    do
    {
        cin >> choice;
        switch (choice)
        {
        case 2:
            cin >> key;
            D.insert(key);
            break;

        case 3:
            cin >> key;
            D.search(key);
            break;

        case 4:
            cin >> key;
            D.remove(key);
            break;

        case 5:
            D.display();
        }
    } while (choice != 6);
    

    return (0);
}
