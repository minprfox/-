/*
	debug:
	fix where E can appear(it only appears if X>20 or Y>20) ;
*/
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
	char mapp[40][40];
	int  i, j, x, y, z, check, t, next[4][2] = { { 0 , 1}, { 1, 0}, { 0, -1}, { -1, 0}}, head, tail,h;
	int fomap[40][40] ,dir, move, gi, gj, fogj = 0, ex, ey;	
	for( i=0; i<40; i+=39)
		for( j=0; j<40; j++)
			mapp[i][j] = '#';
	for( i=1; i<39; i++)
		for( j=0; j<40; j+=39)
			mapp[i][j] = '#';
	do{
		t = 1;
		for( i=1; i<39; i++)
			for( j=1; j<39; j++)
				mapp[i][j] = '.';
		for( i=0; i<39; i++){
			for( j=0; j<39; j++){
				srand( time(0) + t);
       		    z = rand() % 7;
       		    if( z >= 4)
       	    		mapp[i][j] = '#';
       	   		t += 2;
			}
		}
		x = 38; 
		y = 38;
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
		ex = x; 
		ey = y;
		check = 0;
		head = 1;
		tail = 1;
		que[tail].qx = 1;
		que[tail].qy = 1;
		tail++;
		for(int i =0 ;i<40; i++){
			for(int j=0;j<40; j++)
				fomap[i][j] = 0;
		}
		fomap[x][y] = 1;
		do{
			for( i=0; i<=3; i++){
				x = que[head].qx+ next[i][0];
				y = que[head].qy+ next[i][1];
				if( x < 1 || y < 1 || x > 38 || y > 38){
					x = ex;
					y = ey;
					continue;
				}
				ex = x;
				ey = y;
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
	}while( x <= 20 && y <= 20);
	if( check != 1){
		mapp[ex][ey] ='#';
		mapp[x][y] = 'E';
	}
	for( i=0; i<40; i++){
			for( j=0; j<40; j++){
				if( j == 0)
					cout<<mapp[i][0];
				else if( i < 1 || i > 38 || j > 38 )
					cout<<" "<<mapp[i][j];
				else
					cout<<"  ";
			}
			cout<<endl;
		}
	cout<<"  0 = you  ,  # = wall ,  Your task is to find E  ";
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
		if( x < 1 || y < 1 || x > 38 || y > 38 || mapp[x][y] == '#'){
			x = ex;
			y = ey;
			continue;	
		}
		fogj += next[dir][1] * 2;
	}	
	gotoxy( 0, 42);
	cout<<"you win";
	return 0;
}
