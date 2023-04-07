#include "terminal.h"

#include <termios.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>

static termios orig_termios;

void die(const char *s) {
  perror(s);
  exit(1);
}

void disableRawMode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) < 0) die("tcsetattr");
}

void enableRawMode() {
  if (tcgetattr(STDIN_FILENO, &orig_termios) < 0) die("tcgetattr");

  atexit(disableRawMode);

  termios raw = orig_termios;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0) die("tcsetattr");
}
