#include <iostream>
#include <vector>

// Tic-Tac-Toe 보드를 저장하는 2차원 벡터
std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));

// 현재 플레이어를 추적하기 위한 변수
char currentPlayer = 'X';

// Tic-Tac-Toe 보드를 출력하는 함수
void PrintBoard() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			std::cout << board[i][j];
			if (j < 2) {
				std::cout << " | ";
			}
		}
		std::cout << std::endl;
		if (i < 2) {
			std::cout << "---------" << std::endl;
		}
	}
	std::cout << std::endl;
}

// 현재 플레이어가 이겼는지 확인하는 함수
bool CheckWin() {
	// 가로, 세로, 대각선 중 하나라도 같은 문자로 채워져 있다면 승리
	for (int i = 0; i < 3; ++i) {
		if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) {
			return true; // 가로로 승리
		}
		if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) {
			return true; // 세로로 승리
		}
	}
	if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) {
		return true; // 왼쪽 위에서 오른쪽 아래로 대각선으로 승리
	}
	if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) {
		return true; // 오른쪽 위에서 왼쪽 아래로 대각선으로 승리
	}
	return false; // 아직 승리하지 않음
}

// 무승부 여부를 확인하는 함수
bool CheckTie() {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i][j] == ' ') {
				return false; // 빈 칸이 있으면 무승부가 아님
			}
		}
	}
	return true; // 모든 칸이 채워져 있으면 무승부
}

int main() {
	std::cout << "Tic-Tac-Toe 게임을 시작합니다!" << std::endl;

	while (true) {
		PrintBoard(); // 보드 출력

		// 현재 플레이어의 차례
		std::cout << "플레이어 " << currentPlayer << "의 차례입니다." << std::endl;

		// 플레이어에게 입력 받기
		int row, col;
		std::cout << "행과 열을 입력하세요 (예: 1 2): ";
		std::cin >> row >> col;

		// 입력 유효성 검사
		if (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
			std::cout << "유효하지 않은 위치입니다. 다시 입력하세요." << std::endl;
			continue;
		}

		// 보드 업데이트
		board[row - 1][col - 1] = currentPlayer;

		// 승리 확인
		if (CheckWin()) {
			PrintBoard(); // 최종 보드 출력
			std::cout << "플레이어 " << currentPlayer << "가 이겼습니다! 축하합니다!" << std::endl;
			break;
		}

		// 무승부 확인
		if (CheckTie()) {
			PrintBoard(); // 최종 보드 출력
			std::cout << "무승부입니다. 게임 종료!" << std::endl;
			break;
		}

		// 다음 플레이어로 넘기기
		currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
	}

	return 0;
}
