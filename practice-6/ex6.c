#include <stdio.h>
#define MAX_SIZE 5  // небольшой размер для демонстрации переполнения

// ==================== ОБЫЧНАЯ ОЧЕРЕДЬ СО СДВИГОМ ====================
typedef struct {
    int data[MAX_SIZE];
    int front;  // индекс первого элемента
    int rear;   // индекс последнего элемента
    int count;  // количество элементов
} LinearQueue;

void initLinearQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    printf("Линейная очередь инициализирована.\n");
}

int isLinearEmpty(LinearQueue *q) {
    return (q->count == 0);
}

int isLinearFull(LinearQueue *q) {
    return (q->count == MAX_SIZE);
}

int enqueueLinear(LinearQueue *q, int value) {
    if (isLinearFull(q)) {
        printf("Ошибка: линейная очередь переполнена!\n");
        return 0;
    }
    
    q->rear++;
    q->data[q->rear] = value;
    q->count++;
    printf("Добавлен элемент: %d\n", value);
    return 1;
}

int dequeueLinear(LinearQueue *q, int *value) {
    if (isLinearEmpty(q)) {
        printf("Ошибка: линейная очередь пуста!\n");
        return 0;
    }
    
    *value = q->data[q->front];
    printf("Удален элемент: %d\n", *value);
    
    // Сдвигаем все элементы на одну позицию вперед
    for (int i = 0; i < q->count - 1; i++) {
        q->data[i] = q->data[i + 1];
    }
    
    q->rear--;
    q->count--;
    
    return 1;
}

void printLinearQueue(LinearQueue *q) {
    if (isLinearEmpty(q)) {
        printf("Линейная очередь пуста.\n");
        return;
    }
    
    printf("Линейная очередь (от начала к концу):\n");
    printf("Индекс | Значение\n");
    printf("-------|---------\n");
    
    for (int i = 0; i < q->count; i++) {
        printf("  [%d]  |    %d\n", i, q->data[i]);
    }
    
    printf("\nВсего элементов: %d\n", q->count);
    printf("Начало: индекс %d\n", q->front);
    printf("Конец:  индекс %d\n", q->rear);
}

void linearQueueInfo(LinearQueue *q) {
    printf("\n=== Информация о линейной очереди ===\n");
    printf("Максимальный размер: %d\n", MAX_SIZE);
    printf("Текущий размер: %d\n", q->count);
    printf("Свободно мест: %d\n", MAX_SIZE - q->count);
    printf("Состояние: %s\n", 
           isLinearEmpty(q) ? "пуста" : 
           isLinearFull(q) ? "полна" : "есть элементы");
    printf("===============================\n");
}

// ==================== КОЛЬЦЕВАЯ ОЧЕРЕДЬ ====================
typedef struct {
    int data[MAX_SIZE];
    int front;  // индекс первого элемента
    int rear;   // индекс после последнего элемента
    int count;  // количество элементов
} CircularQueue;

void initCircularQueue(CircularQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    printf("Кольцевая очередь инициализирована.\n");
}

int isCircularEmpty(CircularQueue *q) {
    return (q->count == 0);
}

int isCircularFull(CircularQueue *q) {
    return (q->count == MAX_SIZE);
}

int enqueueCircular(CircularQueue *q, int value) {
    if (isCircularFull(q)) {
        printf("Ошибка: кольцевая очередь переполнена!\n");
        return 0;
    }
    
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX_SIZE;  // кольцевой переход
    q->count++;
    printf("Добавлен элемент: %d\n", value);
    return 1;
}

int dequeueCircular(CircularQueue *q, int *value) {
    if (isCircularEmpty(q)) {
        printf("Ошибка: кольцевая очередь пуста!\n");
        return 0;
    }
    
    *value = q->data[q->front];
    printf("Удален элемент: %d\n", *value);
    
    q->front = (q->front + 1) % MAX_SIZE;  // кольцевой переход
    q->count--;
    
    return 1;
}

void printCircularQueue(CircularQueue *q) {
    if (isCircularEmpty(q)) {
        printf("Кольцевая очередь пуста.\n");
        return;
    }
    
    printf("Кольцевая очередь (от начала к концу):\n");
    printf("Физический индекс | Значение\n");
    printf("------------------|---------\n");
    
    int index = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("       [%d]        |    %d\n", index, q->data[index]);
        index = (index + 1) % MAX_SIZE;
    }
    
    printf("\nВсего элементов: %d\n", q->count);
    printf("Начало: индекс %d\n", q->front);
    printf("Конец:  индекс %d\n", (q->rear - 1 + MAX_SIZE) % MAX_SIZE);
    printf("Следующая позиция для добавления: %d\n", q->rear);
}

