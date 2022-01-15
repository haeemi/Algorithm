extern void my_push(int s);
extern void enqueue(void);
extern int my_pop(int s);

void test_main() {
	int stackCount[10] = { 10000, 0, };  //���� �� ī��Ʈ�ϱ�

	int targetStack = -1;
	int nowElement = -1;
	int tempStack = -1;		//nowElement�� �ӽ÷� �����ص� ��

	while (true) {
		if (stackCount[0] == 0) break;

		nowElement = my_pop(0);					//0���� �ٷ� ������� 
		if (nowElement == 0) {	//���� 0�̸� �ٷ� ť�� �ְ� ����ī��Ʈ ����
			enqueue();
			stackCount[0]--;
			continue;
		}
		targetStack = nowElement / 100;
		//����
		if (targetStack == 10)targetStack = 9;
		if (targetStack == 0)targetStack = 1;

		if (stackCount[targetStack] == 0) {
			my_push(targetStack);
		}
		else {
			if (targetStack == 9) tempStack = 1;
			else tempStack = targetStack + 1;
			my_push(tempStack);					//�ٷ� ���ڸ���(Ÿ���� 9�� 1���ڸ���) �ӽ÷� �־�α� 
			int compareElement;
			int n = 0;		//0���� ������� ��
			int targetN = stackCount[targetStack];	//Ÿ���� �ܿ� ��� ��
			while (true) {
				if (targetN == 0) {					//Ÿ���� �ܿ� ��Ұ� 0�̶��
					my_pop(tempStack);
					my_push(targetStack);
					for (int i = 0; i < n; i++) {
						my_pop(0);
						my_push(targetStack);	//�ٽ� �Ѳ� �ݱ�
					}
					break;
				}

				compareElement = my_pop(targetStack);	//���Ұ�
				if (compareElement >= nowElement) {
					my_push(targetStack);		//�Ʊ� ���� ���ߴ��� �ٽ� ����ֱ�
					my_pop(tempStack);
					my_push(targetStack);		//������ ���� nowElement�� �ٽ� ���� ����ֱ�

					for (int i = 0; i < n; i++) {
						my_pop(0);
						my_push(targetStack);	//�ٽ� �Ѳ� �ݱ�
					}
					break;
				}
				else {
					my_push(0);
					n++;
					targetN--;
				}
			}
		}

		stackCount[targetStack]++;
		stackCount[0]--;

	}
	for (int i = 1; i <= 9; i++) {


		for (int j = 0; j < stackCount[i]; j++) {
			my_pop(i);
			enqueue();
		}
	}
}
