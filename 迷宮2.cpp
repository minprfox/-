#include <iostream>
#include <windows.h>
#include <cmath>
#include<conio.h>
#include<cstdlib>
#include<ctime>
using namespace std;
struct note{
	int qx;
	int qy; 
};
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
int main(){
	struct note que[1860];
	char mapp[23][23];
	int  i, j, x = 21, y = 21, z, check = 0, t, next[4][2] = { { 0 , 1}, { 1, 0}, { 0, -1}, { -1, 0}}, head, tail,h;
	int fomap[23][23]={0} ,dir, move, gi, gj, fogj = 0;		
	for( i=0; i<23; i+=22)
		for( j=0; j<23; j++)
			mapp[i][j] = '#';
	for( i=1; i<22; i++)
		for( j=0; j<23; j+=22)
			mapp[i][j] = '#';
	for( i=1; i<22; i++)
		for( j=1; j<22; j++)
			mapp[i][j] = '.';
	for( i=0; i<23; i++){
		for( j=0; j<23; j++){
			srand( time(0) + t);
       	    z = rand() % 7;
       	    if( z >= 4)
       	    	mapp[i][j] = '#';
       	    t += 2;
		}
	}
	mapp[1][1] = '0';
	srand( time(0) + t);
    z = rand() % 3;
    switch(z){
    	case 0:
    		x = 1;
    		break;
    	case 1:
    		y = 1;
    		break;
	}
	mapp[x][y] = 'E';
	int ex = x, ey = y;
	check = 0;
	head = 1;
	tail = 1;
	que[tail].qx = 1;
	que[tail].qy = 1;
	tail++;
	fomap[x][y] = 1;

	do{
		for( i=0; i<=3; i++){
			x = que[head].qx+ next[i][0];
			y = que[head].qy+ next[i][1];
			if( x < 1 || y < 1 || x > 21 || y > 21)
				continue;
			if( mapp [x][y] == 'E')
				check=1;
			if( mapp[x][y] == '#'){
				srand( time(0) + t);
       	    	z = rand() % 20;
       	    	t ++;
       	    	if( z <= 1)
       	    		mapp[x][y] = '.';
			}
			if( mapp[x][y] == '.' && fomap[x][y] == 0){
				fomap[x][y] = 1;
				que[tail].qx = x;
				que[tail].qy = y;
				tail++;
			}
		}
		head++;	
	}while( head < tail);
	if( check != 1){
		mapp[ex][ey] ='#';
		mapp[x][y] = 'E';
	}	
	for( i=0; i<23; i++){
			for( j=0; j<23; j++){
				if( j == 0)
					cout<<mapp[i][0];
				else if( i < 1 || i > 21 || j > 21 )
					cout<<" "<<mapp[i][j];
				else
					cout<<"  ";
			}
			cout<<endl;
		}
	x=1, y=1, ex=1, ey=1;
	while( mapp[x][y] != 'E'){
		for( i=x-1; i<x+2; i++){
			gj = fogj;
			for( j=y-1; j<y+2; j++){
				gi = i ;
				gotoxy( gj, gi);
				cout<<"  ";
				gj += 2;
			}
		}
		mapp[ex][ey] = '.';
		mapp[x][y] = '0';
		ex = x;
		ey = y;
		for( i=x-1; i<x+2; i++){
			gj = fogj;
			for( j=y-1; j<y+2; j++){
				gi = i ;
				gotoxy( gj, gi);
				cout<<mapp[i][j];
				gj += 2;
			}
		}
		move = getch();
       	switch(move){
            case 224:
                move = getch();
                switch(move){
                    case 72:    
						dir = 3;
                        break;
                    case 80:     
						dir = 1;
                        break;
                    case 77:    
						dir = 0;
                        break;
                    case 75:    
						dir = 2;
                        break;
                }
    	}
    	x += next[dir][0];
		y += next[dir][1];
		
		if( x < 1 || y < 1 || x > 21 || y > 21 || mapp[x][y] == '#'){
			x = ex;
			y = ey;
			continue;	
		}
		fogj += next[dir][1] * 2;
	
		
	}	
	gotoxy( 0, 24);
	cout<<"you win";
	return 0;
}
