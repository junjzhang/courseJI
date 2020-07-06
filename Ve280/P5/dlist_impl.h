#ifndef __DLIST_IMPL_H__
#define __DLIST_IMPL_H__

template <class T>
bool Dlist<T>:: isEmpty() const{
    return first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node *np = new node;
    np->next = first;
    np->prev = nullptr;
    np->op = op;
    if(this->isEmpty()){
        first = last = np;
    }
    else{
        first->prev = np;
        first = np;
    }
    return;
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node *np = new node;
    np->next = nullptr;
    np->prev = last;
    np->op = op;
    if(isEmpty()){
        first = last = np;
    }
    else{
        last->next = np;
        last = np;
    }
}

template <class T>
T* Dlist<T>::removeFront(){
    if(isEmpty()){
        throw emptyList();
    }
    T* value = first->op;
    node* victim = first;
    if(first == last){
        delete victim;
        first = last = nullptr;
    }
    else{
        first = victim->next;
        first->prev = nullptr;
        delete victim;
    }
    return value;
}

template <class T>
T* Dlist<T>::removeBack(){
    if(isEmpty()){
        throw emptyList();
    }
    T* value = last->op;
    node* victim = last;
    if(first == last){
        delete victim;
        first = last = nullptr;
    }
    else{
        last = victim->prev;
        last->next = nullptr;
        delete victim;
    }
    return value;
}

template <class T>
Dlist<T>::Dlist(): first(nullptr), last(nullptr) {}

template <class T>
Dlist<T>::Dlist(const Dlist &l): first(nullptr), last(nullptr) {
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    if (&l！=this){
    removeAll();
    copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

template <class T>
void Dlist<T>::removeAll(){
    while(!isEmpty()){
       T* victim =removeFront();
       delete victim;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    node* temp = l.first;
    while(temp!=nullptr){
        T* new_op = new T(*temp->op);
        insertBack(new_op);
        temp = temp->next;
    }
    return;
}

#endif
