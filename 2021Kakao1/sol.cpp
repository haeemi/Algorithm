#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;


int solution(string s) {

	string a[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	int size[10] = { 3, 2, 2, 4, 3, 3, 2, 4, 4, 3 };
	int temp[50] = { 0, };
	bool comp = false;

	int answer = 0;
	int locate = 0;


	for (int i = 0; i < 50; i++) {
		temp[i] = -1;
	}

	for (int i = 0; i < 50; i++) {
		if (s[i] == '\0') {
			break;
		}
		if (s[i] <= 57 && s[i] >= 48) {
			temp[locate] = s[i] - 48;
			locate++;
			continue;
		}

			switch (s[i]) {
			case 'z':
				temp[locate] = 0;
				locate++;
				i += size[0];
				break;
			case 'o':
				i += size[1];
				temp[locate] = 1;
				locate++;
				break;
			case 't':
				if (s[i + 1] == 'w') {
					i += size[2];
					temp[locate] = 2;
					locate++;
					break;
				}
				else {
					i += size[3];
					temp[locate] = 3;
					locate++;
					break;
				}

			case 'f':
				if (s[i + 1] == 'o') {
					i += size[4];
					temp[locate] = 4;
					locate++;
					break;
				}
				else {
					i += size[5];
					temp[locate] = 5;
					locate++;
					break;
				}

			case 's':
				if (s[i + 1] == 'i') {
					i += size[6];
					temp[locate] = 6;
					locate++;
					break;
				}
				else {
					i += size[7];
					temp[locate] = 7;
					locate++;
					break;
				}
			case 'e':
				i += size[8];
				temp[locate] = 8;
				locate++;
				break;
			case 'n':
				i += size[9];
				temp[locate] = 9;
				locate++;
				break;

			}
		
	}
	for (int i = 0; i < 50; i++) {
		if (temp[i] == -1)break;
		answer+=pow(10, locate-1)* temp[i];
		locate--;
	}
	return answer;
}

int main() {
	//printf("%s", a[1]);
	printf("%d", solution("onetwo5three48"));
}