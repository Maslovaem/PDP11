#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int max_five_digit = 0;

    // Поиск максимального пятизначного числа
    do {
        int num = 0;
        for (int i = 0; i < 5; i++) {
            num = num * 10 + digits[i];
        }
        max_five_digit = (num > max_five_digit) ? num : max_five_digit;
    } while (next_permutation(digits, digits + 10));

    // Создаем второе число из оставшихся цифр
    int remaining_digits[5];
    int index = 0;
    for (int i = 0; i < 10; i++) {
        if (!binary_search(digits, digits + 5, i)) {
            remaining_digits[index++] = i;
        }
    }
    int num = 0;
    for (int i = 0; i < 5; i++) {
        num = num * 10 + remaining_digits[i];
    }

    // Вычисляем НОД двух чисел
    int result = gcd(max_five_digit, num);

    printf("Максимальное пятизначное число: %d\n", max_five_digit);
    printf("Второе число: %d\n", num);
    printf("НОД: %d\n", result);

    return 0;
}
