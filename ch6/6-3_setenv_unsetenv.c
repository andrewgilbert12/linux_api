#include <stdlib.h>
#include <string.h>
#include <errno.h>

int unsetenv(const char *name) {
  extern char **environ;
  char **cp, **rp;

  if (name == NULL || name[0] == '\n' || strchr(name, '=') != NULL) {
    errno = EINVAL;
    return -1;
  }

  size_t len = strlen(name);

  for (cp = environ; *cp != NULL; ) {
    if (strncmp(*cp, name, len) == 0 && *(cp)[len] == '=') {
      for (rp = cp; *rp != NULL; rp++) {
        *rp = *(rp + 1); // shift each pointer past the one we delete to the left
      }
    } else {
      cp++;
    }
  }

  return 0;
}

int setenv(const char *name, const char *value, int overwrite) {

  if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL ||
      value == NULL) {
    errno = EINVAL;
    return -1;
  }

  if (getenv(name) != NULL && overwrite == 0) {
    return 0;
  }

  unsetenv(name);

  char *new_val = malloc(strlen(name) + strlen(value) + 2); // 2 for '=' and '\0'

  if (new_val == NULL) {
    return -1; // malloc error
  }

  strcpy(new_val, name);
  strcat(new_val, "=");
  strcat(new_val, value);

  return (putenv(new_val) == 0) ? 0 : -1; // there shouldn't be any way for putenv to fail, but check anyway
}
