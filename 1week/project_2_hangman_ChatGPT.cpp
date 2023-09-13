#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 사전 단어 목록
vector<string> wordList = {
	"apple",
	"banana",
	"cherry",
	"grape",
	"orange",
	"strawberry",
	"watermelon",
	"pineapple",
	"blueberry",
	"raspberry"
};

// 무작위 단어 선택 함수
string getRandomWord() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int randomIndex = rand() % wordList.size();
	return wordList[randomIndex];
}

// 단어 비밀 처리 함수
string hideWord(const string& word, const string& guessedLetters) {
	string hiddenWord = word;
	for (char& letter : hiddenWord) {
		if (guessedLetters.find(letter) == string::npos) {
			letter = '_';
		}
	}
	return hiddenWord;
}

int main() {
	// 게임 초기화
	string secretWord = getRandomWord();
	string guessedLetters;
	int maxAttempts = 6;
	int attemptsLeft = maxAttempts;

	cout << "Welcome to Hangman!" << endl;

	while (attemptsLeft > 0) {
		// 현재 단어 상태 표시
		string currentGuess = hideWord(secretWord, guessedLetters);
		cout << "Current word: " << currentGuess << endl;

		// 입력 받기
		cout << "Guess a letter: ";
		char guess;
		cin >> guess;

		// 이미 추측한 글자인지 확인
		if (guessedLetters.find(guess) != string::npos) {
			cout << "You already guessed that letter." << endl;
			continue;
		}

		// 추측한 글자 추가
		guessedLetters += guess;

		// 정답 확인
		if (secretWord.find(guess) != string::npos) {
			cout << "Correct guess!" << endl;
		}
		else {
			cout << "Wrong guess. Attempts left: " << --attemptsLeft << endl;
		}

		// 게임 종료 조건 확인
		if (secretWord == hideWord(secretWord, guessedLetters)) {
			cout << "Congratulations! You guessed the word: " << secretWord << endl;
			break;
		}
	}

	if (attemptsLeft == 0) {
		cout << "You ran out of attempts. The word was: " << secretWord << endl;
	}

	return 0;
}
