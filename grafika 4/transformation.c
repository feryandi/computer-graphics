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



int* rotateList(int degree, int centerX, int centerY, int *list, int length){
    int *temp = (int*)malloc(length * sizeof(int));
	if(length%2==0){
		double val = PI/180.0;
		for (int i=0; i<length; i++){
			if(i%2==0){
				temp[i] = (int) ( cos(degree * val) * (list[i] - centerX) - ( sin(degree*val) * ((list)[i+1] - centerY) ) + centerX );
				//printf("hiks: %d, %d, %d\n", (int) (list)[i+1],  centerY, (int) (list)[i+1] - centerY );
			}else{
				temp[i] = (int) ( sin(degree * val) * (list[i-1] - centerX) + cos(degree * val) * (list[i] - centerY) + centerY ) ;
			}
		}
	}else{
		printf("Odd list");
	}
	return temp;
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
