						//10��, 9��, 9��, 8�� ... 8��
static int square[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
static int start[9] = { 1, 11, 29, 65, 129, 257, 513, 1025, 2049 };
static int log[9][11] = { 0, };	//[����][group]	[����][o]=count

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

	//1) �ڱ� ������ �� �� ������ ����
	if (n == 0 && log[n][0] == 10) return -1;
	else if ((n == 1 || n == 2) && log[n][0] == 9) return -1;
	else if (n >= 3 && log[n][0] == 8) return -1;

	//2) �ڱ� ������ �� ������ ������
	else {
		//2-1.���� �Ѱ��� ������ ù��° ��ǥ ������ ����
		if (log[n][0] == 0) {
			log[n][1] = group;
			log[n][0]++;
			return start[n]-1;
		}
		//2-2. ���� �Ѱ��� �����Ǿ������� ó������ ������ Ȯ�� �� ��ǥ ������ ����
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
	int n, turn;	//���̿� �� ��Ұ� ������ ��ġ
	bool find = false;
	for (int i = 0; i < 9; i++) {
		for (int j = 1; j < 11; j++) {	//[����][��ġ] 
			if (log[i][j] == group) { n = i; turn = j; find = true; break; }
		}
		if (find == true) break;
	}
	log[n][turn] = 0;
	log[n][0]--;
}