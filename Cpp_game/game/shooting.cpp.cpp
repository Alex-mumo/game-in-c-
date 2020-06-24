#include <iostream>
#include <conio.h>
#include "player.h"

using namespace std;

player staring;
CHALLENGERS challenger_one, challenger_two, challenger_three, challenger_four;

void innitial(){
	srand((unsigned)time(NULL));
    GAMEOVER = false;
    x_pos = (width / 2) - 1;
    y_pos = (height / 2);
}

void drawing(){
    system("cls");
    system("color 05");
    bool PRINT;
    bool ANOTHER_PRINT, TWO_PRINT, THREE_PRINT, FOUR_PRINT, bullet_print;
    for(int haxis = 0; haxis < width; haxis++) printf ("\xDC");
    printf ("\n");

    for(int vaxis = 0; vaxis < height; vaxis++){
        for(int haxis = 0; haxis < width; haxis++){
            if (haxis == 0) printf ("\xDB");
            else if(haxis == width - 1) printf ("\xDB");
            else{
            	node *pointer = kichwa;
            	PRINT = bullet_print = ANOTHER_PRINT = TWO_PRINT = THREE_PRINT = FOUR_PRINT = false;
            	for(int row = 0; row < 3; row++){
            		for(int col = 0; col < 3; col++){
            			if(haxis == staring.x_player(row, col) && vaxis == y_pos + row){
							printf("0");
							PRINT = true;
						}
						if(haxis == challenger_one.FIRST_PLAYER_X_POSITION_CHALLENGER(row, col) && vaxis == challenger_one.FIRST_PLAYER_Y_POSITION + row){
							printf("0");
							ANOTHER_PRINT = true;
						}
						if(haxis == challenger_two.FIRST_PLAYER_X_POSITION_CHALLENGER(row, col) && vaxis == challenger_two.FIRST_PLAYER_Y_POSITION + row){
							printf("0");
							TWO_PRINT = true;
						}
						if(haxis == challenger_three.FIRST_PLAYER_X_POSITION_CHALLENGER(row, col) && vaxis == challenger_three.FIRST_PLAYER_Y_POSITION + row){
							printf("0");
							THREE_PRINT = true;
						}
						if(haxis == challenger_four.FIRST_PLAYER_X_POSITION_CHALLENGER(row, col) && vaxis == challenger_four.FIRST_PLAYER_Y_POSITION + row){
							printf("0");
							FOUR_PRINT = true;
						}
						while(pointer != NULL){
							if(haxis == pointer->x_pos && vaxis == pointer->y_pos){
								cout << "x";
								bullet_print = true;
							}
							pointer = pointer->next;
						}
					}
				}
				if(!PRINT && !ANOTHER_PRINT && !TWO_PRINT && !THREE_PRINT && !FOUR_PRINT) printf(" ");
			}
        }
        printf ("\n");
    }

    for(int haxis = 0; haxis < width; haxis++) printf ("\xDF");
    printf ("\n");

    printf ("%d::%d", x_pos, y_pos);
}

int main(){
	bool Nshoot;
	
    innitial();
    staring.init();
    challenger_one.FIRST_INIT(XPOSITION_ONE, YPOSITION_ONE, DOWN); challenger_two.FIRST_INIT(XPOSITION_ONE, YPOSITION_THREE, UP);
    challenger_three.FIRST_INIT(XPOSITION_TWO, YPOSITION_ONE, LEFT); challenger_four.FIRST_INIT(XPOSITION_TWO, YPOSITION_THREE, RIGHT);

    while(!GAMEOVER){
    	if(kichwa == NULL) kichwa = staring.returnhead();
    	srand((unsigned)time(NULL));
		staring.variable(); Nshoot = staring.input(); staring.control();
		if(Nshoot == true){
			int xxx;
			int yyy = staring.gety();
			if(staring.getmovement() == LEFT){
				xxx = staring.getx_left();
				staring.main_bullet(Nshoot, LEFT, xxx, yyy);
			}
			else if(staring.getmovement() == RIGHT){
				xxx = staring.getx_right();
				staring.main_bullet(Nshoot, RIGHT, xxx, yyy);
			}
			else if(staring.getmovement() == DOWN){
				xxx = staring.getx_down();
				staring.main_bullet(Nshoot, DOWN, xxx, yyy);
			}
			else{
				xxx = staring.getx_up();
				staring.main_bullet(Nshoot, UP, xxx, yyy);
			}
		}
		staring.main_bullet_mover();
		challenger_one.caller(); challenger_two.caller(); challenger_three.caller(); challenger_four.caller();
		drawing();
		if(Nshoot == true) cout << "shooting in progress" << endl;
		else cout << "shooting not in progress" << endl;
		if (kichwa != NULL)cout << kichwa->x_pos << " " << kichwa->y_pos << endl;
		else cout << "NULL" << endl;
		Sleep(100);
	}
    return 0;
}
