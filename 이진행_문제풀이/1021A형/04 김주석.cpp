/*
[작업] https://www.acmicpc.net/problem/2056
위상 정렬 + DP

N개의 작업이 주어짐
작업 소요시간과 선행관계가 주어질 때,
모든 작업을 완료하기 위한 최소시간을 출력

*/

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <math.h>

#define MAX 51

using namespace std;

int N; // 작업 개수
int inDegree[MAX];  // 진입 차수 
int t[MAX]; // 소요시간
int dp[MAX]; // 선행작업을 하는데 걸리는 시간을 저장
int t_cpy[MAX] , dp_cpy[MAX], inDegree_cpy[MAX]; // 복사본

vector<int> edge[MAX]; // 간선 정보

void Input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int x;
		cin >> t[i] >> x; // 소요 시간과 선행 관계 개수 입력
		dp[i] = t[i]; // dp초기화
		inDegree[i] = x; // 진입 차수 개수 설정

		// 선행 관계가 있다면
		if (x != 0) {
			for (int j = 0; j < x; j++) {
				int pre;
				cin >> pre;
				edge[pre].push_back(i); // 간선 정보 저장
			}
		}
	}
	memcpy(t_cpy, t, sizeof(t_cpy));
	memcpy(inDegree_cpy, inDegree, sizeof(inDegree_cpy));
	memcpy(dp_cpy, dp, sizeof(dp_cpy));
}

// 위상정렬
// i번째 업무는 시간이 반이 된다.
int topologySort(int help) {
	int answer = 0;
	queue<int> qu;

	// 김주석이 도와주는 업무는 시간이 절반으로 줄어듬
	for (int i = 1; i <= N; i++) {
		if (i == help) {
			dp[i] = dp[i] / 2; 
			t[i] = t[i] / 2; 
			break;
		}
	}

	// 1. 진입 차수가 0인 노드를 큐에 모두 삽입
	for (int i = 1; i <= N; i++) {
		if (inDegree[i] == 0) {
			qu.push(i);
		}
	}

	for (int i = 1; i <= N; i++) {
		if (qu.empty()) { // 위상정렬 도중 큐가 빈다면, 사이클이 생성된것
			// cout << "사이클 생성됨!" << endl;
			return -1;
		}

		int now = qu.front();
		qu.pop();

		// cout << now << " ";

		// 현재 노드와 연결된 간선들 확인
		for (int i = 0; i < edge[now].size(); i++) {
			int next = edge[now][i];
			dp[next] = max(dp[next], dp[now] + t[next]);
			
			// now와 연결된 간선들 제거, 이후 진입차수가 0인 노드들 큐에 넣기
			inDegree[next]--;
			if (inDegree[next] == 0) {
				qu.push(next);
			}
		}
	}

	// 결과 출력
	for (int i = 1; i <= N; i++) {
		answer = max(answer, dp[i]); // 가장 오래걸리는 시간 출력
	}

	return answer;
}

int main() {
	freopen_s(new FILE*, "input.txt", "r", stdin);
	Input();

	// 위상정렬 수행 후 결과 출력
	int min_time = 21e8;

	// 김수석이 i번째 업무를 도와주는 경우를 각각 계산해서 최소값 비교?
	for (int i = 1; i <= N; i++) {
		
		// 원상복구
		memcpy(t, t_cpy, sizeof(t));
		memcpy(dp, dp_cpy, sizeof(dp)); 
		memcpy(inDegree, inDegree_cpy, sizeof(inDegree));
		int tmp;

		tmp = topologySort(i);

		if (tmp < min_time) {
			min_time = tmp;
		}
	}
	
	cout << min_time;

	return 0;
}