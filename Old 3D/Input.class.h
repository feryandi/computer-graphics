#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>
#include <time.h>
#include <string.h>

class Input{
  
public:
  /* restore new terminal i/o settings */
  static void resetTermios();

  /* initialize new terminal i/o settings */
  static void initTermios();

  /* detect keyboard press */
  static int kbhit();

  /* read 1 character */
  static char getch();

};
