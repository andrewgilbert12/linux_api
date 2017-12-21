#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s name\n", argv[0]);
    exit(1);
  }

  int use_uid = 0;

  if ((strcmp(argv[1],"-u") == 0)) {
    use_uid = 1;
  }

  if ((strncmp(argv[1],"-",1) == 0)) {
    ++argv;
  }

  struct passwd *pw;

  if (use_uid) {
    printf("searching by uid...\n");
    pw = getpwuid(atoi(argv[1]));
  } else {
    pw = getpwnam(argv[1]);
  }

  if (pw == NULL) {
    printf("user %s not found\n", argv[1]);
    exit(1);
  }

  printf("pw_name: %s\n", pw->pw_name);
  printf("pw_passwd: %s\n", pw->pw_passwd);
  printf("pw_uid: %u\n", pw->pw_uid);
  printf("pw_gid: %u\n", pw->pw_gid);
  printf("pw_gecos: %s\n", pw->pw_gecos);
  printf("pw_dir: %s\n", pw->pw_dir);
  printf("pw_shell: %s\n", pw->pw_shell);

  return 0;
}
