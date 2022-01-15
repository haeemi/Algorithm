extern void get_school_position(int school_index, int* posX, int* posY);
extern void get_student_position(int student_index, int* posX, int* posY);
extern void set_student_school(int student_index, int school_index);

int calculateDistance(int x1, int x2, int y1, int y2)
{
	int x, y;
	x = (x1 - x2) * (x1 - x2);
	y = (y1 - y2) * (y1 - y2);
	return x + y;
}

int findShortest(int stdNum, int student[10000][3])
{
	int distance = 100000000;
	int tmp = 0, school = 0;
	int schoolX, schoolY, studentX, studentY;

	get_student_position(stdNum, &studentX, &studentY);
	student[stdNum][0] = studentX;
	student[stdNum][1] = studentY;
	for (int i = 0; i < 3; i++)
	{
		get_school_position(i, &schoolX, &schoolY);
		tmp = calculateDistance(schoolX, studentX, schoolY, studentY);
		if (distance > tmp) {
			distance = tmp;
			school = i;
		}
	}
	student[stdNum][2] = school;
	return school;
}

void QuickSort(int arr[], int left, int right, int arrNumber[]) {
	int L = left, R = right;
	int tmp; int numTemp;
	int pivot = arr[(left + right) / 2];

	while (L <= R) {
		while (arr[L] < pivot)
			L++;
		while (arr[R] > pivot)
			R--;


		if (L <= R) {
			if (L != R) {
				tmp = arr[L];
				arr[L] = arr[R];
				arr[R] = tmp;

				numTemp = arrNumber[L];
				arrNumber[L] = arrNumber[R];
				arrNumber[R] = numTemp;

			}
			L++; R--;
		}
	}

	if (left < R)
		QuickSort(arr, left, R, arrNumber);
	if (L < right)
		QuickSort(arr, L, right, arrNumber);
}


void QuickSort2(int arr[], int left, int right, int arrNumber[], int arrinfo[]) {
	int L = left, R = right;
	int tmp; int numTemp; int infoTemp;
	int pivot = arr[(left + right) / 2];

	while (L <= R) {

		while (arr[L] < pivot)
			L++;
		while (arr[R] > pivot)
			R--;

		if (L <= R) {
			if (L != R) {
				tmp = arr[L];
				arr[L] = arr[R];
				arr[R] = tmp;

				numTemp = arrNumber[L];
				arrNumber[L] = arrNumber[R];
				arrNumber[R] = numTemp;

				infoTemp = arrinfo[L];
				arrinfo[L] = arrinfo[R];
				arrinfo[R] = infoTemp;

			}
			L++; R--;
		}
	}

	if (left < R)
		QuickSort2(arr, left, R, arrNumber, arrinfo);
	if (L < right)
		QuickSort2(arr, L, right, arrNumber, arrinfo);
}

