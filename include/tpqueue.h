// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Element {
    T value;
    Element* next;
    explicit Element(const T& val) : value(val), next(nullptr) {}
  };
  Element* first;

 public:
  TPQueue() : first(nullptr) {}

  ~TPQueue() {
    while (first) {
      Element* toDelete = first;
      first = first->next;
      delete toDelete;
    }
  }

  void push(const T& item) {
    Element* newElem = new Element(item);
    if (!first) {
      first = newElem;
      return;
    }
    if (item.prior > first->value.prior) {
      newElem->next = first;
      first = newElem;
      return;
    }
    Element* current = first;
    while (current->next && current->next->value.prior >= item.prior) {
      current = current->next;
    }
    newElem->next = current->next;
    current->next = newElem;
  }

  T pop() {
    if (!first) {
      throw std::out_of_range("Queue is empty!");
    }
    Element* toRemove = first;
    T tempVal = first->value;
    first = first->next;
    delete toRemove;
    return tempVal;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
