#include <cstdlib>
#include <iostream>
#include <ctime>
#include <conio.h>

#include <windows.h>

#define width 25
#define height 15

#define XPOSITION_ONE 1
#define XPOSITION_TWO (width - 4)
#define YPOSITION_ONE  0
#define YPOSITION_TWO (height / 2)
#define YPOSITION_THREE (height - 3)

bool GAMEOVER;
enum ROTATOR{invalid, move_left_ready, move_right_ready, move_up_ready, move_down_ready};
enum DIRECTION{STOP, LEFT, RIGHT, DOWN, UP};

struct node{
	int x_pos;
	int y_pos;
	DIRECTION BULLET_DIRECTION;
	struct node *next;
};

class bullet{
public:
	void bullet_creation(node *&head, DIRECTION BULLET, int x, int y){
		node *new_bullet = NULL;
		new_bullet = new node;
		switch(BULLET){
			case LEFT:
				new_bullet->x_pos = x - 1;
				new_bullet->y_pos = y;
				break;
			case RIGHT:
				new_bullet->x_pos = x + 1;
				new_bullet->y_pos = y;
				break;
			case DOWN:
				new_bullet->x_pos = x;
				new_bullet->y_pos = y + 1;
				break;
			case UP:
				new_bullet->x_pos = x;
				new_bullet->y_pos = y - 1;
				break;
			default:
				new_bullet->x_pos = x;
				new_bullet->y_pos = y - 1;
				break;
		}
		new_bullet->BULLET_DIRECTION = BULLET;
		new_bullet->next = NULL;
		if(head == NULL){
			head = new_bullet;
		}
		else{
			node *temp = head;
			while(temp->next != NULL) temp = temp->next;
			temp->next = new_bullet;
		}
	}
	
	void bullet_mover(node *head){
		node *pointer = head;
		while(pointer != NULL){
			switch(pointer->BULLET_DIRECTION){
				case LEFT:
					pointer->x_pos--;
					break;
				case RIGHT:
					pointer->x_pos++;
					break;
				case DOWN:
					pointer->y_pos++;
					break;
				case UP:
					pointer->y_pos--;
					break;
				default:
					break;
			}
			pointer = pointer->next;
		}
	}
	
	void bullet_destoyer(node *&head){//this should destroy any bullet that has heat the wall or target
		node *pointer = head;
		node *prev = head;
		while(pointer != NULL){
			if(pointer->y_pos < 0 && pointer->BULLET_DIRECTION == UP){
				node *deleter = NULL;
				deleter = pointer;
				prev = pointer->next;
				delete deleter;
			}
			else if(pointer->y_pos > height && pointer->BULLET_DIRECTION == DOWN){
				node *deleter = NULL;
				deleter = pointer;
				prev = pointer->next;
				delete deleter;
			}
			else if(pointer->x_pos > width - 1  && pointer->BULLET_DIRECTION == RIGHT){
				node *deleter = NULL;
				deleter = pointer;
				prev = pointer->next;
				delete deleter;
			}
			else if(pointer->x_pos < 0 && pointer->BULLET_DIRECTION == LEFT){
				node *deleter = NULL;
				deleter = pointer;
				prev = pointer->next;
				delete deleter;
			}
			prev = pointer;
			pointer = pointer->next;
		}
	}
};

class player{
private:
	ROTATOR move;
	DIRECTION movement, setter;
	int x_pos, y_pos;
	int player[3][3];
	bullet shooter;
	
public:
	node *gun_head = NULL;
	int gety(){return y_pos;}
	
	init(){
		movement = STOP;
	    setter = UP;
	    player[0][0] = 1000; player[0][1] = x_pos + 1; player[0][2] = 1000; player[1][0] = x_pos + 0; player[1][1] = x_pos + 1; player[1][2] = x_pos + 2; player[2][0] = x_pos + 0; player[2][1] = x_pos + 1; player[2][2] = x_pos + 2;
	}
	
