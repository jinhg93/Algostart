/*
위상 정렬 : 순서가 정해져있는 작업을 차례로 수행해야 할 때, 그 순서를 결정해 주기 위해 사용하는 알고리즘
사이클이 발생하지 않는 그래프에서만 사용 가능하다
https://m.blog.naver.com/ndb796/221236874984

위상정렬 알고리즘(큐를 이용)
1. 진입 차수가 0인 정점을 큐에 삽입한다
    진입차수 : 연결된 간선의 개수(여기선 이 작업을 하기 위해 먼저 해결해야하는 작업 개수)
2. 큐에서 원소를 꺼내 연결된 모든 간선을 제거한다
3. 간선 제거 이후, 진입차수가 0이 된 정점을 큐에 삽입
4. 큐가 빌때까지 2, 3번 과정을 반복한다.
    모든 원소를 방문하기 전에 큐가 빈다면, 사이클이 존재하는 것이고(불가능!), 모든 원소를 방문했다면 큐에서 꺼낸 순서가 위상정렬의 결과이다.
*/
/*
위상정렬 예시
       2 → 3 → 4
    ↗
  1            ↓
    ↘
       5    →  6  → 7
*/

#include <iostream>
#include <vector>
#include <queue>

#define MAX 10

using namespace std;

int n; // 작업 개수
int inDegree[MAX]; // 진입차수를 저장하는 배열 
vector<int> a[MAX]; // 간선 정보를 저장하는 2차원 벡터


void topologySort() {
    int result[MAX]; // 정렬된 결과를 저장하는 배열
    queue<int> q;

    // 진입차수가 0인 노드를 큐에 삽입
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    // 정렬을 완전히 하려면 정확히 n개의 노드 방문 필요
    for (int i = 1; i <= n; i++) {
        if (q.empty()) { // 그 전에 큐가 빈다면 사이클이 발생하여 종료한것임
            printf("사이클 발생");
            return;
        }
    
        int x = q.front();
        q.pop();
        result[i] = x;

        for (int i = 0; i < a[x].size(); i++) {
            int y = a[x][i]; // 연결된 간선을 따라간다
            inDegree[y]--;
            if (inDegree[y] == 0) {
                q.push(y);
            }
        }
    }

    // 정렬된 결과 출력
    for (int i = 1; i <= n; i++) {
        printf("%d ", result[i]);
    }
   

}

int main() {
    n = 7;
    a[1].push_back(2); // 1->2
    inDegree[2]++; // 2의 진입차수 1 증가
    a[1].push_back(5); // 1->5
    inDegree[5]++;
    a[2].push_back(3);
    inDegree[3]++;
    a[3].push_back(4);
    inDegree[4]++;
    a[4].push_back(6);
    inDegree[6]++;
    a[5].push_back(6);
    inDegree[6]++;
    a[6].push_back(7);
    inDegree[7]++;

    topologySort();

    return 0;
}