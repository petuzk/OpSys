#include <stdio.h>

char* string = "Witajcie moi mili ...";

int main(int argc, char const *argv[]) {
  for (unsigned i = 0; ; i++) {
    printf("%c", string[i]);
  }

  return 0;
}
