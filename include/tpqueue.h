// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

struct SYM {
  char ch;
  int prior;
 public:
  char GetChar()const {
    return ch;
  }
  int GetPrior() const {
    return prior;
  }
};

template<typename T>
class TPQueue {
 private:
  struct Item {
    T data;
    Item* next;
    Item* prev;    
  };
  Item* head;
  Item* tail;
  TPQueue::Item* create(const T&);
 public:
  TPQueue() : head(nullptr), tail(nullptr){};
  //~TPQueue();
  void addHead(const T&);
  void addTail(const T&);
  const T pop();
  void push(const T&);
};

template<typename T>
typename::TPQueue<T>::Item* TPQueue<T>::create(const T& value)
{
  Item* temp = new Item;
  temp->data = value;
  temp->next = nullptr;
  temp->prev = nullptr;
  return temp;
}


template<typename T>
void TPQueue<T>::addTail(const T& value)
{
  if (head && tail) {
    tail->next = create(value);
    tail->next->prev = tail;
    tail = tail->next;
  } else{
      head = create(value);
      tail = head;
    }
}


template<typename T>
void TPQueue<T>::addHead(const T&value)
{
  if (head && tail) {
    Item* temp = create(value);
    temp->next = head;
    temp->next->prev = temp;
    head = temp;
  } else {
      head = tail = create(value);
    }
}
 
template<typename T>
const T TPQueue<T>::pop()
{
 // if (head) {
    Item* temp = head->next;
      if (temp) {
        temp->prev = nullptr;
      } else {
          tail = nullptr;
        }
    T data = head->data;
    delete head;
    head = temp;
    return data;
 // }
}



/*template<typename T>
TPQueue<T>::~TPQueue()
{
    while (head);
    pop();
}*/


template<typename T>
void TPQueue<T>::push(const T& value)
{
  if(head&&tail) {
    if (head->data.GetPrior() < value.GetPrior()) {
      addHead(value);
      return;
    }
    if (tail->data.GetPrior() > value.GetPrior()) {
      addTail(value);
      return;
    }
    if (head->next==nullptr && head->data.GetPrior() <= value.GetPrior()) {
      addTail(value);
      return;
    }
    Item* temp = tail;
    while (temp) {
      while (value.GetPrior() > temp->data.GetPrior()) {
        temp = temp->prev;
        continue;
      }
      Item* new_item = create(value);
      new_item->prev = temp;
      new_item->next = temp->next;
      temp->next->prev = new_item;
      temp->next = new_item;
      break;
            //temp = temp->next;
    }
  } else {
      addHead(value);
    }
}
#endif  // INCLUDE_TPQUEUE_H_
