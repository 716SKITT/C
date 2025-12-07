#include <stdio.h>
#include <string.h>
#include <math.h>

// Функция для перевода числа в двоичную строку
void toBinary(int num, char* bin) {
    if (num == 0) {
        strcpy(bin, "0");
        return;
    }
    
    char temp[32];
    int i = 0;
    
    while (num > 0) {
        temp[i++] = (num % 2) + '0';
        num /= 2;
    }
    
    for (int j = 0; j < i; j++) {
        bin[j] = temp[i - 1 - j];
    }
    bin[i] = '\0';
}

// Функция для вычисления количества контрольных битов
int calcParityBits(int dataBits) {
    int r = 0;
    while ((1 << r) < (dataBits + r + 1)) {
        r++;
    }
    return r;
}

// Функция для вычисления позиций контрольных битов (степени двойки)
int isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Функция для вычисления значения контрольного бита
int calcParityBit(int pos, char* hamming, int totalBits) {
    int parity = 0;
    
    // Проверяем все биты, кроме контрольных
    for (int i = 1; i <= totalBits; i++) {
        if (!isPowerOfTwo(i)) {  // если не контрольная позиция
            // Проверяем, содержит ли позиция i в битовом представлении единицу в разряде pos
            if ((i & pos) == pos) {
                parity ^= (hamming[i - 1] - '0');
            }
        }
    }
    
    return parity;
}

int main() {
    int number;
    char binary[32];
    char hamming[64] = {0};
    
    printf("Введите число: ");
    scanf("%d", &number);
    
    // 1. Получаем двоичное представление
    toBinary(number, binary);
    printf("\n1. Двоичный код исходного числа %d: %s\n", number, binary);
    
    int dataBits = strlen(binary);
    printf("   Количество информационных битов: %d\n", dataBits);
    
    // 2. Вычисляем количество контрольных битов
    int parityBits = calcParityBits(dataBits);
    printf("2. Количество контрольных битов (r): %d\n", parityBits);
    
    // 3. Вычисляем общую длину кода Хэмминга
    int totalBits = dataBits + parityBits;
    printf("3. Общая длина кода Хэмминга: %d + %d = %d бит\n", 
           dataBits, parityBits, totalBits);
    
    // 4. Заполняем позиции контрольных битов
    printf("\n4. Заполняем кодовое слово:\n");
    
    // Инициализируем все позиции символом 'x' (не определено)
    for (int i = 0; i < totalBits; i++) {
        hamming[i] = 'x';
    }
    
    // Размещаем контрольные биты на позициях степеней двойки
    for (int i = 0; i < parityBits; i++) {
        int pos = (1 << i) - 1; // позиции: 0, 1, 3, 7, 15... (индексация с 0)
        if (pos < totalBits) {
            hamming[pos] = 'p'; // помечаем как контрольный бит
        }
    }
    
    // Размещаем информационные биты на оставшихся позициях
    int dataIndex = 0;
    for (int i = 0; i < totalBits; i++) {
        if (hamming[i] != 'p') {
            hamming[i] = binary[dataIndex++];
        }
    }
    
    printf("   Позиции (1-indexed): ");
    for (int i = 0; i < totalBits; i++) {
        printf("%3d", i + 1);
    }
    printf("\n");
    
    printf("   Контрольные биты:    ");
    for (int i = 0; i < totalBits; i++) {
        printf("%3c", isPowerOfTwo(i + 1) ? 'P' : ' ');
    }
    printf("\n");
    
    printf("   Кодовое слово:       ");
    for (int i = 0; i < totalBits; i++) {
        printf("%3c", hamming[i]);
    }
    printf("\n");
    
    // 5. Вычисляем значения контрольных битов
    printf("\n5. Вычисляем контрольные биты:\n");
    
    for (int i = 0; i < parityBits; i++) {
        int pos = (1 << i); // позиции: 1, 2, 4, 8... (1-indexed)
        
        printf("   P%d контролирует биты: ", i + 1);
        
        // Находим биты, которые контролирует данный контрольный бит
        int count = 0;
        for (int j = 1; j <= totalBits; j++) {
            if (!isPowerOfTwo(j) && ((j & pos) == pos)) {
                printf("%d", j);
                count++;
                if (count < 8) printf(", "); // ограничиваем вывод
            }
        }
        printf("...\n");
    }
    
    // Вычисляем значения контрольных битов
    for (int i = 0; i < parityBits; i++) {
        int pos = (1 << i); // позиция контрольного бита (1-indexed)
        int parity = calcParityBit(pos, hamming, totalBits);
        
        // Записываем значение контрольного бита
        int idx = pos - 1; // переводим в 0-indexed
        hamming[idx] = parity + '0';
        
        printf("   P%d = XOR контролируемых битов = %d\n", i + 1, parity);
    }
    
    // 6. Выводим итоговый код Хэмминга
    printf("\n6. Итоговый код Хэмминга:\n");
    
    printf("   Двоичный: ");
    for (int i = 0; i < totalBits; i++) {
        printf("%c", hamming[i]);
    }
    
    // Вычисляем десятичное значение
    int hammingValue = 0;
    for (int i = 0; i < totalBits; i++) {
        hammingValue = hammingValue * 2 + (hamming[i] - '0');
    }
    
    printf("\n   Десятичный: %d\n", hammingValue);
    
    // 7. Показываем разметку
    printf("\n7. Разметка кода Хэмминга:\n");
    printf("   Позиция: ");
    for (int i = 0; i < totalBits; i++) {
        printf("%2d ", i + 1);
    }
    printf("\n");
    
    printf("   Тип:     ");
    for (int i = 0; i < totalBits; i++) {
        if (isPowerOfTwo(i + 1)) {
            printf(" P ");
        } else {
            printf(" D ");
        }
    }
    printf("\n");
    
    printf("   Значение:");
    for (int i = 0; i < totalBits; i++) {
        printf("%2c ", hamming[i]);
    }
    printf("\n");
    
    return 0;
}