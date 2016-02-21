#include <iostream>
#include "Polygon.class.h"
#include "FrameBuffer.class.h"
using namespace std;

// 40
int jakartaUtara[] = {
	16, 3, 18, 2,
	18, 2, 28, 7,
	28, 7, 38, 8,
	38, 8, 46, 11,
	46, 11, 51, 10,
	51, 10, 56, 15,
	56, 15, 70, 15,
	70, 15, 82, 6,
	82, 6, 94, 8,
	94, 8, 98, 8,
	98, 8, 100, 6,
	100, 6, 110, 4,
	110, 4, 114, 4,
	114, 4, 116, 2,
	116, 2, 124, 0,
	124, 0, 124, 30,
	124, 30, 116, 30,
	116, 30, 114, 32,
	114, 32, 112, 31,
	112, 31, 108, 34,
	108, 34, 104, 34,
	104, 34, 103, 30,
	103, 30, 99, 30,
	99, 30, 101, 33,
	101, 33, 101, 39,
	101, 39, 94, 40,
	94, 40, 82, 35,
	82, 35, 64, 29,
	64, 29, 58, 24,
	58, 24, 55, 22,
	55, 22, 54, 20,
	54, 20, 52, 20,
	52, 20, 50, 22,
	50, 22, 50, 24,
	50, 24, 38, 24,
	38, 24, 38, 22,
	38, 22, 28, 18,
	28, 18, 20, 12,
	20, 12, 16, 6,
	16,	6, 16, 3
};

// 40
int jakartaBarat[] = {
	16, 3, 12, 4,
	12, 4, 4, 4,
	4, 4, 2, 5,
	2, 5, 0, 5,
	0, 5, 0, 8,
	0, 8, 2, 11,
	2, 11, 0, 16,
	0, 16, 1, 20,
	1, 20, 2, 38,
	2, 38, 14, 43,
	14, 43, 14, 45,
	14, 45, 16, 45,
	16, 45, 16, 52,
	16, 52, 14, 54,
	14, 54, 13, 56,
	13, 56, 14, 58,
	14, 58, 21, 59,
	21, 59, 38, 59,
	38, 59, 38, 54,
	38, 54, 40, 54,
	40, 54, 40, 52,
	40, 52, 46, 52,
	46, 52, 50, 44,
	50, 44, 52, 44,
	52, 44, 52, 39,
	52, 39, 48, 32,
	48, 32, 51, 30,
	51, 30, 60, 30,
	60, 30, 58, 24,
	58, 24, 55, 22,
	55, 22, 54, 20,
	54, 20, 52, 20,
	52, 20, 50, 22,
	50, 22, 50, 24,
	50, 24, 38, 24,
	38, 24, 38, 22,
	38, 22, 28, 18,
	28, 18, 20, 12,
	20, 12, 16, 6,
	16, 6, 16, 3
};

// 41
int jakartaSelatan[] = {
	21, 59, 38, 59,
	38, 59, 38, 54,
	38, 54, 40, 54,
	40, 54, 40, 52,
	40, 52, 46, 52,
	46, 52, 46, 61,
	46, 61, 57, 54,
	57, 54, 58, 50,
	58, 50, 70, 50,
	70, 50, 74, 58,
	74, 58, 74, 70,
	74, 70, 72, 76,
	72, 76, 67, 82,
	67, 82, 68, 88,
	68, 88, 72, 94,
	72, 94, 68, 98,
	68, 98, 68, 94,
	68, 94, 63, 98,
	63, 98, 64, 104,
	64, 104, 62, 112,
	62, 112, 56, 113,
	56, 113, 54, 116,
	54, 116, 46, 117,
	46, 117, 44, 116,
	44, 116, 44, 110,
	44, 110, 46, 108,
	46, 108, 48, 104,
	48, 104, 48, 101,
	48, 101, 50, 98,
	50, 98, 50, 96,
	50, 96, 38, 96,
	38, 96, 37, 94,
	37, 94, 37, 90,
	37, 90, 25, 78,
	25, 78, 26, 75,
	26, 75, 29, 74,
	29, 74, 30, 70,
	30, 70, 26, 70,
	26, 70, 25, 66,
	25, 66, 22, 65,
	22, 65, 21, 59
};

// 49
int jakartaTimur[] = {
	124, 30, 116, 30,
	116, 30, 114, 32,
	114, 32, 112, 31,
	112, 31, 108, 34,
	108, 34, 104, 34,
	104, 34, 103, 30,
	103, 30, 99, 30,
	99, 30, 101, 33,
	101, 33, 101, 39,
	101, 39, 94, 40,
	94, 40, 82, 35,
	82, 35, 82, 35,
	82, 35, 78, 44,
	78, 44, 76, 44,
	76, 44, 70, 46,
	70, 46, 70, 50,
	70, 50, 74, 58,
	74, 58, 74, 70,
	74, 70, 72, 76,
	72, 76, 67, 82,
	67, 82, 68, 88,
	68, 88, 72, 94,
	72, 94, 68, 98,
	68, 98, 68, 94,
	68, 94, 63, 98,
	63, 98, 64, 104,
	64, 104, 68, 102,
	68, 102, 68, 104,
	68, 104, 74, 112,
	74, 112, 77, 111,
	77, 111, 79, 113,
	79, 113, 77, 116,
	77, 116, 79, 117,
	79, 117, 81, 117,
	81, 117, 85, 120,
	85, 120, 91, 119,
	91, 119, 90, 121,
	90, 121, 93, 121,
	93, 121, 98, 108,
	98, 108, 98, 90,
	98, 90, 95, 88,
	95, 88, 94, 79,
	94, 79, 99, 79,
	99, 79, 99, 70,
	99, 70, 108, 70,
	108, 70, 110, 58,
	110, 58, 120, 52,
	120, 52, 124, 46,
	124, 46, 124, 30
};

