//
// Created by user24 on 2019/10/17.
//
#define LIST_NUM 8
typedef int ElemType;

#include <cstring>
#include "SeqList.h"

using std::to_string;
using std::cin;
using std::cout;
using std::endl;
using std::exception;

void clear() {
#ifdef _WIN32 // on Windows Command Line
    system("cls");
#else // on Unix and Unix-like shell
    system("clear");
#endif
}


template<typename T>
void displayMenu(SeqList<T> *seqLists[], int index) {
    // Rewrite menu display function with printf.
    printf("----------------------------------------\n");
    printf("** Current Index is %d **\n", index);
    if (seqLists[index] == nullptr ) {
        printf("%-20s%-20s\n", "1. InitList", "20. ChangeIndex");
    } else {
        printf("%-20s%-20s\n", "1. InitList", "10. ListInsert");
        printf("%-20s%-20s\n", "2. DestroyList", "11. ListDelete");
        printf("%-20s%-20s\n", "3. ClearList", "12. ListTraverse");
        printf("%-20s%-20s\n", "4. ListEmpty", "13. Push");
        printf("%-20s%-20s\n", "5. ListLength", "14. Pop");
        printf("%-20s%-20s\n", "6. GetElem", "15. Save");
        printf("%-20s%-20s\n", "7. LocateElem", "16. Load");
        printf("%-20s%-20s\n", "8. PriorElem", "20. ChangeIndex");
        printf("%-20s%-20s\n", "9. NextElem", "");
    }
}

int main() {
    // Initialize a pointer array for multi-list management.
    SeqList<ElemType> *seqLists[LIST_NUM];
    memset(seqLists, 0, sizeof(seqLists));
    int option = 1;
    int index = 0;
    clear();
    while (option) {
        try {
            displayMenu(seqLists, index);
            cin >> option; // accept keyboard input as option
            clear();
            if (seqLists[index] == nullptr && (option != 1 && option != 20 && option != 0)) {
                // To avoid nullptr being operated.
                cout << "Exception: " << "List Not Initialized!" << endl;
                continue;
            }
            switch (option) {
                case 0: {
                    break;
                }
                case 1: {
                    clear();
                    cout << "InitList" << endl;
                    seqLists[index] = new SeqList<ElemType>();
                    break;
                }
                case 2: {
                    clear();
                    cout << "DestroyList" << endl;
                    SeqList<ElemType>::destroy(*seqLists[index]); // Free space
                    seqLists[index]= nullptr; // Assign nullptr
                    break;
                }
                case 3: {
                    clear();
                    cout << "ClearList" << endl;
                    seqLists[index]->clear();
                    break;
                }
                case 4: {
                    clear();
                    cout << "ListEmpty" << endl;
                    cout << (seqLists[index]->isEmpty() ? "True" : "False") << endl;
                    break;
                }
                case 5: {
                    clear();
                    cout << "ListLength" << endl;
                    cout << seqLists[index]->getLength() << endl;
                    break;
                }
                case 6: {
                    clear();
                    cout << "GetElem" << endl;
                    int i = 0;
                    cin >> i;
                    cout << seqLists[index]->get(i) << endl;
                    break;
                }
                case 7: {
                    clear();
                    cout << "LocateElem" << endl;
                    ElemType i = 0;
                    cin >> i;
                    cout << seqLists[index]->locate(
                            i,
                            // Lambda expression introduced in C++11;
                            [](ElemType &a, ElemType &b) -> bool { return a > b; })
                         << endl;
                    break;
                }
                case 8: {
                    clear();
                    cout << "PriorElem" << endl;
                    ElemType i = 0;
                    cin >> i;
                    cout << seqLists[index]->prior(i) << endl;
                    break;
                }
                case 9: {
                    clear();
                    cout << "NextElem" << endl;
                    ElemType i = 0;
                    cin >> i;
                    cout << seqLists[index]->next(i) << endl;
                    break;
                }
                case 10: {
                    clear();
                    cout << "ListInsert" << endl;
                    int i = 0;
                    ElemType v = 0;
                    cin >> i;
                    cin >> v;
                    seqLists[index]->insertBefore(i, v);
                    break;
                }
                case 11: {
                    clear();
                    cout << "ListDelete" << endl;
                    int i = 0;
                    cin >> i;
                    cout << seqLists[index]->remove(i) << endl;
                    break;
                }
                case 12: {
                    clear();
                    cout << "ListTraverse" << endl;
                    seqLists[index]
                            ->forEach([](ElemType &v) -> void {
                                cout << v << " "; // Lambda expression introduced in C++11;
                            });
                    cout << endl;
                    break;
                }
                case 13: {
                    clear();
                    cout << "Push" << endl;
                    ElemType v;
                    cin >> v;
                    seqLists[index]->push(v);
                    break;
                }
                case 14: {
                    clear();
                    cout << "Pop" << endl;
                    ElemType v = seqLists[index]->pop();
                    cout << v << endl;
                    break;
                }
                case 15: {
                    clear();
                    cout << "Save" << endl;
                    seqLists[index]->save(to_string(index) + ".sav");
                    break;
                }
                case 16: {
                    clear();
                    cout << "Load" << endl;
                    seqLists[index]->load(to_string(index) + ".sav");
                    break;
                }
                case 20 : {
                    clear();
                    cout << "ChangeIndex" << endl;
                    int i;
                    cin >> i;
                    if (i>0 && i<LIST_NUM) {
                        index = i; // Avoid overstepping.
                    } else {
                        cout << "Invalid index" << endl;
                    }
                    continue;
                }
                default: {
                    break;
                }
            }
        } catch (exception &e) {
            cout << "RuntimeException: " << e.what() << endl;
        }
    }

}
