#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list {
    char *str;
    struct list *next;
};

/* ソートされたリスト内で適切な位置にノードを挿入するヘルパー関数 */
struct list* sortedInsert(struct list* head, struct list* newNode) {
    struct list dummy;
    struct list* current = &dummy;
    dummy.next = head;

    while (current->next != NULL && ft_strcmp(current->next->str, newNode->str) < 0) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;

    return dummy.next;
}

/* 挿入ソートを使ってリストをソートする */
struct list* insertionSort(struct list* head) {
    struct list* sorted = NULL;

    while (head != NULL) {
        struct list* next = head->next;
        sorted = sortedInsert(sorted, head);
		printf("sorted->str:%s\n", sorted->str);
        head = next;
    }

    return sorted;
}

/* デバッグのためのリスト表示関数 */
void printList(struct list *node) {
    while (node != NULL) {
        printf("%s ", node->str);
        node = node->next;
    }
    printf("\n");
}

/* テストコード */
int main() {
    struct list* head = (struct list*)malloc(sizeof(struct list));
    head->str = "banana";
    head->next = (struct list*)malloc(sizeof(struct list));
    head->next->str = "orange";
    head->next->next = (struct list*)malloc(sizeof(struct list));
    head->next->next->str = "apple";
    head->next->next->next = NULL;

    printf("Before sorting:\n");
    printList(head);

    head = insertionSort(head);

    printf("After sorting:\n");
    printList(head);

    return 0;
}
