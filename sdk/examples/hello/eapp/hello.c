#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main() {
  char* buff =
      "The quick brown fox jumps over the lazy dog The quick brown fox jumps "
      "over the lazy dog The quick brown fox jumps over the lazy dog The quick "
      "brown fox jumps over the lazy dog The quick brown fox jumps over the "
      "lazy dog";

  size_t bytes_in_buff = strlen(buff) + 1;

  unsigned int i = 0;

  printf("--> buff at %p\n", buff);

  while (bytes_in_buff > 0 && i < 3) {
    size_t block_size = (bytes_in_buff < 128) ? bytes_in_buff : 128;
    size_t bytes_sent = write(1, buff, block_size);

    if (bytes_sent < 0) {
      break;
    }

    buff += bytes_sent;
    bytes_in_buff -= bytes_sent;
    i++;
    printf("\n %zu byte written, %zu remaining\n", bytes_sent, bytes_in_buff);
  }

  char* secret = "super secret enclave string";
  printf("--> enclave secret '%s' at %p\n\n", secret, secret);

  return 0;
}