---
layout: post
title: 'TRY'
subtitle: 'One'
date: 2018-09-15
tags: DSAA
description: 'My DSAA HomewWork'
color: 'rgb(255,210,32)'
cover: 'http://img1.tplm123.com/2008/10/05/37515/869534843924.jpg'
---
> Transform your plain text into static websites and blogs.

# HomeWork For Lecture1

**Author:** LinWeijun  
**Student number:** 2017141461358

## Answer For Question 1

```c++
template <typename T>
class StringMethod
{
  public:
    virtual bool isEmpty() = 0;            //Judge if it is empty
    char getAttr(int k) = 0;               //Get the character in the position k
    int cmpStr(const T & other) = 0;       //Compare
    int cpyStr(T & other, bool flag) = 0;  //Copy itself to other or copy other to itself
    int getLenth() = 0;                    //Get the length of the string
    void catStr(T & other) = 0;            //Concatenate the string other
    void clearStr() = 0;                   //Clear itself
    void printStr() = 0;                   //Print itself
};
```

My ***ADT*** consist on but not limited to the functions above.

### The two definition of physical representations for strings

- The **String** can be represented in the form of a segment of continuous memory

- The **String** also can be represented using the form of linked list

## Answer For Question 2

- I think the ***time*** it cost should be the first argument to think about. Because we can use lots of ways to save them. Besides, the ***stability*** is also important. A wonderful algorithm should deal with most situations successfully. Last but not least, we'd better take the ***space*** it occupies into account.

- First of all, We should do ***a great quantity*** tests. The amount is a important reference. The we should use various ***data forms*** such as ***totally inverted*** to calculate the time it costs.

## Answer For Question 3

The function:

```c
#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdio>

using namespace std;

const int maxn = 20;

bool used[maxn];
int index[maxn];

void PrintPermutations(const vector<int> &num, int start)
{
    int size = num.size();
    if (start == size)                         //Right situation
    {
        for (int i = 0; i < size; i++)
            printf("%d ", num[index[i]]);
        printf("\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (used[i] == false)
        {
            used[i] = true;
            index[start] = i;                  //Recording the immediate position
            PrintPermutations(num, start + 1); //Look for the next permutation
            used[i] = false;                   //Recover
        }
    }
}

int main()
{
    int n;
    while (cin >> n)
    {
        srand(time(NULL));
        memset(used, 0, sizeof(used));
        vector<int> num;
        for (int i = 0; i < n; i++)
        {
            num.push_back(rand() % 1000);
        }
        int time1 = clock();
        PrintPermutations(num, 0);
        int time2 = clock();
        cout << "It took " << time2 - time1 << " ms " << double((time2 - time1)) / CLOCKS_PER_SEC << " s" << endl;
    }
    return 0;
}
```

--------
I use **recursion** and **backtracking** to do it.  
In my opinion, the **complexity** is "n!".  
Because of the output statement, it will take lots of time to get the result when n bigger than 10.