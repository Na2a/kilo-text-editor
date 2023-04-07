// Copyright [2023] <Nazarbek Altybay>

#include <termios.h>
#include <unistd.h>

#include <cctype>
#include <cerrno>
#include <cstdio>
#include <cstdlib>

#include "terminal.h"

int main() {
  enableRawMode();

  for (;;) {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) < 0 && errno != EAGAIN) die("read");
    if (iscntrl(c)) {
      printf("%d\r\n", c);
    } else {
      printf("%d ('%c')\r\n", c, c);
    }
    if (c == 'q') break;
  }
  return 0;
}