	void variable(){
		if(setter == RIGHT){player[0][0] = x_pos + 0; player[2][0] = x_pos + 0; player[0][1] = x_pos + 1; player[1][0] = x_pos + 0; player[1][1] = x_pos + 1; player[1][2] = x_pos + 2; player[2][1] = x_pos + 1;}
		else if(setter == LEFT){player[0][2] = x_pos + 2; player[2][2] = x_pos + 2; player[0][1] = x_pos + 1; player[1][0] = x_pos + 0; player[1][1] = x_pos + 1; player[1][2] = x_pos + 2; player[2][1] = x_pos + 1;}
		else if(setter == DOWN){player[0][0] = x_pos + 0;	player[0][2] = x_pos + 2; player[0][1] = x_pos + 1; player[1][0] = x_pos + 0; player[1][1] = x_pos + 1; player[1][2] = x_pos + 2; player[2][1] = x_pos + 1;}
		else{player[2][0] = x_pos + 0; player[2][2] = x_pos + 2; player[0][1] = x_pos + 1; player[1][0] = x_pos + 0; player[1][1] = x_pos + 1; player[1][2] = x_pos + 2; player[2][1] = x_pos + 1;}
	}
	
	ROTATOR rotator(DIRECTION movement){
		if(movement == LEFT){player[0][0] = 1000; player[2][0] = 1000; player[0][2] = x_pos + 2; player[2][2] = x_pos + 2; setter = LEFT;
			return move_left_ready;
		}
		else if(movement == RIGHT){player[0][0] = x_pos + 0; player[2][0] = x_pos + 0; player[0][2] = 1000;	player[2][2] = 1000; setter = RIGHT;
			return move_right_ready;
		}
		else if(movement == DOWN){player[0][0] = x_pos + 0; player[2][0] = 1000; player[0][2] = x_pos + 2; player[2][2] = 1000; setter = DOWN;
			return move_down_ready;
		}
		else if(movement == UP){	player[0][0] = 1000; player[2][0] = x_pos + 0; player[0][2] = 1000; player[2][2] = x_pos + 2; setter = UP;
			return move_up_ready;
		}
		else return invalid;
	}
	
	int x_player(int row, int col){
		if(player[row][col] == 0) return 1000;
		else return player[row][col];
	}
	void input(){
		int x, y;
		if (GetAsyncKeyState(VK_UP)){
			if(move != move_up_ready){
				move = rotator(UP);
			}
			else movement = UP;
		}
		else if (GetAsyncKeyState(VK_DOWN)){
			if(move != move_down_ready){
				move = rotator(DOWN);
			}
			else movement = DOWN;
		}
		else if (GetAsyncKeyState(VK_LEFT)){
			if(move != move_left_ready){
				move = rotator(LEFT);
			}
			else movement = LEFT;
		}
		else if (GetAsyncKeyState(VK_RIGHT)){
			if(move != move_right_ready){
				move = rotator(RIGHT);
			}
			else movement = RIGHT;
		}
		else movement = STOP;
		if(kbhit()){
			if(getch() == 's'){
				switch(setter){
					case LEFT:
						shooter.bullet_creation(gun_head, LEFT, player[1][0], gety() + 1);
						break;
					case RIGHT:
						shooter.bullet_creation(gun_head, RIGHT, player[1][2], gety() + 1);
						break;
					case DOWN:
						shooter.bullet_creation(gun_head, DOWN, player[2][1], gety() + 2);
						break;
					case UP:
						shooter.bullet_creation(gun_head, UP, player[0][1], gety());
						break;
					default:
						break;
				}
			}
		}
	}
	
	void control(){
		switch(movement){
			case LEFT:  x_pos--; break;
			case RIGHT: x_pos++; break;
			case UP: y_pos--; break;
			case DOWN: y_pos++; break;
		} movement = STOP;
	
		if(x_pos == 0) x_pos = 1;
		else if(x_pos == width - 3) x_pos = width - 4;
		else if(y_pos == -1) y_pos = 0;
		else if(y_pos == height - 2) y_pos = height - 3;
	}
	
	void mover(){shooter.bullet_mover(gun_head);}
};

