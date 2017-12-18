#include <setjmp.h>
#include <stdio.h>

void f();

jmp_buf env;

int main()
{
  f();

  longjmp(env, 1); // will cause a segfault since we jump into a function that already returned

  return 0;
}

void f()
{
  puts("doing f");

  setjmp(env);
}
