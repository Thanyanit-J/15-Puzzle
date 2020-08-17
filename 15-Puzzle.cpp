#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void print_instruction();
void print_board_info();
void reset_board();
void draw_board();
void get_input();
void shift(char direction[5] /* "up", "down", "left", "right" */);
void swap(int row1, int col1, int row2, int col2);
void shuffle();

//////////////////////////////////////////////////////////////////////////

#define ALLOW_PRINT_BOARD_INFO false
#define BOARD_SIZE 4
#define NUMBER_OF_SHUFFLE 2500

//////////////////////////////////////////////////////////////////////////

int board[BOARD_SIZE][BOARD_SIZE];
int row_space, col_space;
bool isEnd = false;

int main(){
	reset_board();
	get_input();
	while(!isEnd){
		get_input();
	}
	return 0;
}

void print_instruction(){
		printf("PRESS AN ARROW KEY TO SHIFT THE NUMBER.\n");
		printf("PRESS 'S' TO SHUFFLE THE BOARD.\n");
		printf("PRESS 'R' TO RESET.\n");
		printf("PRESS 'Q' TO EXIT.\n");
		printf("\n");
}

void print_board_info(){
	if(ALLOW_PRINT_BOARD_INFO)
	printf("Row space: %d\nCol space: %d\n",row_space, col_space);
}

void reset_board(){
	system("cls");
	print_instruction();
	for(int row = 0; row < BOARD_SIZE; row++){
		for(int col = 0; col < BOARD_SIZE; col++){
			board[row][col] = (row * BOARD_SIZE) + (col + 1);
			if(board[row][col] == pow(BOARD_SIZE, 2)){
				row_space = row;
				col_space = col;
				board[row][col] = 0;
				printf(" * ");
			}
			else
				printf("%2d ", board[row][col]);
		}
		printf("\n");
	}
	printf("\n");
	print_board_info();
}

void draw_board(){
	system("cls");
	print_instruction();
	for(int row = 0; row < BOARD_SIZE; row++){
		for(int col = 0; col < BOARD_SIZE; col++){
			if(board[row][col] == 0){
				printf(" * ");
			}
			else
				printf("%2d ", board[row][col]);
		}
		printf("\n");
	}
	printf("\n");
	print_board_info();
}

void get_input(){
	char input = getch();
	// This checks for Arrow key input.
	// getch() function return two key codes for Arrow keys which are -32 and then 72, 80, 75, or 77.
	// Thus, use getch() two times: one for checking for -32 and another for one of the four directions.
	if (input == -32) {
		input = getch();
	    switch(input) { // the real value
	        case 72:
	            // code for arrow up
	            shift("up");
	            break;
	        case 80:
	            // code for arrow down
	            shift("down");
	            break;
	        case 75:
	            // code for arrow left
	            shift("left");
	            break;
	        case 77:
	            // code for arrow right
	            shift("right");
	            break;
	        default: {
	        	printf("INVALID INPUT\n");
				return;
			}
	    }
	    draw_board();
	}
	// Receive normal input
	else if(input == 'q' || input == 'Q')
		isEnd = true;
	else if(input == 'r' || input == 'R')
		reset_board();
	else if(input == 's' || input == 'S')
		shuffle();	
}

void shift(char direction[5] /* up, down, left, right */){
	direction = strlwr(direction);
	if(direction == "up"){
		if(row_space >= 0  && row_space < BOARD_SIZE-1){
			swap(row_space, col_space, row_space + 1, col_space);
		}
	}
	else if(direction == "down"){
		if(row_space > 0 && row_space < BOARD_SIZE){
			swap(row_space, col_space, row_space - 1, col_space);
		}
	}
	else if(direction == "left"){
		if(col_space >= 0 && col_space < BOARD_SIZE-1){
			swap(row_space, col_space, row_space, col_space + 1);
		}
	}
	else if(direction == "right"){
		if(col_space > 0 && col_space < BOARD_SIZE){
			swap(row_space, col_space, row_space, col_space - 1);
		}
	}
	else {
		printf("INVALID DIRECTION.\n");
		return;
	}
}

void swap(int row1, int col1, int row2, int col2){
	int temp = board[row1][col1];
	board[row1][col1] = board[row2][col2];
	board[row2][col2] = temp;
	
	if(board[row1][col1] == 0){
		row_space = row1;
		col_space = col1;
	}
	if(board[row2][col2] == 0){
		row_space = row2;
		col_space = col2;
	}
}

void shuffle(){
	// Use current time as seed for random generator 
	srand(time(0));
	for(int i = 0; i < NUMBER_OF_SHUFFLE; i++){
		switch(rand()%4) {
			case 0:
				shift("up");
				break;
			case 1:
				shift("down");
				break;
			case 2:
				shift("left");
				break;
			case 3:
				shift("right");
				break;
		}
	}
	draw_board();
}


