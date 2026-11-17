#include <stdio.h>

int main(void)
{
    char *s = "42Bafg";

    // 1. กรณีพื้นฐาน
    printf("1. ปกติ          [%s]\n", s);

    // 2. ใช้ Precision อย่างเดียว (ตัดข้อความ)
    printf("2. Precision     [%.10s]\n", s);

    // 3. Width + Left-align (-)
    printf("3. Width + `-`   [%-12s]\n", s);

    // 4. Width + Zero flag (0) -> สังเกตว่า 0 จะถูกเมินและเติม Space แทน
    printf("4. Width + `0`   [%012s]\n", s);

    // 5. Left-align + Zero flag (`-0`) -> `-` จะยกเลิก `0` ทันที
    printf("5. `-` + `0`     [%-012s]\n", s);

    // 6. Width + Precision + Left-align (`-` และ `.`)
    printf("6. Width + Prec + `-`  [%-12.3s]\n", s);

    // 7. Width + Precision + Zero flag (`0` และ `.`) -> `0` ยังคงถูกเมิน
    printf("7. Width + Prec + `0`  [%012.3s]\n", s);

    // 8. ครบทุกตัว (`-`, `0`, `.`)
    printf("8. All (`-0.`)   [%-012.3s]\n", s);

    printf("9. All (`-0.`)   [%5.3s]\n", s);

    return (0);
}