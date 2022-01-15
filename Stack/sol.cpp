extern void my_push(int s);
extern void enqueue(void);
extern int my_pop(int s);

void test_main() {
	int stackCount[10] = { 10000, 0, };  //스택 안 카운트하기

	int targetStack = -1;
	int nowElement = -1;
	int tempStack = -1;		//nowElement를 임시로 보관해둘 곳

	while (true) {
		if (stackCount[0] == 0) break;

		nowElement = my_pop(0);					//0에서 바로 끄집어내기 
		if (nowElement == 0) {	//만약 0이면 바로 큐에 넣고 스택카운트 감소
			enqueue();
			stackCount[0]--;
			continue;
		}
		targetStack = nowElement / 100;
		//보정
		if (targetStack == 10)targetStack = 9;
		if (targetStack == 0)targetStack = 1;

		if (stackCount[targetStack] == 0) {
			my_push(targetStack);
		}
		else {
			if (targetStack == 9) tempStack = 1;
			else tempStack = targetStack + 1;
			my_push(tempStack);					//바로 옆자리에(타겟이 9면 1번자리에) 임시로 넣어두기 
			int compareElement;
			int n = 0;		//0번에 덜어놓은 수
			int targetN = stackCount[targetStack];	//타겟의 잔여 요소 수
			while (true) {
				if (targetN == 0) {					//타겟의 잔여 요소가 0이라면
					my_pop(tempStack);
					my_push(targetStack);
					for (int i = 0; i < n; i++) {
						my_pop(0);
						my_push(targetStack);	//다시 뚜껑 닫기
					}
					break;
				}

				compareElement = my_pop(targetStack);	//비교할것
				if (compareElement >= nowElement) {
					my_push(targetStack);		//아까 빼서 비교했던거 다시 집어넣기
					my_pop(tempStack);
					my_push(targetStack);		//보관해 놨던 nowElement를 다시 빼서 집어넣기

					for (int i = 0; i < n; i++) {
						my_pop(0);
						my_push(targetStack);	//다시 뚜껑 닫기
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
