#include <stdio.h>
#include <easyx.h>
#include <graphics.h>
#include<string.h>
#include <iostream>
#define GRID_W 25
#define SPACE (3*GRID_W)

enum Chess {
	None,
	Black,
	White,
};
struct Pos {
	int row;
	int col;
	bool isShow;
	int player;
}pos = { -1, - 1,false,Black};
//0 means none, 1 means black, 2 means white
int map[15][15];

//Background Image
IMAGE background;
void loadR() {
	loadimage(&background, "background.jpg");
}
void draw(){

	putimage(0, 0, &background);
	//Lines
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 1);
	for (int i = 0;i < 15;i++) {
		line(SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE, i * GRID_W + SPACE);
		line(i * GRID_W + SPACE, SPACE, i * GRID_W + SPACE, 14 * GRID_W + SPACE);
	}
	setlinestyle(PS_SOLID, 3);
	rectangle(SPACE, SPACE, SPACE + 14 * GRID_W, SPACE + 14 * GRID_W);
	setfillcolor(BLACK);
	solidcircle(SPACE + 7 * GRID_W, SPACE + 7 * GRID_W, 4);
	for(int i = 0;i < 15;i++) {
		for (int j = 0;j < 15;j++) {
			if (map[i][j] == Black) {
				setfillcolor(BLACK);
				solidcircle(j * GRID_W + SPACE, i * GRID_W + SPACE, 8);
			}
			else if (map[i][j] == White) {
				setfillcolor(WHITE);
				solidcircle(j * GRID_W + SPACE, i * GRID_W + SPACE, 8);
			}
		}
	}
	setlinecolor(BLUE);
	if (pos.isShow) {
		rectangle(pos.col*GRID_W+SPACE-12, pos.row * GRID_W + SPACE -12, pos.col * GRID_W + SPACE + 12, pos.row * GRID_W + SPACE + 12);
	}
}
void mouseMoveMsg(ExMessage* msg) {
	for (int i = 0;i < 15;i++) {
		for (int j = 0;j < 15;j++) {
			int gridx = j * GRID_W + SPACE;
			int gridy = i * GRID_W + SPACE;
			if (abs(msg->x - gridx) <= 12 && abs(msg->y - gridy) <= 12) {
				pos.isShow = true;
				pos.row = i;
				pos.col = j;
			}
		}
	}

}

bool judge(int r, int c, int player) {
	std::cout << player<< std::endl;
	for (int i = c - 4; i < c; i++) {
		if (i >= 0 && i < 15 && map[r][i] == player && map[r][i + 1] == player && map[r][i + 2] == player && map[r][i + 3] == player && map[r][i + 4] == player) {
			return true;
		}
	}
	for (int i = c ; i < c+5; i++) {
		if (i >= 0 && i < 15 && map[r][i] == player && map[r][i - 1] == player && map[r][i - 2] == player && map[r][i - 3] == player && map[r][i - 4] == player) {
			return true;
		}
	}
	for (int i = r - 4; i < r; i++) {
		if (i >= 0 && i < 15 && map[i][c] == player && map[i+1][c] == player && map[i+2][c] == player && map[i+3][c] == player && map[i+4][c] == player) {
			return true;
		}
	}
	for (int i = r; i < r+5; i++) {
		if (i >= 0 && i < 15 && map[i][c] == player && map[i - 1][c] == player && map[i - 2][c] == player && map[i - 3][c] == player && map[i - 4][c] == player) {
			return true;
		}
	}
	for (int i = r; i < r + 5; i++) {
		for (int j = c; j < c + 5; j++) {
			if (i >= 0 && i < 15 && map[i][j] == player && map[i - 1][j - 1] == player && map[i - 2][j - 2] == player && map[i - 3][j - 3] == player && map[i - 4][j - 4] == player) {
				return true;
			}
		}
	}

	for (int i = r-4; i < r; i++) {
		for (int j = c-4; j < c; j++) {
			if (i >= 0 && i < 15 && map[i][j] == player && map[i + 1][j + 1] == player && map[i + 2][j + 2] == player && map[i + 3][j + 3] == player && map[i + 4][j + 4] == player) {
				return true;
			}
		}
	}
	
	return false;
}
void mousePressMsg(ExMessage* msg) {
	if (map[pos.row][pos.col] != 0) {
		return;
	}
	if (msg->message == WM_LBUTTONDOWN) {
		map[pos.row][pos.col] = pos.player;
		//Check if win
		if (judge(pos.row, pos.col,pos.player)) {
			MessageBox(GetHWnd()," You Win!", "hit", MB_OK);
			exit(666);
		}
		//switch player
		pos.player = (pos.player == Black ? White : Black);
	}
}



int main() {
	//create window
	initgraph(600,500,EW_SHOWCONSOLE);
	loadR();
	while (true) {
		BeginBatchDraw();
		draw();
		EndBatchDraw();
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE)) {
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				mouseMoveMsg(&msg);
				break;
			case WM_LBUTTONDOWN: //left key click
				mousePressMsg(&msg);
				break;

			default:
				break;
			}
			
		}
	}
	getchar();
	return 0;
}