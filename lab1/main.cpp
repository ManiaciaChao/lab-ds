//
// Created by user24 on 2019/10/17.
//
#define LIST_NUM 8

#include <cstring>
#include "SeqList.h"
#include "SeqList.cpp"

using std::to_string;

#ifdef _WIN32
void clear() {
    system("cls");
}
#else
void clear() {
    system("clear");
}
#endif

template<typename T>
void displayMenu(SeqList<T> *seqLists[], int index) {
    printf("----------------------------------------\n");
    printf("** Current Index is %d **\n", index);
    if (seqLists[index] == nullptr) {
        printf("%-20s%-20s\n", "1. InitList", "0. ChangeIndex");
    } else {
        printf("%-20s%-20s\n", "1. InitList", "10. ListInsert");
        printf("%-20s%-20s\n", "2. DestroyList", "11. ListDelete");
        printf("%-20s%-20s\n", "3. ClearList", "12. ListTraverse");
        printf("%-20s%-20s\n", "4. ListEmpty", "13. Save");
        printf("%-20s%-20s\n", "5. ListLength", "14. Load");
        printf("%-20s%-20s\n", "6. GetElem", "15. ChangeIndex");
        printf("%-20s%-20s\n", "7. LocateElem", "");
        printf("%-20s%-20s\n", "8. PriorElem", "");
        printf("%-20s%-20s\n", "9. NextElem", "");
    }
}

int main() {
    SeqList<int> *seqLists[LIST_NUM];
    memset(seqLists, 0, sizeof(seqLists));
    int option = 1;
    int index = 0;
    while (option) {

        try {
            clear();
            displayMenu(seqLists, index);
            cin >> option;
            switch (option) {
                case 0: {
                    break;
                }
                case 1: {
                    cout << "InitList" << endl;
                    seqLists[index] = new SeqList<int>();
                    break;
                }
                case 2: {
                    cout << "DestroyList" << endl;
                    SeqList<int>::destroy(seqLists[index]);
                    break;
                }
                case 3: {
                    cout << "ClearList" << endl;
                    seqLists[index]->clear();
                    break;
                }
                case 4: {
                    cout << "ListEmpty" << endl;
                    printf("%s", seqLists[index]->isEmpty() ? "True" : "False");
                    break;
                }
                case 5: {
                    cout << "ListLength" << endl;
                    printf("%d", seqLists[index]->getLength());
                    break;
                }
                case 6: {
                    cout << "GetElem" << endl;
                    int i = 0;
                    cin >> i;
                    printf("%d", seqLists[index]->get(i));

                    break;
                }
                case 7: {
                    cout << "LocateElem" << endl;
                    int i = 0;
                    cin >> i;
                    printf("%d", seqLists[index]->locate(
                            i,
                            [](int &a, int &b) -> bool { return a > b; }));
                    break;
                }
                case 8: {
                    cout << "PriorElem" << endl;
                    int i = 0;
                    cin >> i;
                    printf("%d", seqLists[index]->prior(i));
                    break;
                }
                case 9: {
                    cout << "NextElem" << endl;
                    int i = 0;
                    cin >> i;
                    printf("%d", seqLists[index]->next(i));
                    break;
                }
                case 10: {
                    cout << "ListInsert" << endl;
                    int i = 0, v = 0;
                    cin >> i;
                    cin >> v;
                    seqLists[index]->insertBefore(i, v);
                    break;
                }
                case 11: {
                    cout << "ListDelete" << endl;
                    int i = 0;
                    cin >> i;
                    printf("%d", seqLists[index]->remove(i));
                    break;
                }
                case 12: {
                    cout << "ListTraverse" << endl;
                    seqLists[index]
                            ->forEach([](int &v) -> void { printf("%d ", v); });
                    break;
                }
                case 13: {
                    cout << "Save" << endl;
                    int i = 0;
                    seqLists[index]->save(to_string(index) + ".sav");
                    break;
                }
                case 14: {
                    cout << "Load" << endl;
                    int i = 0;
                    seqLists[index]->load(to_string(index) + ".sav");
                    break;
                }
                case 15 : {
                    cout << "ChangeIndex" << endl;
                    cin >> index;
                    continue;
                }
                default: {

                }
            }
        } catch (char *err) {
            printf("%s\n", err);
        }
    }

}