void run_contest(void)
{

	int student[10000][3];
	int stdNum[3] = { 0, 0, 0 };	//�л� ��
	int condition = 0;

	for (int i = 0; i < 10000; i++)
	{
		int shortestSchool = findShortest(i, student);
		set_student_school(i, shortestSchool);
		stdNum[shortestSchool]++;
	}  

	//printf("A�б�: %d, B�б�: %d, C�б�:%d\n", stdNum[0], stdNum[1], stdNum[2]);

	/*3500�� �ʰ����� ���� üũ
	 condition == 0 ��� �б��� ������ �ο��� ���� 3500�� ����
	 condition == 1 3500�� �ʰ��� �б��� ���� 1�� �� ��
	 condition == 1 3500�� �ʰ��� �б��� ���� 2�� �� �� */
	for (int i = 0; i < 3; i++)
		if (stdNum[i] >= 3500) condition++;
	if (condition == 0)return;

	else if (condition == 2) {

		int arr[10000] = { 0, };
		int arrNumber[10000] = { 0, };
		int exceededSchool[2] = { -1, -1 };	//�ʰ��� �б� 2��
		int lackedShool = -1;				//����� �б� 1���� �̸�
		int schoolX, schoolY;				//����� �б��� �Ÿ� ��ǥ
		int NumOfExceeded = 0;				//�ʰ��� �б� 2���� ��� �л� ��(���Ѱ�)

		int j = 0;
		for (int i = 0; i < 3; i++)
			if (stdNum[i] >= 3500) {
				exceededSchool[j] = i;
				NumOfExceeded += stdNum[i];
				j++;
			}
			else {
				lackedShool = i;
				get_school_position(lackedShool, &schoolX, &schoolY);
			}

		j = 0;
		for (int i = 0; i < 10000; i++) {
			if (student[i][2] == lackedShool)continue;
			arr[j] = calculateDistance(student[i][0], schoolX, student[i][1], schoolY);
			arrNumber[j] = i;
			//printf("%d %d\n", arr[j], arrNumber[j]);
			j++;
		}

		QuickSort(arr, 0, 9999, arrNumber);

		//for (int i = 0; i < 10000; i++)
		//	printf("%d, %d\n", arr[i], arrNumber[i]);

		for (int i = 0; i < 10000; i++) {
			if (arrNumber[i] == 0)continue;

			if (student[arrNumber[i]][2] == exceededSchool[0]) {
				stdNum[exceededSchool[0]]--;
				stdNum[lackedShool]++;
				student[arrNumber[i]][2] = lackedShool;//////////////
				set_student_school(arrNumber[i], lackedShool);
				if (stdNum[exceededSchool[0]] <= 3500) exceededSchool[0] = -1;
			}
			else if (student[arrNumber[i]][2] == exceededSchool[1]) {
				stdNum[exceededSchool[1]]--;
				stdNum[lackedShool]++;
				//	printf("%d %d\n", arrNumber[i], student[arrNumber[i]][2]);//
				set_student_school(arrNumber[i], lackedShool);
				student[arrNumber[i]][2] = lackedShool;//////////////
			//	printf("%d %d\n", arrNumber[i], student[arrNumber[i]][2]);//

				if (stdNum[exceededSchool[1]] <= 3500) exceededSchool[1] = -1;
			}
			if (exceededSchool[0] == -1 && exceededSchool[1] == -1) break;
		}
	}

	else if (condition == 1) {
		int arr[10000] = { 0, };			//����� �б� �� ���� �� �� ����� ���� �Ÿ� �迭
		int arrinfo[10000] = { 0, };		//����� �б� �� ���� �� �� ����� ���� �б� �迭
		int arrNumber[10000] = { 0, };		//�л�����
		int exceededSchool = -1;			//�ʰ��� �б� 1���� �̸�
		int lackedShool[2] = { -1, -1 };	//����� �б� 2���� �̸�

		int schoolX0 = 0, schoolY0 = 0;		//����� �б� 1��°�� �Ÿ���ǥ
		int schoolX1 = 0, schoolY1 = 0;		//����� �б� 2��°�� �Ÿ���ǥ

		for (int i = 0; i < 3; i++)			//�ʰ��� �б��� ����� ã��
			if (stdNum[i] > 3500)
			{
				exceededSchool = i; break;
			}

		if (exceededSchool == 0) {
			lackedShool[0] = 1;
			lackedShool[1] = 2;
		}
		else if (exceededSchool == 1) {
			lackedShool[0] = 0;
			lackedShool[1] = 2;
		}
		else if (exceededSchool == 2) {
			lackedShool[0] = 0;
			lackedShool[1] = 1;
		}

		get_school_position(lackedShool[0], &schoolX0, &schoolY0);
		get_school_position(lackedShool[1], &schoolX1, &schoolY1);

		//	printf("%d, %d, %d, %d\n", schoolX0, schoolY0, schoolX1, schoolY1);

		int compare1 = 0, compare2 = 0;
		int j = 0;

		for (int i = 0; i < 10000; i++) {
			if (student[i][2] == lackedShool[0] || student[i][2] == lackedShool[1])continue;

			compare1 = calculateDistance(student[i][0], schoolX0, student[i][1], schoolY0);
			compare2 = calculateDistance(student[i][0], schoolX1, student[i][1], schoolY1);
			if (compare1 > compare2) {
				arr[j] = compare2;
				arrinfo[j] = lackedShool[0];
				arrNumber[j] = i;

			}
			else {
				arr[j] = compare1;
				arrinfo[j] = lackedShool[1];
				arrNumber[j] = i;
				//printf("%d, %d, %d\n", arr[j], arrinfo[j], arrNumber[j]);
			}
			j++;
		}

		QuickSort2(arr, 0, 9999, arrNumber, arrinfo);

		//for (int i = 0; i < 10000; i++)
		//	printf("%d, %d, %d\n", arr[i], arrinfo[i], arrNumber[i]);

		for (int i = 0; i < 10000; i++) {
			//	printf("%d, %d, %d\n", arr[i], arrinfo[i], arrNumber[i]);
			if (arrNumber[i] == 0)continue;
			if (stdNum[exceededSchool] <= 3500) break;
			if (arrinfo[i] == lackedShool[0]) {

				stdNum[exceededSchool]--;
				stdNum[lackedShool[0]]++;
				student[arrNumber[i]][2] = lackedShool[0];
				set_student_school(arrNumber[i], lackedShool[0]);
				if (stdNum[lackedShool[0]] >= 3500) lackedShool[0] = -1;
			}
			else if (arrinfo[i] == lackedShool[1]) {
				stdNum[exceededSchool]--;
				stdNum[lackedShool[1]]++;
				student[arrNumber[i]][2] = lackedShool[1];
				set_student_school(arrNumber[i], lackedShool[1]);
				if (stdNum[lackedShool[1]] >= 3500) lackedShool[1] = -1;
			}
			if (lackedShool[0] == -1 && lackedShool[1] == -1) break;
		}
	}

	int check0 = 0;
	int check1 = 0;
	int check2 = 0;

	for (int i = 0; i < 10000; i++) {
		if (student[i][2] == 0)check0++;
		else if (student[i][2] == 1)check1++;
		else if (student[i][2] == 2)check2++;
	}
	if (check0 > 3500 || check1 > 3500 || check2 > 3500) {

		int arr[10000] = { 0, };
		int arrNumber[10000] = { 0, };

		int exceededSchool[2] = { -1,-1 };
		int lackedShool = 0;
		int schoolX, schoolY;
		int NumOfExceeded = 0;

		int j = 0;
		for (int i = 0; i < 3; i++)
			if (stdNum[i] >= 3500) {
				exceededSchool[j] = i;
				NumOfExceeded += stdNum[i];
				j++;
			}
			else {
				lackedShool = i;
				get_school_position(lackedShool, &schoolX, &schoolY);
			}

		j = 0;
		for (int i = 0; i < 10000; i++) {
			if (student[i][2] == lackedShool)continue;
			arr[j] = calculateDistance(student[i][0], schoolX, student[i][1], schoolY);
			arrNumber[j] = i;
			//printf("%d %d\n", arr[j], arrNumber[j]);
			j++;

			//printf("distancd: %d StudentIndex:%d\n", k, i);
			//printf("%d, %d, �����б�%d\n", student[i][0], student[i][1], student[i][2]);
		}

		QuickSort(arr, 0, 9999, arrNumber);

		//for (int i = 0; i < 10000; i++)
		//	printf("%d, %d\n", arr[i], arrNumber[i]);

		for (int i = 0; i < 10000; i++) {
			if (arrNumber[i] == 0)continue;

			if (student[arrNumber[i]][2] == exceededSchool[0]) {
				stdNum[exceededSchool[0]]--;
				stdNum[lackedShool]++;
				student[arrNumber[i]][2] = lackedShool;//////////////
				set_student_school(arrNumber[i], lackedShool);
				if (stdNum[exceededSchool[0]] <= 3500) exceededSchool[0] = -1;
			}
			else if (student[arrNumber[i]][2] == exceededSchool[1]) {
				stdNum[exceededSchool[1]]--;
				stdNum[lackedShool]++;
				//	printf("%d %d\n", arrNumber[i], student[arrNumber[i]][2]);//
				set_student_school(arrNumber[i], lackedShool);
				student[arrNumber[i]][2] = lackedShool;//////////////
			//	printf("%d %d\n", arrNumber[i], student[arrNumber[i]][2]);//

				if (stdNum[exceededSchool[1]] <= 3500) exceededSchool[1] = -1;
			}
			if (exceededSchool[0] == -1 && exceededSchool[1] == -1) break;
		}
		//printf("A�б�: %d, B�б�: %d, C�б�:%d", stdNum[0], stdNum[1], stdNum[2]);
	}

	check0 = 0;
	check1 = 0;
	check2 = 0;

	for (int i = 0; i < 10000; i++) {
		if (student[i][2] == 0)check0++;
		else if (student[i][2] == 1)check1++;
		else if (student[i][2] == 2)check2++;
	}
	//printf("%d, %d, %d��\n", check0, check1, check2);
}

