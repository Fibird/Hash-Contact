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
    Student data;       //����
    Node *rightlink;    //��ָ��
    Node *leftlink;         //��ָ��
    Node *uplink;           //��ָ��
    Node *downlink;     //��ָ��
    Node(string sname, string sage, string sphoneNumber,
         string ssex, string s_class, Node *r = NULL, Node *d = NULL);  //���캯��
    Node();     //Ĭ�Ϲ��캯��
    ~Node();
};

class HashTable
{
private:
    int divisor;            //�����������е�ģ�Ĵ�С
    int length;             //ɢ�б�ĳ���
    Node *nameHashTable;        //������ϣ��
    Node *numHashTable;         //�����ϣ��
    unsigned int Encode(string &n);      //���뺯��������Ϊһ�ַ��������ڲ�����
    bool nameSearch(string sname);      //��������������Ϊһ�����ַ��������ڲ�����
    bool phoneNumberSearch(string sphoneNumber);    //��������������Ϊһ�ֻ������ַ��������ڲ�����
    void nameRemove(string sname);      //ɾ������������Ϊһ�����ַ��������ڲ�����
    void phoneNumberRemove(string sphoneNumber);    //ɾ������������Ϊһ�ֻ������ַ��������ڲ�����
    unsigned int PJWHash(const string& str);       //PJW��ϣ����
    unsigned int DJBHash(const string& str);        //DJB��ϣ�������˳��������õĹ�ϣ������
    unsigned int DEKHash(const string& str);        //DEK��ϣ����
    unsigned int BPHash  (const std::string& str);
    unsigned int FNVHash (const std::string& str);
    unsigned int APHash  (const std::string& str);
    unsigned int ELFHash(const std::string& str);
    unsigned int MYHash(const string& str);
    unsigned int SDBMHash(const std::string& str);
public:
    HashTable(int d, int l);        //���캯����d����Ϊ��ϣ������ģ��lΪ��ϣ�����ĳ���
    void add(string sname, string sage, string sphoneNumber,
             string ssex, string s_class);      //���뺯��
    void Remove(string key);       //ɾ������������Ϊһ�ַ��������������ֻ����룩
    void Search(string key);        //��������������Ϊһ�ַ��������������ֻ����룩
    void fileRead();        //��ȡ�ļ�
    ~HashTable();
};

#endif // HASHTABLE_H_INCLUDED
