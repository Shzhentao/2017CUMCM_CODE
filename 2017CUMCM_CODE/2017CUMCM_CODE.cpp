// 2017CUMCM_CODE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

struct Node {
int from = 0;
int to = 0;
int next = 0;
int cap = 0;
};

struct Task {
    double p[3];
    vector<User> user_vector;
};

struct Ans {
    double a[3];
};

struct User {
    int id = 0;
    double tasklimits = 0;
    double credit = 0;
};

typedef pair<int, int> pir;
typedef pair<double, double> Range;

// Maximum flow algorithm
const int INF = 0x3f3f3f3f;
const int MAXN = 100100; // Maximum number of points
const int MAXM = 200100; // Maximum number of edges
Range ansrange[3];
Node edge[MAXM];
vector<Task> tasks;
vector<User> users;
double ThresholdValue = 300;
double step = 1;
int tol = 0;
int dep[MAXN]; // dep is the level of points
int head[MAXN];
int m = 0;
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

double getPrice(const Ans& ans, const Task& task) {
    double ret = 70;
    for (int i = 0; i < 3; i++) {
        ret += ans.a[i] * task.p[i];
    }
    return ret;
}

double myrand(int range) {
    return double(rand() % range) / range;
}

double Countsatisfaction() {
    // A function to calculate user satisfaction, because the two models have different performance here, so leave this blank
    double m = 0;
    return m;
}

//int getPerfromance(Task task) {
//    int src = 0, dest = m + n + 1;
//    init(); //初始化建图
//    for (int i = 0; i < task.size(); i++)
//        addedge(src, i, 1);
//    for (int j = 0; j < task[i].user_vct.size(); i++) {
//        if (Countsatisfaction() > ThresholdValue) {
//            addedge(i, n + task[i].user[j], 1);
//        }
//    }
//    for (int j = 0; j < m; j++) {
//        addedge(task.size(), dest, users[j].tasklimits);
//    }
//    return dinic(src, dest);
//}
//int dx[] = { -1, 1, 0, 0, 0, 0 };
//int dy[] = { 0, 0, -1, 1, 0, 0 };
//int dz[] = { 0, 0, 0, 0, -1, 1 };
//void SA(double) {
//    double T = 1;
//    vector<Ans> host, guest;
//    for (int i = 0; i < 1000; i++) {//初始化解
//        Ans tmp;
//        for (int j = 0; j < 3; j++) {
//            tmp[j] = (ansrange[j].second - ans[j].first) * rand(1000) + ansrange[j].first;
//        }
//        host.push_back(tmp);;
//    }
//    double e = .00000001;
//    double at = 0.999;
//    double L = 20000;
//    for (int i = 0; i < L; i++) {
//        guest.clear();
//        for (int k = 0; k < host.size(); k++)
//            const Task& cur = host[k];
//        int cur_v = getPerfromance(cur);
//        for (int j = 0; j < 6; j++) {
//            Task& newtask;
//            newtask.p[0] += dx[j] * step;
//            newtask.p[1] += dy[j] * step;
//            newtask.p[2] += dz[j] * step;
//            int new_performance = getPerfromance(newtask);
//            if (new_performance > cur_v)
//                guest.push_back(newtask);
//            else if (exp(cur_v - new_performance) / T > myrand(1000)) {
//                host.push_back(newtask);
//            }
//        }
//    }
//}

int main()
{
    srand(unsigned(time(0)));
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        Task tmp;
        for (int j = 0; j < 3; j++) {
            cin >> tmp.p[j];
        }
        tasks.push_back(tmp);
        int a; cin >> a;
        tmp.user_vector.clear();
        for (int i = 0; i < a; i++) {
            User usertmp;
            cin >> usertmp.id >> usertmp.tasklimits >> usertmp.credit;
            tmp.user_vector.push_back(usertmp);
        }
    }
    for (int i = 0; i < 3; i++) {
        cin >> ansrange[i].first >> ansrange[i].second;
    }
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
