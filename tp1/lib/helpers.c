#include "../config/colors.c"

#define ERR(msg)       \
    printf(COLOR_RED); \
    printf("%s", msg); \
    printf(COLOR_RESET);

#define BR(ln)                   \
    for (int i = 0; i < ln; i++) \
        printf("\n");

#define RND rand() % 10

#define RPT(ch, times)              \
    for (int x = 0; x < times; x++) \
        printf("%s", ch);

#define YLW printf("%s", COLOR_YELLOW);
#define RST printf("%s", COLOR_RESET);
#define CYN printf("%s", COLOR_CYAN);