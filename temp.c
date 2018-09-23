#include <stdio.h>

struct thing {
    int val;
    const char* str;
    int another_val;
};
struct thing data1 = {1, "one"};
struct thing data2 = {2, "two"};

/* The following two pointers will be placed in "my_custom_section".
 * Store pointers (instead of structs) in "my_custom_section" to ensure
 * matching alignment when accessed using iterator in main(). */
struct thing *p_one __attribute__((section("my_custom_section"))) = &data1; 
struct thing *p_two __attribute__((section("my_custom_section"))) = &data2;

/* The linker automatically creates these symbols for "my_custom_section". */
extern struct thing *__start_my_custom_section;
extern struct thing *__stop_my_custom_section;

int main(void) {
    struct thing **iter = &__start_my_custom_section;
    for ( ; iter < &__stop_my_custom_section; ++iter) {
        printf("Have thing %d: '%s'\n", (*iter)->val, (*iter)->str);
    }
    return 0;
}