class CHALLENGERS{
private:
	ROTATOR FIRST_PLAYER_MOVE;
	DIRECTION FIRST_PLAYER_MOVEMENT, FIRST_PLAYER_SETTER;
	int FIRST_PLAYER_X_POSITION[3][3], X_CHA;
	bullet shooter;
	
public:
	node *gun_head = NULL;
	int FIRST_PLAYER_Y_POSITION;
	
	void FIRST_INIT(int x_position, int y_position, DIRECTION SETTER_CONTROL){
		X_CHA = x_position;
		FIRST_PLAYER_MOVEMENT = STOP;
	    FIRST_PLAYER_SETTER = SETTER_CONTROL;
	    FIRST_PLAYER_Y_POSITION = y_position;
		FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[2][1] = 1000; FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[2][0] = X_CHA; FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = X_CHA + 1; FIRST_PLAYER_X_POSITION[1][2] = FIRST_PLAYER_X_POSITION[2][2] = X_CHA + 2;
	}
	
	void FIRSTPLAYERVARIABLE(){
		if(FIRST_PLAYER_SETTER == RIGHT){
		FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[2][2] = 1000;
		FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[2][0] = X_CHA;
		FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
		FIRST_PLAYER_X_POSITION[1][2] = X_CHA + 2;
		}
	
		else if(FIRST_PLAYER_SETTER == LEFT){
		FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[1][2] =	FIRST_PLAYER_X_POSITION[2][0] = 1000;
		FIRST_PLAYER_X_POSITION[1][0] = X_CHA;
		FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
		FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[2][2] = X_CHA + 2;
		}
	
		else if(FIRST_PLAYER_SETTER == DOWN){
		FIRST_PLAYER_X_POSITION[2][2] = FIRST_PLAYER_X_POSITION[2][0] = FIRST_PLAYER_X_POSITION[0][1] = 1000;
		FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[0][0] = X_CHA;
		FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
		FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[1][2] =X_CHA + 2;
		}
	
		else{
		FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[2][1] = FIRST_PLAYER_X_POSITION[0][2] = 1000;
		FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = X_CHA + 1;
		FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[2][0] = X_CHA;
		FIRST_PLAYER_X_POSITION[1][2] = FIRST_PLAYER_X_POSITION[2][2] = X_CHA + 2;
		}
	}
	
	ROTATOR FIRST_PLAYER_ROTATOR(DIRECTION FIRST_PLAYER_MOVEMENT){
		if(FIRST_PLAYER_MOVEMENT == LEFT){
			FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[1][2] =	FIRST_PLAYER_X_POSITION[2][0] = 1000;
			FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
			FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[2][2] = X_CHA + 2;
			FIRST_PLAYER_X_POSITION[1][0] = X_CHA;
			FIRST_PLAYER_SETTER = LEFT;
			return move_left_ready;
		}
		else if(FIRST_PLAYER_MOVEMENT == RIGHT){
			FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[2][0] = X_CHA;
			FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[2][2] = 1000;
			FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
			FIRST_PLAYER_X_POSITION[1][2] = X_CHA + 2;
			FIRST_PLAYER_SETTER = RIGHT;
			return move_right_ready;
		}
	
		else if(FIRST_PLAYER_MOVEMENT == DOWN){
			FIRST_PLAYER_X_POSITION[2][2] = FIRST_PLAYER_X_POSITION[2][0] = FIRST_PLAYER_X_POSITION[0][1] = 1000;
			FIRST_PLAYER_X_POSITION[0][2] = FIRST_PLAYER_X_POSITION[1][2] =X_CHA + 2;
			FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[0][0] = X_CHA;
			FIRST_PLAYER_X_POSITION[1][1] = FIRST_PLAYER_X_POSITION[2][1] = X_CHA + 1;
			FIRST_PLAYER_SETTER = DOWN;
			return move_down_ready;
		}
	
		else if(FIRST_PLAYER_MOVEMENT == UP){
			FIRST_PLAYER_X_POSITION[0][0] = FIRST_PLAYER_X_POSITION[2][1] = FIRST_PLAYER_X_POSITION[0][2] = 1000;
			FIRST_PLAYER_X_POSITION[0][1] = FIRST_PLAYER_X_POSITION[1][1] = X_CHA + 1;
			FIRST_PLAYER_X_POSITION[1][0] = FIRST_PLAYER_X_POSITION[2][0] = X_CHA;
			FIRST_PLAYER_X_POSITION[1][2] = FIRST_PLAYER_X_POSITION[2][2] = X_CHA + 2;
			FIRST_PLAYER_SETTER = UP;
			return move_up_ready;
		}
		else return invalid;
	}
	
