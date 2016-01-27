//file: grafika1.c

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

#define NUM_THREADS 2
#define FONT_SIZE 10
#define FONT_WIDTH 5
#define FONT_HEIGHT 5

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

/* Character Font */
//FONT 5X5

typedef struct Picture {
    int width;
    int height;
    int size;
    int pixel[500];
} Picture;

int fbfd = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
long int screensize = 0;
char *fbp = 0;
char *buffer = 0;
long int location = 0;

void blockBuilder(int x, int y, int block_size, int blue, int green, int red) {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = y; j < y + block_size ; j++) {
        for (i = x; i < x + block_size; i++) {

            if ( i >= 0 && j >= 0 && i < vinfo.xres - 50 && j < vinfo.yres - 50 ) {
                location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (j+vinfo.yoffset) * finfo.line_length;

                if (vinfo.bits_per_pixel == 32) {
                    *(buffer + location) = 255 - blue;        // Blue
                    *(buffer + location + 1) = 255 - green;    // Green
                    *(buffer + location + 2) = 255 - red;    // Red
                    *(buffer + location + 3) = 0;      // Alpha
            //location += 6;
                } else  { //assume 16bpp
                    int b = 255 - blue;
                    int g = 255 - green;     // A little green
                    int r = 255 - red;    // A lot of red
                    unsigned short int t = r<<11 | g << 5 | b;
                    *((unsigned short int*)(buffer + location)) = t;
                }
            }

        }
    }
}

void pictureBuilder(Picture P, int startX, int startY) {
    int i, j;
    for (j = 0; j < P.height; j++) {
        for (i = 0; i < P.width; i++) {
            int digit = P.pixel[(P.width * j) + i];
            if ( digit >= 1 ) {
                //printf("h: %d, w: %d", i, j);
                blockBuilder(startX + i * P.size, startY + j * P.size, P.size, (50 * digit), (20 * digit), (20 * digit * 3)); //Ngilangin warna
            }
        }
    }
}

void pictureDestruct(Picture P, int startX, int startY) {
    int i, j;
    for (j = 0; j < P.height; j++) {
        for (i = 0; i < P.width; i++) {
            if ( P.pixel[(P.width * j) + i] == 1 ) {
                //printf("h: %d, w: %d", i, j);
                blockBuilder(startX + i * P.size, startY + j * P.size, P.size, 255, 255, 255); //Ngilangin warna
            }
        }
    }
}

/*void charBuilder(char c, int startX, int startY) {
    int i, j;
    for (j = 0; j < FONT_HEIGHT; j++) {
        for (i = 0; i < FONT_WIDTH; i++) {
            if ( font[c - 65][j * FONT_WIDTH + i] == 1 ) {
                blockBuilder(startX + i * FONT_SIZE, startY + j * FONT_SIZE, 255, 0, 0); //Ngilangin warna
            }
        }
    }
}

void stringBuilder(char *s, int startX, int startY) {
    int i;
    for (i = 0; i < strlen(s); i++) {
        charBuilder(s[i], startX + i * FONT_SIZE * (FONT_WIDTH + 1), startY);
    }

}*/

/*char* receiveInput(char *s){
    scanf("%99s",s);
    return s;
}*/

void create_buffer() {
    buffer = malloc(screensize);
    memcpy(buffer, fbp, screensize);
}

void render_buffer() {
    memcpy(fbp, buffer, screensize);
}

void solidBackground() {
    int i, j;
    // Figure out where in memory to put the pixel
    for (j = 0; j < vinfo.yres - 50; j++) {
        for (i = 0; i < vinfo.xres - 50; i++) {

            location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (j+vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(buffer + location) = 0;        // Blue
                *(buffer + location + 1) = 0;    // Green
                *(buffer + location + 2) = 0;    // Red
                *(buffer + location + 3) = 0;      // Alpha
        //location += 4;
            } else  { //assume 16bpp
                int b = 0;
                int g = 0;     // A little green
                int r = 0;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(buffer + location)) = t;
            }

        }
    }
}

int iabs(int n){
  int const mask = n >> (sizeof(int) * 8 - 1);
  return ((n + mask) ^ mask);
}

int Fx[] = { 1,  0, -1,  0};
int Fy[] = { 0,  1,  0, -1};

int Gx[] = { 1, -1, -1,  1};
int Gy[] = { 1,  1, -1, -1};

int F(int X, int Y, int Z) {
  if (X & Z) {
    return 0;
  } else if (Y & (! Z)) {
    return 1;
  } else if ((! X) & Z) {
    return 2;
  } else if ((! Y) & (! Z)) {
    return 3;
  }
}

int G(int X, int Y) {
  if (X & Y) {
    return 0;
  } else if ((! X) & Y) {
    return 1;
  } else if ((! X) & (! Y)) {
    return 2;
  } else if (X & (! Y)) {
    return 3;
  }
}

