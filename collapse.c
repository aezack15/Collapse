//compile with: gcc -o c collapse.c -lm
//-lm allows you to link with math library

#include "collapse.h"

double score=0;
int counter=0;

int main(){
	bool playAgain=true;
	while(playAgain==true){
		gameBoard gb=setDifficulty();
		gamePiece** board=createBoard(gb);
		bool stillHaveMoves=true;
		displayBoard(gb.rows,gb.cols,board,score);
			while(stillHaveMoves==true)
    			{
				boardIndex bi=getMove(gb.rows,gb.cols,board);
				while(legalMove(board,bi,gb)==false)
    				{
					printf("Invalid move\n");
					bi=getMove(gb.rows,gb.cols,board);
				}
				gamePiece piece=board[bi.row][bi.col];
				score+=removePieces(board,bi.row,bi.col,piece.item,gb,0,0);
				collapse(board,gb);
				compress(board,gb);
				setCompletedCols(board,gb);
				setVisited(board,gb);
				stillHaveMoves=anyMoveRemaining(board,gb);
			}
			playAgain=anotherTry(board,gb);
			if(playAgain==true)
    			{
				free(board);
			}
		stillHaveMoves=playAgain;
	}
}

gameBoard setDifficulty(){
	printf("Welcome to Capt Zack's Console Collapse!\n");
	printf("You should maximize this window before continuing.\n");
	printf("Please choose your difficulty; incorrect selection will default to difficulty 1.\n");
	printf("1. Easy\n");
	printf("2. Medium\n");
	printf("3. Hard\n");
	printf("4. Insane\n");
	printf("> ");
	gameBoard gb;
	int temp;
	char term;
	if(scanf("%d%c",&temp,&term)!= 2||term!='\n'){ //make sure only 1 valid int is read
		  temp=0;
	}
	system("clear");
	if(temp<=0||temp>4){
		printf("Bad input\n");
		printf("Defaulting to Level 1\n");
		printf("- Rows: 8\n- Cols: 8\n- Colors: 3\n");
		printf("\n");
		gb.rows=8;
		gb.cols=8;
		gb.colors=3;
		return gb;
	}
	if(temp==1){
		printf("Level 1\n");
		printf("- Rows: 8\n- Cols: 8\n- Colors: 3\n");
		printf("\n");
		gb.rows=8;
		gb.cols=8;
		gb.colors=3;
		return gb;
	}
	if(temp==2){
		printf("Level 2\n");
		printf("- Rows: 10\n- Cols: 14\n- Colors: 4\n");
		printf("\n");
		gb.rows=10;
		gb.cols=14;
		gb.colors=4;
		return gb;
	}
	if(temp==3){
		printf("Level 3\n");
		printf("- Rows: 14\n- Cols: 16\n- Colors: 6\n");
		printf("\n");
		gb.rows=14;
		gb.cols=16;
		gb.colors=5;
		return gb;
	}
	if(temp==4){
		printf("Level 4\n");
		printf("- Rows: 28\n- Cols: 26\n- Colors: 8\n");
		printf("\n");
		gb.rows=28;
		gb.cols=26;
		gb.colors=8;
		return gb;
		}
	else{
		printf("Bad input\n");
		printf("Defaulting to Level 1\n");
		printf("- Rows: 8\n- Cols: 8\n- Colors: 3\n");
		printf("\n");
		gb.rows=8;
		gb.cols=8;
		gb.colors=3;
		return gb;
		}
}

gamePiece** createBoard(gameBoard gb){
	gamePiece **board=(gamePiece**)malloc(gb.rows*sizeof(gamePiece*));
	for(int i=0;i<gb.rows;i++){
		board[i]=(gamePiece*)malloc(gb.cols*sizeof(gamePiece));
	}
	char tileArray[8]={'o','x','*','#','=','l','-','+'};
	for(int i=0;i<gb.rows;i++){
		for(int j=0;j<gb.cols;j++){
			gamePiece cell;
			int color=rand()%gb.colors;
			char ch=tileArray[color];
			cell.item=ch;//the cell has a "color"
			cell.isVisited=false;//this cell hasn't been visited
			cell.completeCol=false;//no columns have been completed
			board[i][j]=cell;
		}
	}
	return board;
}

void displayBoard(int rows,int cols,gamePiece** board,double score){
	printf("Total score: %d\n",(int)score);
	for(int i=0;i<rows;i++){
		printf("%2d |", rows-i);
		for(int j=0;j<cols;j++){
			printf("%c ",board[i][j].item);
		}
		printf("\n");
	}
	printf("    ");
	for(int i=0;i<cols;i++){
		printf("--");
	}
	printf("\n");
	printf("    ");
	for(char c='A';c<'A'+cols;c++){
		printf("%c ",c);
	}
	printf("\n");
}