// 17
int jakartaPusat[] = {
	46, 52, 50, 44,
	50, 44, 52, 44,
	52, 44, 52, 39,
	52, 39, 48, 32,
	48, 32, 51, 30,
	51, 30, 60, 30,
	60, 30, 58, 24,
	58, 24, 64, 29,
	64, 29, 82, 35,
	82, 35, 78, 44,
	78, 44, 76, 44,
	76, 44, 70, 46,
	70, 46, 70, 50,
	70, 50, 58, 50,
	58, 50, 57, 54,
	57, 54, 46, 61,
	46, 61, 46, 52
};

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

int main() {
	FrameBuffer FB;

	Polygon jakpus(0, 0,jakartaPusat, 68);
	jakpus.setPosition(0,0);
	jakpus.setMultiplication(5);

	Polygon jaktim(0, 0,jakartaTimur, 196);
	jaktim.setPosition(0,0);
	jaktim.setMultiplication(5);

	Polygon jaksel(0, 0,jakartaSelatan, 164);
	jaksel.setPosition(0,0);
	jaksel.setMultiplication(5);

	Polygon jakbar(0, 0,jakartaBarat, 160);
	jakbar.setPosition(0,0);
	jakbar.setMultiplication(5);

	Polygon jakut(0, 0,jakartaUtara, 160);
	jakut.setPosition(0,0);
	jakut.setMultiplication(5);

	jakbar.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jaksel.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jakut.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jakpus.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);
	jaktim.setPosition(FB.getVInfoX()/2,FB.getVInfoY()/2);

	jakbar.setCenter(62, 60);
	jaksel.setCenter(62, 60);
	jakut.setCenter(62, 60);
	jakpus.setCenter(62, 60);
	jaktim.setCenter(62, 60);

	FB.canvas();

	jaksel.draw(&FB);
	jakut.draw(&FB);
	jakbar.draw(&FB);
	jakpus.draw(&FB);
	jaktim.draw(&FB);

	FB.render();

	int key = 0;
	while (key != 0x20) {
		key = getkey();

	    int translate = (10/jakpus.getMultiplication() > 0) ? (10/jakpus.getMultiplication()) : 1;

		int tX = jakpus.getX();
		int tY = jakpus.getY();
		int tCX = jakpus.getCX();
		int tCY = jakpus.getCY();
		int on_click = 0;

	    if (key == 0x57) {
	        tX = jakpus.getX();
	        tY = jakpus.getY() - translate;
	        tCX = jakpus.getCX();
	        tCY = jakpus.getCY() + translate;
	        on_click = 1;
	    } else if (key == 0x41) {
	        tX = jakpus.getX() - translate;
	        tY = jakpus.getY();
	        tCX = jakpus.getCX() + translate;
	        tCY = jakpus.getCY();
	        on_click = 1;
	    } else if (key == 0x53) {
			tX = jakpus.getX();
	        tY = jakpus.getY() + translate;
	        tCX = jakpus.getCX();
	        tCY = jakpus.getCY() - translate;
	        on_click = 1;
	    } else if (key == 0x44) {
	        tX = jakpus.getX() + translate;
	        tY = jakpus.getY();
	        tCX = jakpus.getCX() - translate;
	        tCY = jakpus.getCY();
	        on_click = 1;
	    } else if (key == 0x49){
	    	if(jakpus.getMultiplication() > 1 && jakpus.getMultiplication()-1 >= 5){
		        jakpus.setMultiplication(jakpus.getMultiplication() - 1);
		        jaksel.setMultiplication(jaksel.getMultiplication() - 1);
		        jakut.setMultiplication(jakut.getMultiplication() - 1);
		        jaktim.setMultiplication(jaktim.getMultiplication() - 1);
		        jakbar.setMultiplication(jakbar.getMultiplication() - 1);
	        	on_click = 1;
		    }
	    } else if (key == 0x4F){
	        jakpus.setMultiplication(jakpus.getMultiplication() + 1);
	        jaksel.setMultiplication(jaksel.getMultiplication() + 1);
	        jakut.setMultiplication(jakut.getMultiplication() + 1);
	        jaktim.setMultiplication(jaktim.getMultiplication() + 1);
	        jakbar.setMultiplication(jakbar.getMultiplication() + 1);
	        on_click = 1;
	    }

        jakpus.setPosition(tX,tY);
        jaksel.setPosition(tX,tY);
        jakut.setPosition(tX,tY);
        jaktim.setPosition(tX,tY);
        jakbar.setPosition(tX,tY);

        jakpus.setCenter(tCX,tCY);
        jaksel.setCenter(tCX,tCY);
        jakut.setCenter(tCX,tCY);
        jaktim.setCenter(tCX,tCY);
        jakbar.setCenter(tCX,tCY);

        if (on_click) {
			FB.canvas();

		    jakpus.draw(&FB);
		    jaksel.draw(&FB);
		    jakut.draw(&FB);
		    jaktim.draw(&FB);
		    jakbar.draw(&FB);

		    FB.render();
		}
	}
		
	return 0;
}