void bresenham(int x1, int y1, int x2, int y2 , int red, int green, int blue) {
  int dx = x2 - x1;
  int dy = y2 - y1;

  int X = dx > 0;
  int Y = dy > 0;
  int Z = (iabs(dx) - iabs(dy)) > 0;

  int f = F(X, Y, Z);
  int g = G(X, Y);

  int m1x = Fx[f];
  int m1y = Fy[f];
  int m2x = Gx[g];
  int m2y = Gy[g];

  int da, db;

  if (Z) {
    da = iabs(dx); db = iabs(dy);
  } else {
    da = iabs(dy); db = iabs(dx);
  }

  int D = 2*db - da;
  
  blockBuilder(x1, y1, 5, red, green, blue);

  int x = x1;
  int y = y1;
  
  while ((Z && (x != x2)) || (!Z && (y != y2))) {
    
    D = D + 2*db;

    if (D >= 0) {
      x += m2x;
      y += m2y;
      D = D - 2*da;
    } else {
      x += m1x;
      y += m1y;
    }

    blockBuilder(x, y, 5, red, green, blue);
  }
}

int main() {

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    //printf("The framebuffer device was mapped to memory successfully.\n");

    create_buffer();

    /* Initialize Object to Draw */
    Picture plane = { .width=20, .height=20, .size=6, .pixel={  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1,
                                                                0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
                                                                0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
                                                                1, 3, 2, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 2, 3, 1,
                                                                0, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 0,
                                                                0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 0, 0,
                                                                0, 0, 2, 2, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 2, 2, 0, 0,
                                                                0, 7, 2, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 7, 0,
                                                                0, 0, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 0, 0,
                                                                1, 0, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, 1,
                                                                0, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 0,
                                                                0, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 0,
                                                                1, 4, 4, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 4, 1,
                                                                0, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 0,
                                                                0, 0, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 0, 0, 0,
                                                                0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
                                                                0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0,
                                                                0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

    Picture ship = { .width=20, .height=20, .size=6, .pixel={   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
                                                                0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
                                                                0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
                                                                9, 9, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 9, 9,
                                                                9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
                                                                0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0,
                                                                0, 0, 6, 6, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 6, 0, 0,
                                                                0, 0, 0, 6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 0, 0, 0,
                                                                0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0,
                                                                0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0 } };


    int reductor = 0;
    int counter = 0;

    solidBackground();

    int plane_x = 50;
    int plane_y = 50;
    int plane_turn = 1;
    
    int ship_x = (vinfo.xres - 50 - (ship.height * ship.size))/2;
    int ship_y = vinfo.yres - 50 - (ship.height * ship.size);

    int ship_center_x = (vinfo.xres - 50)/2;
    int ship_center_y = vinfo.yres - 50;

    int laser_x = 0;
    int laser_y = 0;
    int add_x = 0;
    int add_y = 0;

    int weapon = 0;

    int key;
    while (1) {
        key = getkey();

        if (key == 0x41) {
            laser_y = 20;
            laser_x = ((ship_x-plane_x)*20/(ship_y-plane_y));
            weapon = 0;
        } else if (key == 0x53) {
            laser_y = 20;
            laser_x = ((ship_x-plane_x)*20/(ship_y-plane_y));
            weapon = 1;
        }

        if (weapon == 0) {
            bresenham(ship_center_x-add_x, ship_center_y-add_y, laser_x+ship_center_x-add_x, laser_y+ship_center_y-add_y, 0, 0, 0);
            add_y += laser_y/2;
            add_x += laser_x/2;
        } else if (weapon == 1) {
            bresenham(ship_center_x-add_x, ship_center_y-add_y, laser_x+ship_center_x, laser_y+ship_center_y, 0, 0, 0);
            add_y += laser_y;
            add_x += laser_x;
        }

        if ( (ship_center_y-add_y < 0 || ship_center_x-add_x < 0)
             || (ship_center_y-add_y >= vinfo.yres || ship_center_x-add_x >= vinfo.xres) ) {
            printf("masukin");
            laser_x = 0;
            laser_y = 0;
            add_y = 0;
            add_x = 0;
        }

        pictureBuilder(plane, plane_x, plane_y);
        if ( plane_x <= 0 ) {
            plane_turn = 1;
        } else if ( plane_x + (plane.width * plane.size) > vinfo.xres - 50 ) {   
            plane_turn = -1;
        }

        plane_x -= -5 * plane_turn;

        pictureBuilder(ship, ship_x, ship_y);

        render_buffer();
        solidBackground();
        ++counter;

    }

    munmap(fbp, screensize);

    close(fbfd);
    return 0;
}
