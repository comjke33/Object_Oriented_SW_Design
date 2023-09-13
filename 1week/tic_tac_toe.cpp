#include <iostream>
#include <vector>
using namespace std;

// data struct용 class
// 승패 여부와 승리자 정보를 담고 있음
class checkFinishGameStruct {
public:
	bool isFinish;
	int whoWin;
};

class TicTacToe {
public:
	// map을 보여줌
	void printMap(vector<vector<int>> map) {
		cout << "\n --- --- ---\n";
		for (int i = 0; i < 3; i++) {
			cout << "| ";
			for (int j = 0; j < 3; j++) {
				char point;
				if (map[i][j] == 0) {
					point = '_';
				}
				else if (map[i][j] == 1) {
					point = 'O';
				}
				else if (map[i][j] == 2) {
					point = 'X';
				}
				cout << point << " | ";
			}
			cout << "\n --- --- ---\n";
		}
		return;
	}
	// 돌 번호를 보여줌
	void printUserHelpMap(vector<vector<int>> map) {
		cout << "\n --- --- ---\n";
		for (int i = 0; i < 3; i++) {
			cout << "| ";
			for (int j = 0; j < 3; j++) {
				cout << map[i][j] << " | ";
			}
			cout << "\n --- --- ---\n";
		}
		return;
	}

	// 중복된 위치인지 bool형 반환
	bool checkDuplication(vector<vector<int>> map, int location) {
		int r = (location-1) / 3;
		int c = (location-1) % 3;

		// 중복되면 true, 그렇지 않으면 false 반환
		return map[r][c] != 0;
	}

	// map에 선택한 돌 두기
	vector<vector<int>> changeMap(vector<vector<int>> map, int location, int userNum) {
		int r = (location - 1) / 3;
		int c = (location - 1) % 3;

		map[r][c] = userNum;
		return map;
	}

	// 게임 끝 및 승패 결정
	checkFinishGameStruct checkFinishGame(vector<vector<int>> map) {
		checkFinishGameStruct data  = checkFinishGameStruct();
		data.isFinish = true;
		data.whoWin = 0;
		// 게임 끝 검사
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (map[i][j] == 0) {
					data.isFinish = false;
				}
			}
		}
		
		// 일자 승패 검사
		for (int i = 0; i < 3; i++) {
			int count1 = 0, count2 = 0;
			for (int j = 0; j < 3; j++) {
				map[i][j] == 1 ? count1++ : count1 = count1;
				map[i][j] == 2 ? count2++ : count2 = count2;
			}
			if (count1 == 3) {
				data.isFinish = true;
				data.whoWin = 1;
			}
			if (count2 == 3) {
				data.isFinish = true;
				data.whoWin = 2;
			}
			
			count1 = 0, count2 = 0;
			for (int j = 0; j < 3; j++) {
				map[j][i] == 1 ? count1++ : count1 = count1;
				map[j][i] == 2 ? count2++ : count2 = count2;
			}
			if (count1 == 3) {
				data.isFinish = true;
				data.whoWin = 1;
			}
			if (count2 == 3) {
				data.isFinish = true;
				data.whoWin = 2;
			}
		}

		// 대각선 검사
		if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[0][0] == 1) {
			data.isFinish = true;
			data.whoWin = 1;
		}
		if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[0][0] == 2) {
			data.isFinish = true;
			data.whoWin = 2;
		}

		// 무승부 검사
		if (data.isFinish && data.whoWin== 0) {
			data.whoWin = 3;
		}

		return data;
	}

	
};

int main(void) {
	// 배치 번호 map
	vector<vector<int>> userMap
	{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	// 게임 map
	vector<vector<int>> map
	{
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

	TicTacToe t = TicTacToe();

	cout << "시~작!" << endl;
	cout << "--게임 방법--" << endl;
	cout << "1. 유저가 번갈아가면서 1~9 돌 입력하기" << endl;
	cout << "2. 그만하고 싶다면 0 입력" << endl;
	cout << "\n아래처럼 번호가 배치되어있습니다." << endl;
	t.printUserHelpMap(userMap);
	int userNum = 1;
	int userChoice = 0;
	
	while (1) {
		cout << "\n----------------------------" << endl;
		cout << userNum << "번 유저가 입력할 차례입니다." << endl;
		cout << "입력할 돌 번호(1~9): ";
		cin >> userChoice;

		// 게임 중단
		if (userChoice == 0) {
			cout << "게임을 중단합니다." << endl;
			break;
		}

		// 잘못된 배치 번호
		if (userChoice < 0 && userChoice >9) {
			cout << "잘못된 배치 번호입니다. 다시 입력해주세요." << endl;
			continue;
		}

		// 중복 검사
		if (t.checkDuplication(map, userChoice)) {
			cout << "중복된 곳입니다. 다시 입력해주세요." << endl;
			continue;
		}
		
		// map 업데이트
		map = t.changeMap(map, userChoice, userNum);

		// map 출력
		t.printMap(map);

		// 게임 승패 여부 검사
		checkFinishGameStruct result = t.checkFinishGame(map);
		if (result.isFinish) {
			// 1. 무승부 판정
			if (result.whoWin == 3) {
				cout << "무승부입니다." << endl;
				return 0;
			}
			// 2. 승패 판정
			cout <<"축하합니다. " << result.whoWin << "번 유저의 승리입니다." << endl;
			return 0;
		}

		// 유저 번호 변경
		userNum == 1 ? userNum = 2 : userNum = 1;
	}
		
	return 0;
}
