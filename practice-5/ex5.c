#include <stdio.h>
#define MAX_SIZE 10  // максимальный размер стека

// Структура для стека
typedef struct {
    int data[MAX_SIZE];
    int top;  // индекс вершины стека
} Stack;

// 1. Инициализация стека
void initStack(Stack *s) {
    s->top = -1;  // -1 означает, что стек пуст
    printf("Стек инициализирован.\n");
}

// 2. Проверка пустоты стека
int isEmpty(Stack *s) {
    return (s->top == -1);
}

// 3. Проверка заполненности стека
int isFull(Stack *s) {
    return (s->top == MAX_SIZE - 1);
}

// 4. Добавление элемента в стек (push)
int push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Ошибка: стек переполнен!\n");
        return 0;  // неудача
    }
    
    s->top++;
    s->data[s->top] = value;
    printf("Добавлен элемент: %d\n", value);
    return 1;  // успех
}

// 5. Удаление элемента из стека (pop)
int pop(Stack *s, int *value) {
    if (isEmpty(s)) {
        printf("Ошибка: стек пуст!\n");
        return 0;  // неудача
    }
    
    *value = s->data[s->top];
    s->top--;
    printf("Удален элемент: %d\n", *value);
    return 1;  // успех
}

// 6. Просмотр вершины стека без удаления (peek)
int peek(Stack *s, int *value) {
    if (isEmpty(s)) {
        printf("Ошибка: стек пуст!\n");
        return 0;  // неудача
    }
    
    *value = s->data[s->top];
    printf("Вершина стека: %d\n", *value);
    return 1;  // успех
}

// 7. Вывод содержимого стека
void printStack(Stack *s) {
    if (isEmpty(s)) {
        printf("Стек пуст.\n");
        return;
    }
    
    printf("Текущий стек (снизу вверх):\n");
    printf("Индекс | Значение\n");
    printf("-------|---------\n");
    
    for (int i = 0; i <= s->top; i++) {
        printf("  [%d]  |    %d\n", i, s->data[i]);
    }
    
    printf("\nВершина стека на позиции: %d\n", s->top);
}

// 8. Вывод информации о стеке
void stackInfo(Stack *s) {
    printf("\n=== Информация о стеке ===\n");
    printf("Максимальный размер: %d\n", MAX_SIZE);
    printf("Текущий размер: %d\n", s->top + 1);
    printf("Свободно мест: %d\n", MAX_SIZE - (s->top + 1));
    printf("Состояние: %s\n", 
           isEmpty(s) ? "пуст" : 
           isFull(s) ? "полон" : "есть элементы");
    printf("==========================\n\n");
}

int main() {
    Stack stack;
    int choice, value, result;
    
    // 1. Инициализация пустого стека
    initStack(&stack);
    
    // 2. Организация диалогового цикла
    do {
        printf("\n=== МЕНЮ ОПЕРАЦИЙ СО СТЕКОМ ===\n");
        printf("1. Добавить элемент (push)\n");
        printf("2. Удалить элемент (pop)\n");
        printf("3. Просмотреть вершину (peek)\n");
        printf("4. Вывести стек\n");
        printf("5. Информация о стеке\n");
        printf("6. Проверить пустоту\n");
        printf("7. Проверить заполненность\n");
        printf("8. Заполнить стек тестовыми данными\n");
        printf("0. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:  // Добавление элемента
                printf("Введите значение для добавления: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
                
            case 2:  // Удаление элемента
                if (pop(&stack, &value)) {
                    // value уже выведен в функции pop
                }
                break;
                
            case 3:  // Просмотр вершины
                peek(&stack, &value);
                break;
                
            case 4:  // Вывод стека
                printStack(&stack);
                break;
                
            case 5:  // Информация о стеке
                stackInfo(&stack);
                break;
                
            case 6:  // Проверка пустоты
                if (isEmpty(&stack)) {
                    printf("Стек пуст.\n");
                } else {
                    printf("Стек не пуст.\n");
                }
                break;
                
            case 7:  // Проверка заполненности
                if (isFull(&stack)) {
                    printf("Стек полон.\n");
                } else {
                    printf("Стек не полон.\n");
                }
                break;
                
            case 8:  // Тестовое заполнение
                printf("Добавляю тестовые данные...\n");
                for (int i = 1; i <= 5 && !isFull(&stack); i++) {
                    push(&stack, i * 10);
                }
                printf("Тестовые данные добавлены.\n");
                break;
                
            case 0:  // Выход
                printf("Завершение работы.\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}