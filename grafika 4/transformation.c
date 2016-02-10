#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void translateList(int distanceX, int distanceY, int list[], int length){
	if(length%2==0){
		for (int i=0; i<length; i++){
			if(i%2==0){
				list[i] = list[i] + distanceX;
			}else{
				list[i] = list[i] + distanceY;
			}
		}
	}else{
		printf("Odd list");
	}
}



void rotateList(int degree, int centerX, int centerY, int list[], int length){
	if(length%2==0){
		int val = PI/180.0;
		for (int i=0; i<length; i++){
			if(i%2==0){
				list[i] = cos(degree*val)*(list[i]-centerX) - sin(degree*val)*(list[i+1]-centerY) + centerX;
			}else{
				list[i] = sin(degree*val)*(list[i-1]-centerX) + cos(degree*val)*(list[i]-centerY) + centerY;
			}
		}
	}else{
		printf("Odd list");
	}
}

void scaleList(int scale, int centerX, int centerY, int list[], int length){
	if(length%2==0){
		for (int i=0; i<length; i++){
			if(i%2==0){
				list[i] = scale*(list[i]-centerX) + centerX;
			}else{
				list[i] = scale*(list[i]-centerY) + centerY;
			}
		}
	}else{
		printf("Odd list");
	}
}

int main(){
	int positionList[] = {1,2,3,4,5,6};
	rotateList(180, 0, 0, positionList, 6);//contoh pemakaian saja
	return 0;
}