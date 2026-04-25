#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 21
#define MAX_REGISTERED 10

int main(void)
{
    FILE* fa, * fb, * fc;
    char reg_words[MAX_REGISTERED][MAX_WORD_LEN];
    char word[MAX_WORD_LEN];

    int reg_count = 0;
    int i;
    int found;

    /* 파일 열기 */
    fa = fopen("a.txt", "r");
    fb = fopen("b.txt", "r");
    fc = fopen("c.txt", "w");

    if (fa == NULL || fb == NULL || fc == NULL)
    {
        printf("파일 열기 실패\n");
        return 1;
    }

    /* 1️⃣ 등록 단어 읽기 */
    while (reg_count < MAX_REGISTERED &&
        fscanf(fa, "%s", reg_words[reg_count]) != EOF)
    {
        reg_count++;
    }

    /* 2️⃣ 검출 대상 단어 검사 */
    while (fscanf(fb, "%s", word) != EOF)
    {
        found = 0;

        for (i = 0; i < reg_count; i++)
        {
            if (strcmp(word, reg_words[i]) == 0)
            {
                found = 1;
                break;
            }
        }

        /* 3️⃣ 등록되지 않은 단어 출력 */
        if (!found)
        {
            fprintf(fc, "%s\n", word);
        }
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);

    return 0;
}
