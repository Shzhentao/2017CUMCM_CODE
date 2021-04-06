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

void addedge(int u, int v, int w) { // The first variable subscript must be an even number
    edge[tol].from = u;
    edge[tol].to = v;
    edge[tol].cap = w;
    edge[tol].next = head[u];
    head[u] = tol++;
    edge[tol].from = v;
    edge[tol].to = u;
    edge[tol].cap = w;
    edge[tol].next = head[v];
    head[v] = tol++;
}

int BFS(int start, int end) {
    int que[MAXN];
    int front, rear;
    front = rear = 0;
    memset(dep, -1, sizeof(dep));
    que[rear++] = start;
    dep[start] = 0;
    while (front != rear) {
        int u = que[front++];
        if (front == MAXN)front = 0;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap > 0 && dep[v] == -1) {
                dep[v] = dep[u] + 1;
                que[rear++] = v;
                if (rear >= MAXN)rear = 0;
                if (v == end)return 1;
            }
        }
    }
    return 0;
}

int dinic(int start, int end) {
    int res = 0;
    int top;
    int stack[MAXN]; // stack is the stack, which stores the current augmentation path
    int cur[MAXN];  // store the successor of the current point
    while (BFS(start, end)) {
        memcpy(cur, head, sizeof(head));
        int u = start;
        top = 0;
        while (1) {
            if (u == end) {
                int min = INF;
                int loc;
                for (int i = 0; i < top; i++)
                    if (min > edge[stack[i]].cap) {
                        min = edge[stack[i]].cap;
                        loc = i;
                    }
                for (int i = 0; i < top; i++) {
                    edge[stack[i]].cap -= min;
                    edge[stack[i] ^ 1].cap += min;
                }
                res += min;
                top = loc;
                u = edge[stack[top]].from;
            }
            for (int i = cur[u]; i != -1; cur[u] = i = edge[i].next)
                if (edge[i].cap != 0 && dep[u] + 1 == dep[edge[i].to])
                    break;
            if (cur[u] != -1) {
                stack[top++] = cur[u];
                u = edge[cur[u]].to;
            }
            else {
                if (top == 0)break;
                dep[u] = -1;
                u = edge[stack[--top]].from;
            }
        }
    }
    return res;
}

int m;
double getPrice(const Ans& ans, const Task& task) {
    double ret = 70;
    for (int i = 0; i < 3; i++) {
        ret += ans[i].a[i] * task[i].p[i];
    }
    return ret;
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
