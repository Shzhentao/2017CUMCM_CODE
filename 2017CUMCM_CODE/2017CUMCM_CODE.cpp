// 2017CUMCM_CODE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

// Maximum flow algorithm
const int INF = 0x3f3f3f3f;
const int MAXN = 100100; // Maximum number of points
const int MAXM = 200100; // Maximum number of edges

struct Node {
    int from = 0;
    int to = 0;
    int next = 0;
    int cap = 0;
};

Node edge[MAXM];

int tol = 0;
int dep[MAXN]; // dep is the level of points
int head[MAXN];

int n = 0;
void init() {
    tol = 0;
    memset(head, -1, sizeof(head));
}


int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
