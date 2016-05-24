#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include "student.h"

using namespace std;
extern int avglength;
struct Node
{
    Student data;       //数据
    Node *rightlink;    //右指针
    Node *leftlink;         //左指针
    Node *uplink;           //上指针
    Node *downlink;     //下指针
    Node(string sname, string sage, string sphoneNumber,
         string ssex, string s_class, Node *r = NULL, Node *d = NULL);  //构造函数
    Node();     //默认构造函数
    ~Node();
};

class HashTable
{
private:
    int divisor;            //除留余数法中的模的大小
    int length;             //散列表的长度
    Node *nameHashTable;        //姓名哈希表
    Node *numHashTable;         //号码哈希表
    unsigned int Encode(string &n);      //编码函数，参数为一字符串，仅内部调用
    bool nameSearch(string sname);      //搜索操作，参数为一姓名字符串，仅内部调用
    bool phoneNumberSearch(string sphoneNumber);    //搜索操作，参数为一手机号码字符串，仅内部调用
    void nameRemove(string sname);      //删除操作，参数为一姓名字符串，仅内部调用
    void phoneNumberRemove(string sphoneNumber);    //删除操作，参数为一手机号码字符串，仅内部调用
    unsigned int PJWHash(const string& str);       //PJW哈希函数
    unsigned int DJBHash(const string& str);        //DJB哈希函数（此程序所采用的哈希函数）
    unsigned int DEKHash(const string& str);        //DEK哈希函数
    unsigned int BPHash  (const std::string& str);
    unsigned int FNVHash (const std::string& str);
    unsigned int APHash  (const std::string& str);
    unsigned int ELFHash(const std::string& str);
    unsigned int MYHash(const string& str);
    unsigned int SDBMHash(const std::string& str);
public:
    HashTable(int d, int l);        //构造函数，d参数为哈希函数的模，l为哈希函数的长度
    void add(string sname, string sage, string sphoneNumber,
             string ssex, string s_class);      //插入函数
    void Remove(string key);       //删除操作，参数为一字符串（姓名或者手机号码）
    void Search(string key);        //搜索操作，参数为一字符串（姓名或者手机号码）
    void fileRead();        //读取文件
    ~HashTable();
};

#endif // HASHTABLE_H_INCLUDED
