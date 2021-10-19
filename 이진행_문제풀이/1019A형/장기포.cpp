/*
N*N의 장기판이 주어지고
각 위치에 알과 포가 주어진다
포는 알을 넘어서만 이동 또는, 다른 알을 잡을 수 있다.
포를 세번 움직일 때, 잡을 수 있는 모든 알의 개수를 구하여라

제약사항)
- 포는 빈 공간으로도 움직일 수 있다
- 포는 2개 이상의 알을 넘어갈 수 없다
- 포는 특정 알을 넘어간 후 다시 넘어올 수 있다

풀이)
3번까지 움직여야한다 -> DFS
4방향 이동 -> direct 배열 사용 

DFS(포의 y좌표, 포의 x좌표, 레벨)

	바닥조건 : 레벨 3 이상이라면(3번 움직이면) 종료
	
	4방향 확인 ←↑→↓
		한쪽 방향으로 이동해본다
		만약에 빈공간이 쭉 나오다가 알이 나왔다면
		그 알을 넘어갈 수 있으므로, 그 방향으로 이동이 가능하다
		(알이 없다면 그 방향으로 이동 불가)
			이동이 가능하다면, 그 방향으로 이동하면서 처음 나오는 알을 찾는다
				빈 공간으로 움직일 수 있으므로 이동해본다
					포를 이동 후, 그자리에서 DFS를 재 호출한다

				만약 처음 만나는 알이 나타났다면, 
					포를 그 위치로 이동시키고, 알을 없앤다. 
					또한, chk 배열에 알을 잡을 수 있다고 표시해놓는다
					그리고 이미 알을 하나 넘고 잡았으므로, 그 뒤는 더이상 보지않는다.
					알을 잡은 위치에서 DFS를 재 호출한다. 
			
DFS가 종료되면, chk 배열에 저장해 둔 잡을 수 있는 알들의 개수를 체크한다

*/

#include <iostream>
#include <string.h>

// #define DEBUG
#ifdef DEBUG
#include <vector>
#endif

using namespace std;

int N;
int map[51][51];
int visited[51][51];
int chk[51][51];

int direct[4][2] = { 0,-1, -1,0, 0,1, 1,0 };
int po_y, po_x;

struct node {
	int y;
	int x;
};

#ifdef DEBUG
vector<node> path;
#endif

void Input() {
	cin >> N;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 2) { // 포 위치 
				po_y = y;
				po_x = x;
			}
		}
	}

}

void DFS(int po_y, int po_x, int lev) {

	if (lev >= 3) {
#ifdef DEBUG
		cout << "PATH : ";
		for (int i = 0; i < lev; i++) {
			cout << "(" << path[i].y << "," << path[i].x << ") | ";
		}
		cout << endl;*/
#endif
		return;
	}

	for (int t = 0; t < 4; t++) {
		int dy = po_y + direct[t][0];
		int dx = po_x + direct[t][1];

		bool alread_kill = false;
		while (1) {
			if (alread_kill == true) break;
			if (dy < 0 || dx < 0 || dy >= N || dx >= N) break; // 경계처리

			if (map[dy][dx] == 1) { // 만약 넘을수 있는 알이 나왔다면
				// 그 방향으로 한칸 더 이동 후, 그방향으로 쭉 가본다.
				dy += direct[t][0];
				dx += direct[t][1];

				while (1) {
					if (alread_kill == true) break;
					if (dy < 0 || dx < 0 || dy >= N || dx >= N) break; // 경계처리

					// 만약 잡을수 있는 알이 처음 등장하면 잡고, 그 자리에서 DFS 재 호출
					if (map[dy][dx] == 1 && visited[dy][dx] == 0) {


						visited[dy][dx] = lev + 1;
#ifdef DEBUG
						path.push_back({ dy,dx });
#endif
						chk[dy][dx] = true;

						map[dy][dx] = 2;
						map[po_y][po_x] = 0;

						DFS(dy, dx, lev + 1);

						visited[dy][dx] = 0;
#ifdef DEBUG
						path.erase(path.begin() + path.size()-1);
#endif

						map[dy][dx] = 1;
						map[po_y][po_x] = 2;
						// 돌을 두개를 동시에 넘을 수 없으므로 잡았으면 더이상 확인하지 않게 플래그 처리
						alread_kill = true;
					}
					// 잡을 수 있는 알이 없어도 이동은 할 수 있다.
					else {
						visited[dy][dx] = lev + 1;
#ifdef DEBUG
						path.push_back({ dy,dx });
#endif
						map[dy][dx] = 2;
						map[po_y][po_x] = 0;


						DFS(dy, dx, lev + 1);

						map[dy][dx] = 0;
						map[po_y][po_x] = 2;

						visited[dy][dx] = 0;
#ifdef DEBUG
						path.erase(path.begin() + path.size() - 1);
#endif
					}
					dy += direct[t][0];
					dx += direct[t][1];
				}
			}

			dy += direct[t][0];
			dx += direct[t][1];
		}

	}

}

int main() {
	freopen_s(new FILE*, "input.txt", "r", stdin);
	int T, i = 0;
	cin >> T;

	while (T--) {
		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));
		memset(chk, 0, sizeof(chk));

		Input();

		DFS(po_y, po_x, 0);

		int total = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (chk[y][x] == 1) {
					total++;
				}
			}
		}

		cout << "#" << ++i << " " << total << endl;
	}


	return 0;
}
