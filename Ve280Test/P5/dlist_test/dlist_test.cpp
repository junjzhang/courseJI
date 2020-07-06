// Test for the methods of the class dlist.
#include "dlist.h"
#include <iostream>
#include <string>
#include <cassert>
using std::string;
using std::cout;
using std::endl;

// Effect: convert a Dlist of string to a c++ string for output. If the
// list is empty, returns empty string. Its correctness depends on the
// correctness of removeFront() and the copy constructor!!
string ls_str(const Dlist<string>& ls);

int main()
{
    cout << "Remember to use valgrind to test if there is any memory leak!";
    cout << endl;
    // Test default constructor and isEmpty().
    Dlist<string> ls;
    assert(ls.isEmpty());

    // Test insertFront(), removeFront(), and isEmpty().
    ls.insertFront(new string("ab"));
    assert(!ls.isEmpty());
    ls.insertFront(new string("a"));
    string* p = ls.removeFront();
    assert(*p == "a");
    delete p;
    assert(!ls.isEmpty());
    p = ls.removeFront();
    assert(*p == "ab");
    delete p;
    assert(ls.isEmpty());

    // Test ls_str(). Since it depends on removeBack() and the copy
    // constructor and we have already tested removeFront(), its
    // correctness implies the correctness of the copy constructor.
    ls.insertFront(new string("abc"));
    ls.insertFront(new string("ab"));
    ls.insertFront(new string("a"));
    assert(ls_str(ls) == "a ab abc ");
    // After this point, ls_str() is correct, and we can use it to test
    // other methods.

    // Test insertBack() and removeBack().
    Dlist<string> ls2;
    ls2.insertBack(new string("a"));
    ls2.insertBack(new string("ab"));
    assert(ls_str(ls2) == "a ab ");
    p = ls2.removeBack();
    assert(*p == "ab");
    delete p;
    p = ls2.removeBack();
    assert(*p == "a");
    delete p;
    assert(ls2.isEmpty());

    // Combined test for the four insert and remove methods.
    ls2.insertFront(new string("ab"));
    ls2.insertFront(new string("a"));
    p = ls2.removeBack();
    assert(*p == "ab");
    delete p;
    p = ls2.removeBack();
    assert(*p == "a");
    delete p;
    assert(ls2.isEmpty());
    ls2.insertBack(new string("a"));
    ls2.insertBack(new string("ab"));
    p = ls2.removeFront();
    assert(*p == "a");
    delete p;
    p = ls2.removeFront();
    assert(*p == "ab");
    delete p;
    assert(ls2.isEmpty());
    // Test remove methods when ls2 is empty.
    try {
        ls2.removeFront();
        // If removeFront() does not throw, terminate the program.
        throw -1;
    }
    catch (emptyList& e) {
        // Do nothing.
    }
    try {
        ls2.removeBack();
        // If removeFront() does not throw, terminate the program.
        throw -1;
    }
    catch (emptyList& e) {
        // Do nothing.
    }

    // Explicitly test the copy constructor.
    // At the beginning of test, ls_str(ls) == "a ab abc ".
    auto ls3(ls);
    // Insert an element to ls to test if the copy is a deep copy.
    ls.insertFront(new string("aa"));
    assert(ls_str(ls3) == "a ab abc ");
    // Delete an element from ls3 to test if the copy is a deep copy.
    delete ls3.removeBack();
    assert(ls_str(ls) == "aa a ab abc ");

    // Test the assignment operator. First insert some elements into ls2
    // to test if there is any memory leak when removeAll() is called.
    ls2.insertFront(new string("ab"));
    ls2.insertFront(new string("a"));
    ls2 = ls;
    // Insert an element to ls to test if the copy is a deep copy.
    ls.insertBack(new string("abcde"));
    assert(ls_str(ls2) == "aa a ab abc ");
    // Delete an element from ls2 to test if the copy is a deep copy.
    delete ls2.removeFront();
    assert(ls_str(ls) == "aa a ab abc abcde ");
    cout << "Test finished successfully!" << endl;
}

string ls_str(const Dlist<string>& ls)
{
    string result;
    auto ls_copy(ls);
    while (!ls_copy.isEmpty()) {
        string* p = ls_copy.removeFront();
        result = result + *p + ' ';
        delete p;
    }
    return result;
}
