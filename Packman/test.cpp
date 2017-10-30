#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

void gotoxy(int x, int y) //�ֿܼ����� Ŀ�� �̵� �Լ�
{
	COORD Pos = { x - 1, y - 1 }; //��ǥ ������ 1�� �����ϰڴٴ� �ǹ� = (1, 1)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //�ܼ��� Ŀ���� ������ ���ڴٴ� �ǹ�
}

int move_monster(int way, int *monster_x, int *monster_y){ //���� ��ǥ �̵� �Լ�
	switch (way)
	{
	case 1: //��
		*monster_y--;
		break;

	case 2: //��
		*monster_x -= 2;
		break;

	case 3: //��
		*monster_x += 2;
		break;

	case 4: //��
		*monster_y++;
		break;
	default:
		return 0;
	}
}



int main()
{
	int stage1[17][20] = { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

	int monster_x, monster_y;
	int monster_input_cnt = 0;
	int monster_location[3][2] = { 0, }; //������ ��ǥ ���� (�ֺ� ��ǥ Ž�� �� ���� ��ġ�� �̵���Ű�� ���ؼ�)

	srand((unsigned)time(0));

	do{ //���� 3���� ���� (��ġ�� ����)
		monster_x = rand() % 17;
		monster_y = rand() % 20;
		if (monster_x != 1 && monster_y != 1){ //�÷��̾� ���� ��ġ�� ��ġ�� �ʵ��� �ϱ� ����
			if (stage1[monster_x][monster_y] == 0){
				stage1[monster_x][monster_y] = 4;
				monster_location[monster_input_cnt][0] = monster_x;
				monster_location[monster_input_cnt][1] = monster_y;
				monster_input_cnt++;
			}
		}
	} while (monster_input_cnt != 3);

	cout << monster_location[0][0] << ", " << monster_location[0][1] << endl;
	cout << monster_location[1][0] << ", " << monster_location[1][1] << endl;
	cout << monster_location[2][0] << ", " << monster_location[2][1] << endl;

	monster_input_cnt = 0;
	int way = 0;
	int i = 0;
	do{
		do{
			if (stage1[monster_location[monster_input_cnt][0]][monster_location[monster_input_cnt][1] + 1] == 0){//��
				way = 3;
				/*stage1[monster_location[monster_input_cnt][0]][monster_location[monster_input_cnt][1]] = 0;
				monster_x = monster_location[monster_input_cnt][0];
				monster_y = monster_location[monster_input_cnt][1];
				Sleep(500);
				gotoxy(monster_x + 1, monster_y + 2);
				cout << "��";
				monster_x = monster_location[monster_input_cnt][0] + 1;//��
				monster_y = monster_location[monster_input_cnt][1] + 0;
				move_monster(way, &monster_x, &monster_y);
				gotoxy(monster_x, monster_y);
				cout << "��";
				stage1[monster_location[monster_input_cnt][0]][monster_location[monster_input_cnt][1] + 1] = 4;*/
				gotoxy(monster_x + 1, monster_y + 2);
				cout << "��";
				monster_x = monster_location[monster_input_cnt][0];
				monster_y = monster_location[monster_input_cnt][1];
				move_monster(way, &monster_x, &monster_y);
				gotoxy(monster_x, monster_y);
				cout << "��";
				/*
				gotoxy(x_tmp, y_tmp);
				cout << "��";
				move_character(key, &player_x, &player_y, X_MAX, Y_MAX);
				gotoxy(player_x, player_y);
				cout << "��";
				*/
			}
			i++;
		} while (i != 15);
		monster_input_cnt++;
	} while (monster_input_cnt != 3);


	return 0;
}