	int FIRST_PLAYER_X_POSITION_CHALLENGER(int row, int col){
		if(FIRST_PLAYER_X_POSITION[row][col] == 0) return 1000;
		else return FIRST_PLAYER_X_POSITION[row][col];
	}
	
	void state_input(){
		srand(rand());
		if(rand() % 5 == UP){
			if(FIRST_PLAYER_MOVE != move_up_ready){
				FIRST_PLAYER_MOVE = FIRST_PLAYER_ROTATOR(UP);
			}
			else FIRST_PLAYER_MOVEMENT = UP;
		}
		else if(rand() % 5 == DOWN){
			if(FIRST_PLAYER_MOVE != move_down_ready){
				FIRST_PLAYER_MOVE = FIRST_PLAYER_ROTATOR(DOWN);
			}
			else FIRST_PLAYER_MOVEMENT = DOWN;
		}
		else if(rand() % 5 == RIGHT){
			if(FIRST_PLAYER_MOVE != move_right_ready){
				FIRST_PLAYER_MOVE = FIRST_PLAYER_ROTATOR(RIGHT);
			}
			else FIRST_PLAYER_MOVEMENT = RIGHT;
		}
		else if(rand() % 5 == LEFT){
			if(FIRST_PLAYER_MOVE != move_left_ready){
				FIRST_PLAYER_MOVE = FIRST_PLAYER_ROTATOR(LEFT);
			}
			else FIRST_PLAYER_MOVEMENT = LEFT;
		}
		else FIRST_PLAYER_MOVEMENT = STOP;
		
		if(kbhit()){
			if(getch() == 65){
				getch();
				DIRECTION TRIAL = LEFT;
				FIRST_PLAYER_MOVEMENT = STOP;
				switch(TRIAL/*FIRST_PLAYER_SETTER*/){
					case LEFT:
						shooter.bullet_creation(gun_head, LEFT, FIRST_PLAYER_X_POSITION[1][0], FIRST_PLAYER_Y_POSITION + 1);
						getch();
						break;
					case RIGHT:
						shooter.bullet_creation(gun_head, RIGHT, FIRST_PLAYER_X_POSITION[1][2], FIRST_PLAYER_Y_POSITION + 1);
						break;
					case DOWN:
						shooter.bullet_creation(gun_head, DOWN, FIRST_PLAYER_X_POSITION[2][1], FIRST_PLAYER_Y_POSITION + 2);
						break;
					case UP:
						shooter.bullet_creation(gun_head, UP, FIRST_PLAYER_X_POSITION[0][1], FIRST_PLAYER_Y_POSITION);
						break;
					default:
						getch();
						break;
				}
			}
		}
	}
	
	FIRSTPLAYERCONTROL(){
	switch(FIRST_PLAYER_MOVEMENT){
			case LEFT:
				X_CHA--;
				break;
			case RIGHT:
				X_CHA++;
				break;
			case DOWN:
				FIRST_PLAYER_Y_POSITION++;
				break;
			case UP:
				FIRST_PLAYER_Y_POSITION--;
				break;
			default:
				break;
		}FIRST_PLAYER_MOVEMENT = STOP;

		if(X_CHA == 0) X_CHA = 1;
		else if(X_CHA == width - 3) X_CHA = width - 4;
		else if(FIRST_PLAYER_Y_POSITION == -1) FIRST_PLAYER_Y_POSITION = 0;
		else if(FIRST_PLAYER_Y_POSITION == height - 2) FIRST_PLAYER_Y_POSITION = height - 3;
	}
	
	void mover(){shooter.bullet_mover(gun_head);}
	
	void caller(){
		FIRSTPLAYERVARIABLE();
		state_input();
		FIRSTPLAYERCONTROL();
		mover();
	}
};
