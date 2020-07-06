#ifndef VEC_H
#define VEC_H

class vec{
//Overview: a simple version of vector to realize dynamic int array
private:
    int* array;
    int size;
public:
    vec();
    //EFFECTS: Construct an empty vec
    vec(int n);
    //EFFECTS: Construct an empty vec of size n
    vec(const vec& v);
    //EFFECTS: Construct a vec by v
    vec(const vec& v,int begin,int end);
    //EFFECTS: Construct a vec from v's begin elements to end elements
    //MODIFIES: This
    ~vec();
    //EFFECTS: Realease the assign memory
    //MODIFIES: This
    int get_size();
    //EFFECTS: return the size
    int& operator[](int i);
    //EFFECTS: return the reference of the ith interger in the array
    //MODIFIES: array[i]
    void output();
    //EFFECTS: print the vec in the form of standard way
};

#endif