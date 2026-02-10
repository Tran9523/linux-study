#include <stdio.h>

int main(void)
{
    char s[1000001];    // char라 걍 할당해주는게 편함
    int count = 0;
    int in_word = 0;

    if (!fgets(s, sizeof(s), stdin)) return 0;  // 첫 공백을 포함해야할 수 있으니 fgets

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t') {
            in_word = 0;
        } else {
            if (in_word == 0) {
                count++;
                in_word = 1;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}
