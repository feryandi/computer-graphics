#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <time.h>
#include "polygon.class.h"
#include "transformation.h"
#include "frameBuffer.class.h"
#include <iostream>
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
	16,	6, 16, 3,
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
	16, 6, 16, 3,
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
	22, 65, 21, 59,
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
	124, 46, 124, 30,
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
	46, 61, 46, 52,
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

int main()
{
	frameBuffer f;
	f.solidBackground();
	polygon p1, p2, p3, p4, p5;
	
	p1.setMultiplication(5);
	p1.setPolyline(jakartaUtara, 40);
	p1.setPosition(0,0);
	p1.setFloodPosition(30, 20);
	p1.draw(&f);
	
	p2.setMultiplication(5);
	p2.setPolyline(jakartaBarat, 40);
	p2.setPosition(0,0);
	p2.setFloodPosition(30, 20);
	p2.draw(&f);

	p3.setMultiplication(5);
	p3.setPolyline(jakartaSelatan, 41);
	p3.setPosition(0,0);
	p3.setFloodPosition(30, 20);
	p3.draw(&f);

	p4.setMultiplication(5);
	p4.setPolyline(jakartaTimur, 49);
	p4.setPosition(0,0);
	p4.setFloodPosition(30, 20);
	p4.draw(&f);

	p5.setMultiplication(5);
	p5.setPolyline(jakartaPusat, 17);
	p5.setPosition(0,0);
	p5.setFloodPosition(30, 20);
	p5.draw(&f);

	f.render_buffer();
	int key = 0;
	while (key != 0x20) {
		key = getkey();

	    if (key == 0x57) {
	        f.solidBackground();
	        p1.setPosition(p1.getPositionX() + 0,p1.getPositionY() - 10);
	        p2.setPosition(p2.getPositionX() + 0,p2.getPositionY() - 10);
	        p3.setPosition(p3.getPositionX() + 0,p3.getPositionY() - 10);
	        p4.setPosition(p4.getPositionX() + 0,p4.getPositionY() - 10);
	        p5.setPosition(p5.getPositionX() + 0,p5.getPositionY() - 10);
	        p1.draw(&f);
	        p2.draw(&f);
	        p3.draw(&f);
	        p4.draw(&f);
	        p5.draw(&f);
	        f.render_buffer();
	    } else if (key == 0x41) {
	        f.solidBackground();
	        p1.setPosition(p1.getPositionX() - 10,p1.getPositionY() + 0);
	        p2.setPosition(p2.getPositionX() - 10,p2.getPositionY() + 0);
	        p3.setPosition(p3.getPositionX() - 10,p3.getPositionY() + 0);
	        p4.setPosition(p4.getPositionX() - 10,p4.getPositionY() + 0);
	        p5.setPosition(p5.getPositionX() - 10,p5.getPositionY() + 0);
	        p1.draw(&f);
	        p2.draw(&f);
	        p3.draw(&f);
	        p4.draw(&f);
	        p5.draw(&f);
	        f.render_buffer();
	    } else if (key == 0x53) {
	        f.solidBackground();
	        p1.setPosition(p1.getPositionX() + 0,p1.getPositionY() + 10);
	        p2.setPosition(p2.getPositionX() + 0,p2.getPositionY() + 10);
	        p3.setPosition(p3.getPositionX() + 0,p3.getPositionY() + 10);
	        p4.setPosition(p4.getPositionX() + 0,p4.getPositionY() + 10);
	        p5.setPosition(p5.getPositionX() + 0,p5.getPositionY() + 10);
	        p1.draw(&f);
	        p2.draw(&f);
	        p3.draw(&f);
	        p4.draw(&f);
	        p5.draw(&f);
	        f.render_buffer();
	    } else if (key == 0x44) {
	        f.solidBackground();
	        p1.setPosition(p1.getPositionX() + 10,p1.getPositionY() + 0);
	        p2.setPosition(p2.getPositionX() + 10,p2.getPositionY() + 0);
	        p3.setPosition(p3.getPositionX() + 10,p3.getPositionY() + 0);
	        p4.setPosition(p4.getPositionX() + 10,p4.getPositionY() + 0);
	        p5.setPosition(p5.getPositionX() + 10,p5.getPositionY() + 0);
	        p1.draw(&f);
	        p2.draw(&f);
	        p3.draw(&f);
	        p4.draw(&f);
	        p5.draw(&f);
	        f.render_buffer();
	    }
	}
	return 0;
}