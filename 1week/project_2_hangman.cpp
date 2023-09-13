#include <iostream>
#include <string>
#include <random>
#include <set>
using namespace std;

class CheckingAnswerStruct {
public:
	bool isChange;
	vector<bool> answer;
	void create(int s) {
		for (int i = 0; i < s; i++) {
			answer.push_back(false);
		}
	}
};

class Hangman {
public:
	//solution을 하나 결정
	string selectWord(void) {
		string wordList[] = {
		"vector",
		"programming",
		"language",
		"cpp",
		"string",
		"hangman",
		"object",
		"class",
		"oriented",
		"computer",
		"embedded"
		};

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(0, size(wordList)-1);
		return wordList[dis(gen)];
	}

	void printHangman(int count) {
		switch (count) {
		case 0:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|   -|-" << endl;
			cout << "|   /|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 1:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|   -|-" << endl;
			cout << "|   /" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 2:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|   -|-" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 3:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|   -|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 4:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|    |" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 5:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    O" << endl;
			cout << "|    " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		case 6:
			cout << "----------" << endl;
			cout << "|    |" << endl;
			cout << "|    " << endl;
			cout << "|    " << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			cout << "|" << endl;
			break;
		}	
	}

	CheckingAnswerStruct checkWord(string solution, vector<bool> oneHotAnswer, char userChoice) {
		CheckingAnswerStruct c;
		c.create(size(solution));
		c.isChange = false;
		c.answer = oneHotAnswer;
		for (int i = 0; i < size(solution); i++) {
			// 이전에 발견하지 못했던 정답을 찾았을 때
			if (solution[i] == userChoice && oneHotAnswer[i] == false) {
				c.isChange = true;
				c.answer[i] = true;
			}
		}
		return c;
	}

	void showSolution(string solution, vector<bool> onehot) {
		for (int i = 0; i < size(solution); i++) {
			onehot[i] == true ? cout << solution[i] : cout << "_";
		}
		cout << "\n";
		return;
	}
};
int main(void) {

	while (1) {
		char userChoice;
		Hangman h = Hangman();

		// solution 하나 random하게 결정
		string solution = h.selectWord();
		int count = 0;
		vector<bool> oneHotAnswer(size(solution));
		set<char> s;
		for (int i = 0; i < size(solution); i++) {
			oneHotAnswer[i] = false;
		}

		cout << "Hangman 게임 시~작!" << endl;
		cout << "--게임 방법--" << endl;
		cout << "1. 기회는 6번!" << endl;
		cout << "2. 알파벳을 하나씩 입력해주세요." << endl;
		cout << "3. 그만하고 싶다면, 0을 입력해주세요." << endl;
		cout << "\n이번 단어의 글자수는 " << size(solution) << "글자입니다!" << endl;

		// 행맨 그리기
		h.printHangman(0);

		while(1){
			cout << "------------------------------" << endl;
			// 문자 하나씩 입력 받기
			cout << "알파벳을 입력해주세요: ";
			cin >> userChoice;

			// 게임 종료
			if (userChoice == '0') {
				cout << "게임을 종료합니다." << endl;
				return 0;
			}

			// 문자 하나 검사하기
			CheckingAnswerStruct c;
			c.isChange = false;
			c.answer = vector<bool>(size(solution));
			bool isFinish = true;
			c = h.checkWord(solution, oneHotAnswer, userChoice);
			 
			// 끝났는지 검사
			for (int i = 0; i < size(solution); i++) {
				c.answer[i] == false ? isFinish = false : isFinish= isFinish;
			}
			if (isFinish) {
				cout << "축하드립니다! 맞추셨습니다^_^\n\n" << endl;
				break;
			}
			if (c.isChange == false) {
				cout << "중복되었거나, 틀렸습니다." << endl;
				count++;
			}
			if (c.isChange == true) {
				cout << "맞추기 성공!" << endl;
			}
			// 행맨 그리기
			h.printHangman(count);

			// 맞추고 있는 solution 출력
			h.showSolution(solution, c.answer);

			oneHotAnswer = c.answer;
			if (count == 6) {
				cout << "Lose!\n\n" << endl;
				break;
			}
		}

		
	}

	return 0;
}