void circularQueueInfo(CircularQueue *q) {
    printf("\n=== Информация о кольцевой очереди ===\n");
    printf("Максимальный размер: %d\n", MAX_SIZE);
    printf("Текущий размер: %d\n", q->count);
    printf("Свободно мест: %d\n", MAX_SIZE - q->count);
    printf("Состояние: %s\n", 
           isCircularEmpty(q) ? "пуста" : 
           isCircularFull(q) ? "полна" : "есть элементы");
    printf("Начало: индекс %d\n", q->front);
    printf("Конец:  индекс %d\n", q->rear);
    printf("===============================\n");
}

// ==================== ГЛАВНОЕ МЕНЮ ====================
int main() {
    LinearQueue linearQ;
    CircularQueue circularQ;
    int choice, queueType, value;
    
    initLinearQueue(&linearQ);
    initCircularQueue(&circularQ);
    
    do {
        printf("\n=== ГЛАВНОЕ МЕНЮ ===\n");
        printf("Выберите тип очереди:\n");
        printf("1. Линейная очередь со сдвигом\n");
        printf("2. Кольцевая очередь\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &queueType);
        
        if (queueType == 0) {
            printf("Завершение работы.\n");
            break;
        }
        
        if (queueType != 1 && queueType != 2) {
            printf("Неверный выбор.\n");
            continue;
        }
        
        // Меню операций для выбранного типа очереди
        do {
            if (queueType == 1) {
                printf("\n=== ЛИНЕЙНАЯ ОЧЕРЕДЬ ===\n");
            } else {
                printf("\n=== КОЛЬЦЕВАЯ ОЧЕРЕДЬ ===\n");
            }
            
            printf("1. Добавить элемент (enqueue)\n");
            printf("2. Удалить элемент (dequeue)\n");
            printf("3. Вывести очередь\n");
            printf("4. Информация об очереди\n");
            printf("5. Проверить пустоту\n");
            printf("6. Проверить заполненность\n");
            printf("7. Заполнить тестовыми данными\n");
            printf("8. Вернуться к выбору типа очереди\n");
            printf("0. Выход из программы\n");
            printf("Выберите операцию: ");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1:  // Добавление элемента
                    printf("Введите значение для добавления: ");
                    scanf("%d", &value);
                    if (queueType == 1) {
                        enqueueLinear(&linearQ, value);
                    } else {
                        enqueueCircular(&circularQ, value);
                    }
                    break;
                    
                case 2:  // Удаление элемента
                    if (queueType == 1) {
                        dequeueLinear(&linearQ, &value);
                    } else {
                        dequeueCircular(&circularQ, &value);
                    }
                    break;
                    
                case 3:  // Вывод очереди
                    if (queueType == 1) {
                        printLinearQueue(&linearQ);
                    } else {
                        printCircularQueue(&circularQ);
                    }
                    break;
                    
                case 4:  // Информация
                    if (queueType == 1) {
                        linearQueueInfo(&linearQ);
                    } else {
                        circularQueueInfo(&circularQ);
                    }
                    break;
                    
                case 5:  // Проверка пустоты
                    if (queueType == 1) {
                        if (isLinearEmpty(&linearQ)) {
                            printf("Линейная очередь пуста.\n");
                        } else {
                            printf("Линейная очередь не пуста.\n");
                        }
                    } else {
                        if (isCircularEmpty(&circularQ)) {
                            printf("Кольцевая очередь пуста.\n");
                        } else {
                            printf("Кольцевая очередь не пуста.\n");
                        }
                    }
                    break;
                    
                case 6:  // Проверка заполненности
                    if (queueType == 1) {
                        if (isLinearFull(&linearQ)) {
                            printf("Линейная очередь полна.\n");
                        } else {
                            printf("Линейная очередь не полна.\n");
                        }
                    } else {
                        if (isCircularFull(&circularQ)) {
                            printf("Кольцевая очередь полна.\n");
                        } else {
                            printf("Кольцевая очередь не полна.\n");
                        }
                    }
                    break;
                    
                case 7:  // Тестовые данные
                    printf("Добавляю тестовые данные...\n");
                    for (int i = 1; i <= 3; i++) {
                        if (queueType == 1) {
                            if (!isLinearFull(&linearQ)) {
                                enqueueLinear(&linearQ, i * 10);
                            }
                        } else {
                            if (!isCircularFull(&circularQ)) {
                                enqueueCircular(&circularQ, i * 10);
                            }
                        }
                    }
                    break;
                    
                case 8:  // Возврат к выбору типа
                    printf("Возвращаемся к выбору типа очереди...\n");
                    break;
                    
                case 0:  // Выход
                    printf("Завершение работы.\n");
                    return 0;
                    
                default:
                    printf("Неверный выбор. Попробуйте снова.\n");
            }
            
        } while (choice != 8);  // Возврат при выборе 8
        
    } while (1);  // Бесконечный цикл, выход через case 0
    
    return 0;
}