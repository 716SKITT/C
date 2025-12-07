#include <stdio.h>

int sumDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void toBinary(int n, char* bin) {
    if (n == 0) {
        bin[0] = '0';
        bin[1] = '\0';
        return;
    }
    
    char temp[32];
    int i = 0;
    
    while (n > 0) {
        temp[i++] = (n % 2) + '0';
        n /= 2;
    }
    
    for (int j = 0; j < i; j++) {
        bin[j] = temp[i - 1 - j];
    }
    bin[i] = '\0';
}

int toDecimal(char* bin) {
    int result = 0;
    for (int i = 0; bin[i] != '\0'; i++) {
        result = result * 2 + (bin[i] - '0');
    }
    return result;
}

int process(int n) {
    char bin[32];
    toBinary(n, bin);
    
    int sum = sumDigits(n);
    
    // Добавляем бит
    int len = 0;
    while (bin[len] != '\0') len++;
    
    bin[len] = (sum % 2 == 0) ? '0' : '1';
    bin[len + 1] = '\0';
    
    return toDecimal(bin);
}

int main() {
    int number, iterations;
    
    printf("Введите число: ");
    scanf("%d", &number);
    
    printf("Введите итераций: ");
    scanf("%d", &iterations);
    
    int current = number;
    
    for (int i = 0; i < iterations; i++) {
        printf("Итерация %d: %d -> ", i + 1, current);
        current = process(current);
        printf("%d\n", current);
    }
    
    printf("Итог: %d -> %d\n", number, current);
    
    return 0;
}