boardIndex getMove(int rows,int cols,gamePiece** board){
	boardIndex bi;
	int temp;
	char term;
	printf("> ");
	int check=scanf("%c%d",&term,&temp);
	while(getchar()!='\n');
	if(check==2 && term>='A' && term<'A'+cols && temp>0 && temp<=rows){
		  bi.row=rows-temp;
		  bi.col=term-'A';
		  return bi;
	}
	while(check!=2 || term<'A' || term>='A'+cols || temp<0 || temp>rows){
		printf("Invalid move.\n> ");
		check=scanf("%c%d",&term,&temp);
		while(getchar()!='\n');
	}
	bi.row=rows-temp;
	bi.col=term-'A';
	return bi;
	//still need to add more user input validation for strings>2
}

bool legalMove(gamePiece** board,boardIndex bi,gameBoard gb){
	if(board[bi.row][bi.col].item==' '){
		return false;
	}
	if(bi.row+1<gb.rows){ //check item below
		if(board[bi.row+1][bi.col].item==board[bi.row][bi.col].item){
		return true;
	}
}
	if(bi.row-1>=0){ //check item above
		if(board[bi.row-1][bi.col].item==board[bi.row][bi.col].item){
			return true;
		}
	}
	if(bi.col+1<gb.cols){ //check item to the right
		if(board[bi.row][bi.col+1].item==board[bi.row][bi.col].item){
			return true;
		}
	}
	if(bi.col-1>=0){ //check item to the left
		if(board[bi.row][bi.col-1].item==board[bi.row][bi.col].item){
			return true;
		}
	}
	return false;
}

double removePieces(gamePiece** board,int row, int col,char piece,gameBoard gb,double points,int counter){
	if(board[row][col].item==piece){
		board[row][col].item=' ';
		board[row][col].isVisited=true;
		points+=pow(2,counter);
	}
	if(row+1<gb.rows){
		if(board[row+1][col].item==piece){
			points=removePieces(board,row+1,col,piece,gb,points,counter+1);
		}
	}
	if(row-1>=0){
		if(board[row-1][col].item==piece){
			points=removePieces(board,row-1,col,piece,gb,points,counter+1);
		}
	}
	if(col+1<gb.cols){
		if(board[row][col+1].item==piece){
			points=removePieces(board,row,col+1,piece,gb,points,counter+1);
		}
	}
	if(col-1>=0){
		if(board[row][col-1].item==piece){
			points=removePieces(board,row,col-1,piece,gb,points,counter+1);
		}
	}
	counter=0;
	return points;
}

void collapse(gamePiece** board,gameBoard gb){
	for(int i=0;i<gb.cols;i++){
		for(int j=0;j<gb.rows;j++){
			if(board[j][i].item==' '&&board[j][i].isVisited==true){
				int x=j;
				int y=j;
				while(x-1>=0){
					board[x][i].item=board[x-1][i].item;
					x--;
				}
				board[y-j][i].item=' ';
				system("clear");
				displayBoard(gb.rows,gb.cols,board,score);
				usleep(45000);
			}
		}
	}
}

void compress(gamePiece** board,gameBoard gb){
	for(int y=gb.cols-1;y>=0;y--){
		int temp;
		for(int i=gb.cols-2;i>=0;i--){
			if(board[gb.rows-1][i].item==' '&&board[gb.rows-1][i].completeCol==false){
				for(int k=0;k<gb.rows;k++){
					temp=k;
					board[gb.rows-1-k][i].item=board[gb.rows-1-k][i+1].item;
					board[gb.rows-1-k][i+1].item=' ';
				}
				system("clear");
				displayBoard(gb.rows,gb.cols,board,score);
				usleep(45000);
			}
		}
	}
}

void setVisited(gamePiece** board,gameBoard gb){
	for(int i=0;i<gb.rows;i++){
		for(int j=0;j<gb.cols;j++){
			board[i][j].isVisited=false;
		}
	}
}

void setCompletedCols(gamePiece** board,gameBoard gb){
	for(int i=gb.cols-1;i>=0;i--){
		if(board[gb.rows-1][i].item==' '){
			for(int h=gb.rows-1;h>=0;h--){
				board[h][i].completeCol=true;
			}
		}
	}
}

bool anyMoveRemaining(gamePiece** board,gameBoard gb){
	boardIndex bi;
	for(int i=0;i<gb.rows;i++){
		for(int j=0;j<gb.cols;j++){
			bi.row=i;
			bi.col=j;
			if(legalMove(board,bi,gb)==true){
				return true;
			}
		}
	}
	return false;
}

bool anotherTry(gamePiece** board,gameBoard gb){
	bool didPlayerWin=playerWins(board,gb);
	if(didPlayerWin==false){
		system("clear");
		displayBoard(gb.rows,gb.cols,board,0);
		printf("No more valid moves remain. You lose!\n");
		printf("Your final score is: 0\n");
	}
	else{
		printf("Congratulations! You win!\n");
		printf("Your final score is: %d\n",(int)score);
	}
	printf("Would you like to play again? y or n\n");
	printf("> ");
	char pa;
	scanf("%c",&pa);
	if(pa=='y'){
		score=0;
		counter=0;
		return true;
	}
	if(pa=='n'){
		return false;
	}
		return false;
}

bool playerWins(gamePiece** board,gameBoard gb){
	for(int i=0;i<gb.rows;i++){
		for(int j=0;j<gb.cols;j++){
			if(board[i][j].item!=' '){
				return false;
			}
		}
	}
	return true;
}
