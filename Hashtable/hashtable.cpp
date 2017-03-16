/***********************************************************************
 *  Copyright(c) 2015-2016 西北农林科技大学.
 *  All rights reserved.
 *
 *  文件名称：hashtable.cpp
 *  简要描述：该源文件中包含Node结构体和HashTable类的实现。
 *
 *  当前版本：1.0
 *  作者/修改者：刘朝洋
 *  完成日期：2016年1月4日
 * ***********************************************************************/
#include "hashtable.h"

int avglength = 0;      //计算平均搜索长度

/******************************struct Node**************************************/
//构造函数
Node::Node(string sname, string sage, string sphoneNumber,
           string ssex, string s_class, Node *r, Node *d)
{
    data.name = sname;
    data.age = sage;
    data.phoneNumber = sphoneNumber;
    data.sex = ssex;
    data._class = s_class;
    rightlink = r;
    downlink = d;
}
Node::Node()
    :rightlink(NULL), downlink(NULL)
{
}
Node::~Node()
{
}
/*********************************class HashTable*******************************/
HashTable::HashTable(int d, int l)
{
    divisor = d;
    length = l;
    nameHashTable = new Node [l];
    numHashTable = new Node [l];

    for (int i = 0; i < length; i++)
    {
        nameHashTable[i].rightlink = NULL;
        nameHashTable[i].leftlink = NULL;
        nameHashTable[i].downlink = NULL;
        nameHashTable[i].uplink = NULL;
        numHashTable[i].rightlink = NULL;
        numHashTable[i].leftlink = NULL;
        numHashTable[i].uplink = NULL;
        numHashTable[i].downlink = NULL;
    }
}
//DEK Hash Function
unsigned int HashTable::DEKHash(const std::string& str)
{
   unsigned int hash = static_cast<unsigned int>(str.length());

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ str[i];
   }

   return hash;
}
//PJW Hash Function
unsigned int HashTable::PJWHash(const std::string& str)
{
   unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   unsigned int HighBits          = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash              = 0;
   unsigned int test              = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << OneEighth) + str[i];

      if((test = hash & HighBits)  != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }
   return hash;
}
//DJB Hash Function
unsigned int HashTable::DJBHash(const std::string& str)
{
   unsigned int hash = 5381;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = ((hash << 5) + hash) + str[i];
   }

   return hash;
}
//BPH Hash Function
unsigned int HashTable::BPHash(const std::string& str)
{
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = hash << 7 ^ str[i];
   }

   return hash;
}
//FNV Hash Function
unsigned int HashTable::FNVHash(const std::string& str)
{
   const unsigned int fnv_prime = 0x811C9DC5;
   unsigned int hash = 0;
   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash *= fnv_prime;
      hash ^= str[i];
   }

   return hash;
}

//ELF Hash Function
unsigned int HashTable::ELFHash(const std::string& str)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

//APH Hash Function
unsigned int HashTable::APHash(const std::string& str)
{
   unsigned int hash = 0xAAAAAAAA;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }

   return hash;
}

unsigned int HashTable::MYHash(const string& str)
{
    unsigned int hash = 0;

    if (str.length() != 11)
    {
        for (unsigned int i = 0; i < str.length(); i++)
        {
            hash += (unsigned int) str[i];
        }
        hash += str.length();
    }
    else
    {
        hash = (str[1] - 48) * 100000 + (str[2] - 48) * 10000 + (str[4] - 48) * 1000
                    + (str[5] - 48) * 100 + (str[8] - 48)  * 10 + str[9] - 48;
    }
    return hash;
}

