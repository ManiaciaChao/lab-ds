//
// Created by user24 on 2019/10/14.
//

#ifndef LAB_DS_SEQLIST_CPP
#define LAB_DS_SEQLIST_CPP

#include "SeqList.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename T>
SeqList<T>::SeqList() {
    this->length = 0;
    this->size = INIT_LENGTH;
    this->elem = (T *) malloc(sizeof(T) * INIT_LENGTH);
    if (!this->elem) {
        exit(ERROR_OVERFLOW);
    }
}

template<typename T>
void SeqList<T>::save(const string& file_name) {
    ofstream f;
    f.open(file_name);
    for (int i = 1; i <= this->length; i++) {
        f << this->get(i);
        f << " ";
    }
    f << "\n";
    f.close();
}

template<typename T>
void SeqList<T>::load(const string& file_name) {
    this->clear();
    fstream f(file_name, std::ios_base::in);
    T val;
    while (f >> val) {
        this->push(val);
    }
}

template<typename T>
void SeqList<T>::destroy(SeqList *L) {
    free(L->elem);
    free(L);
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
    return this->elem[index - 1];
}

template<typename T>
int SeqList<T>::locate(T target, bool (*compare)(T &, T &)) {
    if (!this->isEmpty()) {
        for (int i = 1; i <= this->getLength(); i++) {
            if (compare(this->get(i), target))
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
                if (i > 1) {
                    return this->get(i - 1);
                } else {
                    throw ERROR_NO_ELEMENT;
                }
            }
    }
}

template<typename T>
T &SeqList<T>::next(T target) {
    if (this->isEmpty()) {
        throw ERROR_EMPTY;
    } else {
        for (int i = 1; i <= this->getLength(); i++)
            if (this->get(i) == target) {
                if (i < this->getLength()) {
                    return this->get(i + 1);
                } else {
                    throw ERROR_NO_ELEMENT;
                }
            }
    }
}

template<typename T>
T &SeqList<T>::insertBefore(int index, T elem) {
    if (index < 1 || index > this->length + 1) {
        throw ERROR_INDEX_INVALID;
    }
    if (this->getLength() == this->size) {
        T *newElem = (T *) realloc(this->elem, sizeof(T) * (this->size + INCREASE_LENGTH));
        if (!newElem) {
            exit(ERROR_OVERFLOW);
        }
        this->elem = newElem;
        this->size += INCREASE_LENGTH;
    }
    T *p, *q;
    q = &(this->elem[index - 1]);
    for (p = &(this->elem[this->getLength() - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = elem;
    this->length++;
    return elem;
}

template<typename T>
T SeqList<T>::remove(int index) {
    if (index < 1 || index > this->length) {
        throw ERROR_INDEX_INVALID;
    }
    T *p = 0, *q = 0, e;
    p = &this->get(index);
    e = *p;
    q = this->elem + this->length - 1;
    for (++p; p <= q; ++p)
        *(p - 1) = *p;
    this->length--;
    return e;
}

template<typename T>
int SeqList<T>::push(T target) {
    if (this->getLength() == this->size) {
        T *newElem = (T *) realloc(this->elem, sizeof(T) * (this->size + INCREASE_LENGTH));
        if (!newElem) {
            exit(ERROR_OVERFLOW);
        }
        this->elem = newElem;
        this->size += INCREASE_LENGTH;
    }
    this->elem[this->getLength()] = target;
    return ++this->length;
}

template<typename T>
T SeqList<T>::pop() {
    try {
        return this->remove(this->length);
    } catch (exception &e) {
        throw e;
    }
}

template<typename T>
void SeqList<T>::forEach(void (*callback)(T &)) {
    for (int i = 1; i <= this->getLength(); i++) {
        callback(this->get(i));
    }
}

#endif //LAB_DS_SEQLIST_H