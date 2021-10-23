/*
그리디 작업스케줄링 문제? 아닌것같음. 시작시간과 종료시간이 주어지지 않음!

근사 알고리즘 문제?

근사 알고리즘 : 어떤 최적화 문제에 대한 해의 근사값을 구하는 알고리즘
가장 최적화되는 답을 구할 수는 없지만, 어느정도 보장된 근사해를 계산할 수 있다.

https://gazelle-and-cs.tistory.com/16 근사 알고리즘이란 무엇인가
https://dudri63.github.io/2019/02/08/algo38/ 작업스케줄링(근사)

-----------------------------------------------------------------------
일단 단계별로 문제 풀어보기

1. N개의 작업과, M개의 기계가 주어질 때, 종료되는 최단시간 구하는 문제

입력 : N개의 작업과 각 작업의 수행시간 배열, 그리고 수행할 기계의 개수 M
출력 : 모든 작업이 종료된 최단시간
*/

#include <iostream>
#include <vector>

using namespace std;

int N, M; // N개의 작업, M개의 기계
vector<int> t; // 작업 수행시간 
vector<int> L; // 기계 M에 배정된 마지막 작업의 종료 시간

void Input() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int cost;
		cin >> cost;
		t.push_back(cost);
	}

	// M개의 기계 작업시간 0으로 초기화
	L.assign(M, 0); 
}

int main() {
	freopen_s(new FILE*, "input.txt", "r", stdin);
	Input();

	// n개의 작업을 배정하기
	for (int i = 0; i < t.size(); i++) {

		// L[0] ~ L[M-1]중 가장 일찍 끝나는 기계를 찾아 min에 idx를 저장
		// L[i]에 종료시간을 저장하므로, 값이 제일 작은 값을 찾는다
		int min = 0; 
		for (int j = 1; j < L.size(); j++) { 
			if (L[j] < L[min]) {
				min = j;
			}
		}

		// 작업 i(t[i]) 를 
		// 기계 M_min에 배정 <- 종료시간을 추가해준다
		L[min] = L[min] + t[i];
	}

	// 가장 늦게 끝나는 기계 찾기
	int max_time = 0;
	for (int i = 0; i < L.size(); i++) {
		if (max_time < L[i]) {
			max_time = L[i];
		}
	}
	cout << max_time;

	return 0;
}