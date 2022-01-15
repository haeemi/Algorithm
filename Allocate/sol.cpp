						//10개, 9개, 9개, 8개 ... 8개
static int square[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
static int start[9] = { 1, 11, 29, 65, 129, 257, 513, 1025, 2049 };
static int log[9][11] = { 0, };	//[길이][group]	[길이][o]=count

void allocator_init() {
}

int allocate(int group, int len) {
	int n;
	int full = 0;
	for (int i = 0; i < 9; i++) {
		if (len == square[i]) { n = i; break; }
	}
	if (n == 0) full = 10;
	else if (n <= 2) full = 9;
	else full = 8;

	//1) 자기 구역이 꽉 차 있으면 종료
	if (n == 0 && log[n][0] == 10) return -1;
	else if ((n == 1 || n == 2) && log[n][0] == 9) return -1;
	else if (n >= 3 && log[n][0] == 8) return -1;

	//2) 자기 구역에 빈 공간이 있으면
	else {
		//2-1.만약 한개도 없으면 첫번째 좌표 보내고 종료
		if (log[n][0] == 0) {
			log[n][1] = group;
			log[n][0]++;
			return start[n]-1;
		}
		//2-2. 만약 한개라도 배정되어있으면 처음부터 끝까지 확인 후 좌표 보내고 종료
		else {
			for (int i = 1; i <= full; i++) {
				if (log[n][i] == 0) {
					log[n][i] = group;//
					log[n][0]++;
					return start[n]+len*(i-1)-1;
				}
			}
		}
	}
}

void clear(int group) {
	int n, turn;	//길이와 그 요소가 배정된 위치
	bool find = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 11; j++) {	//[길이][위치] 
			if (log[i][j] == group) { n = i; turn = j; find = true; break; }
		}
		if (find == true) break;
	}
	log[n][turn] = 0;
	log[n][0]--;
}