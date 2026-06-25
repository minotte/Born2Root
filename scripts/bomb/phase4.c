#include <stdio.h>

int func4(int x)

{
  int iVar1;
  int res;
  
  if (x < 2) {
    res = 1;
  }
  else {
    iVar1 = func4(x + -1);
    res = func4(x + -2);
    res = res + iVar1;
  }
  return res;
}

int phase_4(int x)

{
  int iVar1;

  iVar1 = func4(x);
  if (iVar1 != 0x37) { // 55
    return 1;
  }
  return 0;
}

int main() {
  int x = 1;
  while (phase_4(x))
    printf("false x = %d\n", x++);
  printf("true x = %d\n", x);
}