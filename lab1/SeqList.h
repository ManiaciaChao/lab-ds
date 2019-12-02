//
// Created by user24 on 2019/10/14.
<<<<<<< HEAD
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
=======
// Defined SeqList Template
//

#ifndef LAB_DS_SEQLIST_H
#define LAB_DS_SEQLIST_H // avoid recycled including.
#define INIT_LENGTH 8
#define INCREASE_LENGTH 8
#define ERROR_OVERFLOW (-2)
#define ERROR_EMPTY std::runtime_error("List is empty!") // Prefer using try-catch than returning an status code
#define ERROR_INDEX_INVALID std::runtime_error("Index invalid!")
#define ERROR_NO_ELEMENT std::runtime_error("No prior/next element founded!")

#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <cstdlib>
>>>>>>> 6f64abf56672e2083b6d811935c95993048fedb0

using std::string;

template<typename T>
class SeqList {
private:
<<<<<<< HEAD
=======
    // Encapsulation. None of these props should be public.
>>>>>>> 6f64abf56672e2083b6d811935c95993048fedb0
    int length{};
    int size{};
    T *elem;
public:
<<<<<<< HEAD
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
=======
    SeqList(); // Constructor of SeqList, which will initialize a SeqList instance.
    ~SeqList(); // Destructor of SeqList, which will free this->elem.

    // auto someFunction() -> someType is trailing return type grammar introduced in C++11.
    static auto destroy(SeqList &L) -> void; // Call destructor. Though, it's an static funtion.
    inline auto isEmpty() -> bool; // inline functions usually have better performance than normal functions
    inline auto getLength() -> int;

    auto save(const string &file_name) -> void; // Save elements into a text file.
    auto load(const string &file_name) -> void; // Load elements from a text file.

    auto enlarge()-> void; // Enlarge SeqLists with step size of INCREASE_LENGTH.
    auto clear() -> void; // Clear elements.
    auto get(int index) -> T &; // Get element of given index, which is from 1 to this->length.
    auto locate(T target, bool(T &, T &)) -> int; // Return index of an element by a bool function.
    auto prior(T) -> T &; // Return the prior element of a given element if it exists.
    auto next(T) -> T &; // Return the next element of a given element if it exists.
    auto insertBefore(int index, T elem) -> T &; // Insert an element before the given index.
    auto remove(int index) -> T; // Remove the index-th element if it exists.
    auto forEach(void (*callback)(T &elem)) -> void; // Traverse the SeqList and execute the given callback

    auto push(T) -> int; // Push an element like a stack;
    auto pop() -> T; // Pop an element like a stack;

    auto operator[](int index) -> T &; // The same as get();

};

template<typename T>
SeqList<T>::SeqList() {
    // Initialize a SeqList
    this->length = 0;
    this->size = INIT_LENGTH;
    this->elem = (T *) malloc(sizeof(T) * INIT_LENGTH);
    if (!this->elem) {
        exit(ERROR_OVERFLOW);
    }
}

template<typename T>
SeqList<T>::~SeqList() {
    delete this->elem;
}

template<typename T>
void SeqList<T>::save(const string &file_name) {
    std::ofstream f;
    f.open(file_name);
    for (int i = 1; i <= this->length; i++) {
        f << this->get(i);
        f << " ";
    }
    f << "\n";
    f.close();
}

template<typename T>
void SeqList<T>::load(const string &file_name) {
    this->clear(); // clear before loading
    std::fstream f(file_name, std::ios_base::in);
    T val;
    while (f >> val) {
        this->push(val);
    }
}

template<typename T>
void SeqList<T>::destroy(SeqList &L) {
    delete &L;
}

template<typename T>
void SeqList<T>::enlarge()  {
    T *newElem = (T *) realloc(this->elem, sizeof(T) * (this->size + INCREASE_LENGTH));
    if (!newElem) {
        exit(ERROR_OVERFLOW);
    }
    this->elem = newElem;
    this->size += INCREASE_LENGTH;
}

template<typename T>
void SeqList<T>::clear() {
    this->length = 0;
}

template<typename T>
bool SeqList<T>::isEmpty() {
    return this->length == 0;
}

template<typename T>
int SeqList<T>::getLength() {
    return this->length;
}

template<typename T>
T &SeqList<T>::get(int index) {
    if (this->isEmpty() || index > this->getLength() || index <= 0) {
        throw ERROR_INDEX_INVALID;
    }
    return this->elem[index - 1]; // for index starts from 1.
}

template<typename T>
auto SeqList<T>::operator[](int index) -> T & {
    return this->get[index];
}

template<typename T>
int SeqList<T>::locate(T target, bool (*compare)(T &, T &)) {
    if (!this->isEmpty()) {
        for (int i = 1; i <= this->getLength(); i++) {
            if (compare(this->get(i), target)) // call compare function
                return i;
        }
        return 0;
    }

    return 0;
}

template<typename T>
T &SeqList<T>::prior(T target) {
    if (this->isEmpty()) {
        throw ERROR_EMPTY;
    } else {
        for (int i = 1; i <= this->getLength(); i++)
            if (this->get(i) == target) {
                if (i <= 1) {
                    throw ERROR_NO_ELEMENT; // The first element has no prior element.
                } else {
                    return this->get(i - 1);
                }
            }
        throw ERROR_NO_ELEMENT; // Given element not matched.
    }
}

template<typename T>
T &SeqList<T>::next(T target) {
    if (this->isEmpty()) {
        throw ERROR_EMPTY;
    } else {
        for (int i = 1; i <= this->getLength(); i++)
            if (this->get(i) == target) {
                if (i >= this->getLength()) { // The last element has no next element.
                    throw ERROR_NO_ELEMENT;
                } else {
                    return this->get(i + 1);
                }
            }
        throw ERROR_NO_ELEMENT; // Given element not matched.
    }
}

template<typename T>
T &SeqList<T>::insertBefore(int index, T elem) {
    if (index < 1 || index > this->length + 1) {
        throw ERROR_INDEX_INVALID; // Invalid index for this SeqList.
    }
    if (this->getLength() == this->size) { // The SeqList is fulled and need to be enlarged.
        this->enlarge();
    }
    T *p, *q;
    q = &(this->elem[index - 1]);
    for (p = &(this->elem[this->getLength() - 1]); p >= q; --p) {
        *(p + 1) = *p; // Move elements afterwards.
    }
    *q = elem; // Assign value.
    this->length++;
    return elem;
}

template<typename T>
T SeqList<T>::remove(int index) {
    if (index < 1 || index > this->length) {
        throw ERROR_INDEX_INVALID; // Invalid index for this SeqList.
    }
    T *p = 0, *q = 0, e;
    p = &this->get(index); // Save the pointer.
    e = *p;
    q = this->elem + this->length - 1;
    for (++p; p <= q; ++p)
        *(p - 1) = *p; // Move elements afterwards.
    this->length--;
    return e;
}

template<typename T>
int SeqList<T>::push(T target) {
    if (this->getLength() == this->size) { // The SeqList is fulled and need to be enlarged.
        this->enlarge();
    }
    this->elem[this->getLength()] = target;
    return ++this->length; // return length
}

template<typename T>
T SeqList<T>::pop() {
    try {
        return this->remove(this->length); // return value
    } catch (std::exception &e) {
        throw e;
    }
}

template<typename T>
void SeqList<T>::forEach(void (*callback)(T &)) {
    for (int i = 1; i <= this->getLength(); i++) {
        callback(this->get(i)); // callback
    }
}
>>>>>>> 6f64abf56672e2083b6d811935c95993048fedb0

#endif //LAB_DS_SEQLIST_H
