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
  void resetTermios();

  /* initialize new terminal i/o settings */
  void initTermios();

  /* detect keyboard press */
  int kbhit();

  /* read 1 character */
  char getch();

};
