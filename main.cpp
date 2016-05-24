#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <ctime>
#include "HashTable.h"

using namespace std;

int main()
{
    HashTable contact(100003, 100004);
    contact.fileRead();
    /*string num;
    for (int i = 0; i < 7; i++)
    {
        cin >> num;
        contact.Search(num);
    }*/

    return 0;
}
/*
ËÕÓ¢
¸µºÍÍ¨
»¨º­ÁÁ
ÎÀå«Ä®
×£º­Òâ
ºÎº­ìã
ÅËºÆåã
*/
/*
10011881739
18118431970
10419051153
14717471785
19417311834
15318741572
14115561778
*/