unsigned int HashTable::SDBMHash(const std::string& str)
{
   unsigned int hash = 0;

   for(std::size_t i = 0; i < str.length(); i++)
   {
      hash = str[i] + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int HashTable::Encode(string &n)
{
    unsigned int k = 0;

    //k = MYHash(n);
    k = DJBHash(n);
    //k = PJWHash(n);
    //k = DEKHash(n);
    //k = SDBMHash(n);
    //k = ELFHash(n);

    return k;
}

void HashTable::add(string sname, string sage, string sphoneNumber,
                    string ssex, string s_class)
{
    unsigned int j1 = Encode(sname) % divisor;
    unsigned int j2 = Encode(sphoneNumber) % divisor;
    Node *p = new Node(sname, sage, sphoneNumber, ssex, s_class);

    p->rightlink = nameHashTable[j1].rightlink;
    p->leftlink = &nameHashTable[j1];
    if (nameHashTable[j1].rightlink != NULL)
    {
        p->rightlink->leftlink = p;
    }
    nameHashTable[j1].rightlink = p;
    p->downlink = numHashTable[j2].downlink;
    p->uplink = &numHashTable[j2];
    if (numHashTable[j2].downlink != NULL)
    {
        p->downlink->uplink = p;
    }
    numHashTable[j2].downlink = p;
}
bool HashTable::nameSearch(string sname)
{
    unsigned int k  = Encode(sname);
    unsigned int j = k % divisor;
    bool flag = false;      //判断是否搜索到的标志
    Node *p = &nameHashTable[j];
    //if (p != NULL)
    while (p->rightlink != NULL)
    {
        p=p->rightlink;
        avglength++;
        if(p->data.name == sname)
        {
            //cout<< p->data.name << " " << p->data.age <<" "
             // << p->data.phoneNumber << " " << p->data.sex <<" "
            //<< p->data._class << endl;
            flag = true;
        }
    }
    if (!flag)
    {
        cout <<"不存在该联系人！"<< endl;
        return false;
    }
    else
    {
        return true;
    }
}
bool HashTable::phoneNumberSearch(string sphoneNumber)
{
    unsigned int k  = Encode(sphoneNumber);
    unsigned int j = k % divisor;
    bool flag = false;
    Node *p = &numHashTable[j];

    while (p->downlink != NULL)
    {
        p=p->downlink;
        avglength++;
        if(p->data.phoneNumber == sphoneNumber)
        {
            //cout << p->data.name << " " << p->data.age << " "
             //<< p->data.phoneNumber << " " << p->data.sex << " "
            //<< p->data._class<< endl;
            flag = true;
        }
    }
    if (!flag)
    {
        cout <<"不存在该联系人！"<< endl;
        return false;
    }
    else
    {
        return true;
    }
}

void HashTable::nameRemove(string sname)
{
    unsigned int k  = Encode(sname);
    unsigned int j = k % divisor;
    bool flag = false;
    Node *p = &nameHashTable[j];
    while (p->rightlink != NULL)
    {
        p = p->rightlink;
        Node *t = p;
        if(p->data.name == sname)
        {
            t->leftlink->rightlink = t->rightlink;
            t->uplink->downlink = t->downlink;
            if (t->rightlink != NULL)
            {
                t->rightlink->leftlink = t->leftlink;
            }
            if (t->downlink != NULL)
            {
                t->downlink->uplink = t->uplink;
            }
            t->rightlink = NULL;
            t->downlink = NULL;
            t->leftlink = NULL;
            t->uplink = NULL;
            delete t;
            flag = true;
        }
    }
    if (!flag)
    {
        cout <<"不存在该联系人！"<< endl;
    }
}

void HashTable::phoneNumberRemove(string sphoneNumber)
{
    unsigned int k  = Encode(sphoneNumber);
    unsigned int j = k % divisor;
    bool flag = false;
    Node *p = &numHashTable[j];
    while (p->downlink != NULL)
    {
        p = p->downlink;
        Node *t = p;
        if(p->data.phoneNumber == sphoneNumber)
        {
            t->leftlink->rightlink = t->rightlink;
            t->uplink->downlink = t->downlink;
            if (t->rightlink != NULL)
            {
                t->rightlink->leftlink = t->leftlink;
            }
            if (t->downlink != NULL)
            {
                t->downlink->uplink = t->uplink;
            }
            t->rightlink = NULL;
            t->downlink = NULL;
            t->leftlink = NULL;
            t->uplink = NULL;
            delete t;
            flag = true;
        }
    }
    if (!flag)
    {
        cout <<"不存在该联系人！"<< endl;
    }
}

void HashTable::fileRead()
{
    ifstream fin;
    fin.open("E:\\Qtprojects\\Contact\\files\\contact.txt");
    string sname, sage, sphoneNumber, ssex, s_class;
    if (fin.peek() == EOF)
    {
        cout << "file is empty!" << endl;
        exit(0);
    }
    while (!fin.eof())
    {
        fin >> sname >> sage >> sphoneNumber >> ssex >> s_class;
        add(sname, sage, sphoneNumber, ssex, s_class);
    }
    fin.close();
}

void HashTable::Search(string key)
{
    int k = (int) key[0];
    if (k < 0)
    {
        nameSearch(key);
    }
    else
    {
        phoneNumberSearch(key);
    }
}

void HashTable::Remove(string key)
{
    int k = (int) key[0];
    if (k < 0)
    {
        nameRemove(key);
    }
    else
    {
        phoneNumberRemove(key);
    }
}

HashTable::~HashTable()
{
    for (int i = 0; i < length; i++)
    {
        Node *p = &nameHashTable[i];
        while (p->rightlink != NULL)
        {
            p = p->rightlink;
            Node *t = p;
            t = NULL;
            delete t;
        }
    }
    delete [] nameHashTable;
    delete [] numHashTable;
}

