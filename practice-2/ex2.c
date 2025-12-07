#include <stdio.h>
#include <limits.h>

// Функция для проверки, помещается ли число в заданное количество байтов
int checkNumberFits(long long number, int bytes, int isSigned) {
    long long maxValue, minValue;
    
    if (isSigned) {
        // Для знаковых чисел: один бит на знак
        switch (bytes) {
            case 1: 
                maxValue = CHAR_MAX;
                minValue = CHAR_MIN;
                break;
            case 2: 
                maxValue = SHRT_MAX;
                minValue = SHRT_MIN;
                break;
            case 4: 
                maxValue = INT_MAX;
                minValue = INT_MIN;
                break;
            case 8: 
                maxValue = LLONG_MAX;
                minValue = LLONG_MIN;
                break;
            default:
                // Для других размеров вычисляем границы
                maxValue = (1LL << (bytes * 8 - 1)) - 1;
                minValue = -(1LL << (bytes * 8 - 1));
                break;
        }
        
        return (number >= minValue && number <= maxValue);
    } else {
        // Для беззнаковых чисел: все биты на значение
        switch (bytes) {
            case 1: 
                maxValue = UCHAR_MAX;
                break;
            case 2: 
                maxValue = USHRT_MAX;
                break;
            case 4: 
                maxValue = UINT_MAX;
                break;
            case 8: 
                maxValue = ULLONG_MAX;
                break;
            default:
                // Для других размеров вычисляем границу
                maxValue = (1ULL << (bytes * 8)) - 1;
                break;
        }
        
        return (number >= 0 && number <= maxValue);
    }
}

// Функция для вывода двоичного представления числа
void printBinary(long long number, int bytes, int isSigned) {
    unsigned long long mask;
    int totalBits = bytes * 8;
    
    printf("Двоичное представление (%d байт = %d бит):\n", bytes, totalBits);
    
    if (isSigned && number < 0) {
        // Для отрицательных знаковых чисел используем дополнительный код
        unsigned long long positiveNumber = -number;
        unsigned long long complement = (~positiveNumber + 1) & ((1ULL << totalBits) - 1);
        
        mask = 1ULL << (totalBits - 1);
        for (int i = 0; i < totalBits; i++) {
            printf("%c", (complement & mask) ? '1' : '0');
            if ((i + 1) % 8 == 0 && i != totalBits - 1) {
                printf(" ");
            }
            mask >>= 1;
        }
    } else {
        // Для положительных чисел
        unsigned long long unsignedNumber = (unsigned long long)number;
        
        mask = 1ULL << (totalBits - 1);
        for (int i = 0; i < totalBits; i++) {
            printf("%c", (unsignedNumber & mask) ? '1' : '0');
            if ((i + 1) % 8 == 0 && i != totalBits - 1) {
                printf(" ");
            }
            mask >>= 1;
        }
    }
    
    printf("\n");
}

int main() {
    long long number;
    int bytes;
    int isSigned;
    char formatChoice;
    
    printf("=== Преобразование числа в двоичный код ===\n\n");
    
    // Ввод числа
    printf("Введите число: ");
    scanf("%lld", &number);
    
    // Ввод количества байтов
    printf("Введите количество байтов (1, 2, 4, 8 или другое целое): ");
    scanf("%d", &bytes);
    
    if (bytes <= 0) {
        printf("Ошибка: количество байтов должно быть положительным.\n");
        return 1;
    }
    
    // Выбор формата (знаковый/беззнаковый)
    printf("Выберите формат:\n");
    printf("  s - знаковый (старший бит - знак)\n");
    printf("  u - беззнаковый (все биты - значение)\n");
    printf("Ваш выбор (s/u): ");
    scanf(" %c", &formatChoice);
    
    if (formatChoice == 's' || formatChoice == 'S') {
        isSigned = 1;
    } else if (formatChoice == 'u' || formatChoice == 'U') {
        isSigned = 0;
    } else {
        printf("Ошибка: неверный выбор формата.\n");
        return 1;
    }
    
    printf("\n");
    
    // Проверка, помещается ли число в выделенную память
    if (checkNumberFits(number, bytes, isSigned)) {
        printf("Число %lld помещается в %d байт(а) в %s формате.\n", 
               number, bytes, isSigned ? "знаковом" : "беззнаковом");
        
        // Вывод двоичного представления
        printBinary(number, bytes, isSigned);
        
        // Дополнительная информация
        printf("\nРазрядная сетка:\n");
        printf("- Всего бит: %d\n", bytes * 8);
        if (isSigned) {
            printf("- Старший бит (бит %d): знак (0=+, 1=-)\n", bytes * 8 - 1);
            printf("- Биты 0-%d: значение числа\n", bytes * 8 - 2);
        } else {
            printf("- Все биты (0-%d): значение числа\n", bytes * 8 - 1);
        }
    } else {
        printf("ОШИБКА: Число %lld не помещается в %d байт(а) в %s формате!\n", 
               number, bytes, isSigned ? "знаковом" : "беззнаковом");
        
        // Показываем допустимый диапазон
        if (isSigned) {
            long long maxValue = (1LL << (bytes * 8 - 1)) - 1;
            long long minValue = -(1LL << (bytes * 8 - 1));
            printf("Допустимый диапазон для знакового %d-байтового числа: [%lld, %lld]\n", 
                   bytes, minValue, maxValue);
        } else {
            unsigned long long maxValue = (1ULL << (bytes * 8)) - 1;
            printf("Допустимый диапазон для беззнакового %d-байтового числа: [0, %llu]\n", 
                   bytes, maxValue);
        }
    }
    
    return 0;
}