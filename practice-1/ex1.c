#include <stdio.h>

// Функция для перевода числа в строку в заданной системе счисления
void convertToBase(int number, int base, char result[]) {
    char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int index = 0;
    
    // Обрабатываем случай, когда число равно 0
    if (number == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }
    
    // Временный массив для хранения цифр в обратном порядке
    char temp[100];
    int tempIndex = 0;
    
    // Основной алгоритм преобразования
    while (number > 0) {
        int remainder = number % base;
        temp[tempIndex++] = digits[remainder];
        number = number / base;
    }
    
    // Переворачиваем результат (так как цифры были получены в обратном порядке)
    for (int i = 0; i < tempIndex; i++) {
        result[i] = temp[tempIndex - 1 - i];
    }
    result[tempIndex] = '\0';
}

// Функция для проверки корректности основания системы счисления
int isValidBase(int base) {
    return (base >= 2 && base <= 36);
}

int main() {
    int number, base;
    char converted[100];
    
    printf("Преобразование десятичного числа в произвольную систему счисления\n\n");
    
    // Ввод десятичного числа
    printf("Введите целое неотрицательное число: ");
    scanf("%d", &number);
    
    // Проверка на отрицательное число
    if (number < 0) {
        printf("Ошибка: программа работает только с неотрицательными числами.\n");
        return 1;
    }
    
    // Ввод основания системы счисления
    printf("Введите основание системы счисления (2-36): ");
    scanf("%d", &base);
    
    // Проверка корректности основания
    if (!isValidBase(base)) {
        printf("Ошибка: основание должно быть от 2 до 36.\n");
        return 1;
    }
    
    // Преобразование числа
    convertToBase(number, base, converted);
    
    // Вывод результата
    printf("\nРезультат преобразования:\n");
    printf("Десятичное число: %d\n", number);
    printf("В системе счисления с основанием %d: %s\n", base, converted);
    
    return 0;
}