#include <bits/stdc++.h>
using namespace std;

class page
{
public:
  page(int);
  ~page();

  bool insertData(int, int);
  int search(int);
  int page_status();

private:
  int free_space;
  vector<int> vec;
};

page::page(int cap)
{
  free_space = cap - (4 * 4);
}

page::~page()
{
}

bool page::insertData(int val, int size)
{
  if (free_space - (size + 4) >= 0)
  {
    vec.push_back(val);
    free_space -= (size + 4);
    return true;
  }
  return false;
}

int page::search(int val)
{
  for (int i = 0; i < vec.size(); i++)
  {
    if (vec[i] == val)
    {
      return i;
    }
  }
  return -1;
}

int page::page_status()
{
  return vec.size();
}

class heapfile
{
private:
  int page_size;
  vector<page *> pages;

public:
  heapfile(int);
  ~heapfile();
  bool insert(int, int);
  bool search(int);
  void status();
};

heapfile::heapfile(int pageSizeIn)
{
  page_size = pageSizeIn;
}

heapfile::~heapfile()
{
}

void heapfile::status()
{
  cout << pages.size();
  for (auto i : pages)
  {
    cout << " " << i->page_status();
  }
  cout << endl;
}

bool heapfile::insert(int val, int size)
{
  for (int i = 0; i < pages.size(); i++)
  {
    if (pages[i]->insertData(val, size))
      return true;
  }
  pages.push_back(new page(page_size));
  return insert(val, size);
}

bool heapfile::search(int val)
{
  for (int i = 0; i < pages.size(); i++)
  {
    int stat = pages[i]->search(val);
    if (stat != -1)
    {
      cout << i << " " << stat << endl;
      return true;
    }
  }
  cout << -1 << " " << -1 << endl;
  return false;
}

int main()
{
  int page_size, op_code;
  cin >> page_size;
  heapfile file(page_size);
  while (1)
  {
    cin >> op_code;
    if (op_code == 2)
    {
      file.status();
    }
    else if (op_code == 3)
    {
      int val;
      cin >> val;
      file.search(val);
    }
    else if (op_code == 1)
    {
      int rec_size, primary_key;
      cin >> rec_size >> primary_key;
      file.insert(primary_key, rec_size);
    }
    else if (op_code == 4)
      break;
  }
  return 0;
}
