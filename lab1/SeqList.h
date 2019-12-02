//
// Created by user24 on 2019/10/14.
//

#ifndef LAB_DS_SEQLIST_H
#define LAB_DS_SEQLIST_H
#define INIT_LENGTH 8
#define INCREASE_LENGTH 8
#define ERROR_OVERFLOW (-2)
#define ERROR_EMPTY runtime_error("List is empty!")
#define ERROR_INDEX_INVALID runtime_error("Index invalid!")
#define ERROR_NO_ELEMENT runtime_error("No prior/next element founded!")

#include <string>
#include <exception>

using std::string;

template<typename T>
class SeqList {
private:
    int length{};
    int size{};
    T *elem;
public:
    SeqList();

//    ~SeqList();

    void save(const string& file_name);

    void load(const string& file_name);

    static void destroy(SeqList ** L);

    void clear(); // Covered

    bool isEmpty(); // Covered

    int getLength(); // Covered

    T &get(int index); // Covered

    int locate(T target, bool(T &, T &)); // Covered

    T &prior(T); // Covered

    T &next(T); // Covered

    T &insertBefore(int index, T elem); // Covered

    T remove(int index); // Covered

    void forEach(void (*callback)(T &elem)); // Covered

    int push(T); // Covered

    T pop();
};

#endif //LAB_DS_SEQLIST_H
