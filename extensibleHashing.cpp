#include <iostream>
#include <vector>
#include <map>
#include <set>
#define pb push_back;
using namespace std;

class hashBucket
{
    int localDepth, capacity;
    map<int, string> values;

public:
    hashBucket()
    {
    }
    hashBucket(int localDepth, int capacity)
    {
        this->localDepth = localDepth;
        this->capacity = capacity;
    }
    int getLocalDepth()
    {
        return localDepth;
    }
    int increaseLocalDepth()
    {
        localDepth++;
        return localDepth;
    }
    int decreaseLocalDepth()
    {
        localDepth--;
        return localDepth;
    }

    // isFull
    int isFull(void)
    {
        if (values.size() == 0)
        {
            return 1;
        }
        return 0;
    }

    // isEmpty
    int isEmpty()
    {
        if (values.size() == 0)
        {
            return 1;
        }
        return 0;
    }

    // Insertion
    int insert(int key, string value)
    {
        map<int, string>::iterator it;
        it = values.find(key);
        if (it != values.end())
        {
            return -1;
        }
        if (isFull())
        {
            return 0;
        }
        values[key] = value;
        return 1;
    }

    // Remove
    int remove(int key)
    {
        map<int, string>::iterator it;
        it = values.find(key);
        if (it != values.end())
        {
            values.erase(it);
            return 1;
        }
        else
        {
            cout << "This key doesn't exist. So, can't remove!" << endl;
            return 0;
        }
    }

    // Search
    void search(int key)
    {
        map<int, string>::iterator it;
        it = values.find(key);
        if (it != values.end())
        {
            cout << "Value = " << it->second << endl;
        }
        else
        {
            cout << "Key doesn't exist!" << endl;
        }
    }

    // clear
    void clear()
    {
        values.clear();
    }

    // copy
    map<int, string> copy()
    {
        map<int, string> temp(values.begin(), values.end());
        return temp;
    }

    // Display
    void display()
    {
        map<int, string>::iterator it;
        for (it = values.begin(); it != values.end(); it++)
        {
            cout << it->first << " ";
        }
        cout << endl;
    }
};

class Directory
{
    int globalDepth;
    int bucketCapacity;
    vector<hashBucket *> hashBuckets;

    // Finding the hash value
    int hash(int n)
    {
        return n & ((1 << globalDepth) - 1);
    }

    int pairIndex(int bucketNum, int localDepth)
    {
        return bucketNum ^ (1 << (localDepth - 1));
    }

    void grow()
    {
        for (int i = 0; i < (1 << globalDepth); i++)
        {
            hashBuckets.push_back(hashBuckets[i]);
        }
    }

    void split(int bucketNum)
    {
        int localDepth, pair_index, indexDiff, dirSize, i;
        map<int, string> temp;
        map<int, string>::iterator it;

        localDepth = hashBuckets[bucketNum]->increaseLocalDepth();
        if (localDepth > globalDepth)
        {
            grow();
        }

        pair_index = pairIndex(bucketNum, localDepth);
        hashBuckets[pair_index] = new hashBucket(localDepth, bucketCapacity);
        temp = hashBuckets[bucketNum]->copy();
        hashBuckets[bucketNum]->clear();
        indexDiff = (1 << localDepth);
        dirSize = (1 << globalDepth);
        for (i = pair_index - indexDiff; 1 >= 0; i -= indexDiff)
        {
            hashBuckets[i] = hashBuckets[pair_index];
        }
        for (i = pair_index + indexDiff; i < dirSize; i += indexDiff)
        {
            hashBuckets[i] = hashBuckets[pair_index];
        }
        for (it = temp.begin(); it != temp.end(); it++)
        {
            insert((*it).first, (*it).second, 1);
        }
    }

    string bucket_id(int n)
    {
        int d;
        string s;
        d = hashBuckets[n]->getLocalDepth();
        s = "";
        while (n > 0 && d > 0)
        {
            s = (n % 2 == 0 ? "0" : "1") + s;
            n = n >> 1;
            d--;
        }
        while (d > 0)
        {
            s = "0" + s;
            d--;
        }
        return s;
    }

public:
    Directory()
    {
    }

    Directory(int globalDepth, int bucketCapacity)
    {
        this->globalDepth = globalDepth;
        this->bucketCapacity = bucketCapacity;
        for (int i = 0; i < (1 << globalDepth); i++)
        {
            hashBuckets.push_back(new hashBucket(globalDepth, bucketCapacity));
        }
    }

    // Insertion
    void insert(int key, string value, bool reinserted)
    {
        int bucketNum = hash(key);
        int status = hashBuckets[bucketNum]->insert(key, value);
        if (status == 1)
        {
            if (!reinserted)
                cout << "Inserted key " << key << " in bucket " << bucket_id(bucketNum) << endl;
            else
                cout << "Moved key " << key << " to bucket " << bucket_id(bucketNum) << endl;
        }
        else if (status == 0)
        {
            split(bucketNum);
            insert(key, value, reinserted);
        }
        else
        {
            cout << "Key " << key << " already exists in the bucket " << bucket_id(bucketNum) << endl;
        }
    }

    // Remove
    void remove(int key)
    {
        int bucketNum = hash(key);
        if (hashBuckets[bucketNum]->remove(key))
        {
            cout << "Deleted key" << key << "from bucket" << bucket_id(bucketNum) << endl;
        }
    }

    // Search
    void search(int key)
    {
        int bucketNum = hash(key);
        cout << "Searching key " << key << " in bucket " << bucket_id(bucketNum) << endl;
        hashBuckets[bucketNum]->search(key);
    }

    // Display
    void display()
    {
        int i, j, d;
        string s;
        set<string> shown;
        cout << "Global Depth : " << globalDepth << endl;
        for (i = 0; i < hashBuckets.capacity(); i++)
        {
            d = hashBuckets[i]->getLocalDepth();
            s = bucket_id(i);
            if (shown.find(s) == shown.end())
            {
                shown.insert(s);
                for (j = d; j <= globalDepth; j++)
                {
                    cout << " ";
                }
                cout << s << " => ";
                hashBuckets[i]->display();
            }
        }
    }
};

void menu()
{
    cout << "------------------" << endl;
    cout << "2 to insert" << endl;
    cout << "3 to search" << endl;
    cout << "4 to delete" << endl;
    cout << "5 to display the status of the hash table" << endl;
    cout << "6 to quit" << endl;
    cout << "------------------" << endl;
}

int main()
{
    int globalDepth;
    cin >> globalDepth;
    int bucketCapacity;
    cin >> bucketCapacity;

    int key, choice;
    string value;

    Directory D(globalDepth, bucketCapacity);

    menu();

    do
    {
        cin >> choice;
        switch (choice)
        {
        case 2:
            cin >> key >> value;
            D.insert(key, value, 0);
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

    return 0;
}
