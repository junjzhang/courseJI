#include <iostream>
#include <cstdlib>
#include <cassert>
#include "p2.h"

using namespace std;

void test_bool(list_t v, int i, bool (*fn) (list_t));
bool even(int i);

int main(){
	int i;
	list_t testList;
	testList=list_make();
	/*
	 * Test for int size(list_t list)
	 * Expected output:
	 * 0
	 * 1
	 * 2
	 */
	i=size(testList);
	cout<<i<<endl;
	testList=list_make(1,testList);
	i=size(testList);
	cout<<i<<endl;
	testList=list_make(2,testList);
	i=size(testList);
	cout<<i<<endl;
	/*
	 * Test for bool memberOf(list_t list, int val)
	 * Expected output:
	 * "1 is in the list"
	 * "0 is in the list"
	 * "4 is not in the list"
	 * "-1 is not in the list"
	 */
	if (memberOf(testList,1)){
		cout<<"1 is in the list"<<endl;
	}
	if (memberOf(testList,0)){
		cout<<"o is in the list"<<endl;
	}
	if (!memberOf(testList,4)){
		cout<<"4 is not in the list"<<endl;
	}
	if (!memberOf(testList,-1)){
		cout<<"-1 is not in the list"<<endl;
	}
	/*
     * Test for dot(list_t v1, list_t v2)
	 * Expected output:
     * "v1 dot v2: 10"
	 * "v1 dot v3: 20"
	 * "v1 dot v4: 8"
	 * "v3 dot v4: 11"
	 * ("exit the program")
     */
	list_t v1 = list_make();
	for (int i=1;i<=3;i++){
		v1 = list_make(i,v1);
	}// v1: (3 2 1)
	list_t v2 = list_make();
	for (int i=1;i<=3;i++){
        v2 = list_make(4-i,v2);
    }// v2: (1 2 3)
	list_t v3 = list_make();
    for (int i=1;i<=4;i++){
        v3 = list_make(i,v3);
    }// v3: (4 3 2 1)
	list_t v4 = list_make();
	for (int i=1;i<=2;i++){
		v4 = list_make(i,v4);
	}// v4: (2 1)
	list_t v5 = list_make();//v5: ()
	cout<<"v1 dot v2: "<<dot(v1,v2)<<endl;
	cout<<"v1 dot v3: "<<dot(v1,v3)<<endl;
	cout<<"v1 dot v4: "<<dot(v1,v4)<<endl;
	
	cout<<"v3 fot v4: "<<dot(v3,v4)<<endl;
	//cout<<"v1 dot v5: "<<dot(v1,v5)<<endl;
	/*
	 * Test for bool isIncreasing(list_t v)
	 * Expected output:
	 * "v1 is false"
	 * "v2 is true"
	 * "v5 is true"
	 * "v6 is true"
	 */
	list_t v6 = list_make();
	v6 = list_make(0,v6);// v6: (0)
	test_bool(v1,1,isIncreasing);
	test_bool(v2,2,isIncreasing);
	test_bool(v5,5,isIncreasing);
	test_bool(v6,6,isIncreasing);
	/*
	 * Test for list_t reverse(list_t v)
	 * Expected output:
	 * "(1 2 3) () (0) (1 2 3 4 5 6 7 8 9 10)"
	 */
	list_t v7 = reverse(v1);
	list_t v8 = reverse(v5);
	list_t v9 = reverse(v6);
	list_print(v7);
	list_print(v8);
	list_print(v9);
	list_t v10 = list_make();// v10: (10 9 8 7 6 5 4 3 2 1)
    for (int i=1;i<=10;i++){
        v10 = list_make(i,v10);
    }
    list_t v11 = reverse(v10);
    list_print(v11);
    /*
     * Test for list_t append(list_t first, list_t second)
     * Expected output:
     * "()(0)(0)(0 0)(3 2 1)(3 2 1)(10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10)"
     */
    list_t v12 = append(v5,v5);
    list_t v13 = append(v5,v6);
    list_t v14 = append(v6,v5);
    list_t v15 = append(v6,v6);
    list_t v16 = append(v5,v1);
    list_t v17 = append(v1,v5);
    list_t v18 = append(v10,v11);
    list_print(v12); list_print(v13); list_print(v14); list_print(v15); list_print(v16); list_print(v17); list_print(v18);
    /*
     * Test for bool isArithmeticSequence(list_t v)
     * Expected output:
     * "v5 is true"
     * "v6 is true"
     * "v1 is true"
     * "v10 is true"
     * "v18 is false"
     */
    test_bool(v5,5,isArithmeticSequence); test_bool(v6,6,isArithmeticSequence); test_bool(v1,1,isArithmeticSequence);
    test_bool(v10,10,isArithmeticSequence); test_bool(v18,18,isArithmeticSequence);
    /*
     * Test for list_t filter_odd(list_t list)
     * Expected output:
     * "() () (1) (1 3) (3 1)"
     */
    list_t v19 = filter_odd(v5);
    list_t v20 = filter_odd(v6);
    list_t v21 = list_make();
    v21 = list_make(1,v21);
    v21 = filter_odd(v21);
    list_t v22 = filter_odd(v2);
    list_t v23 = filter_odd(v1);
    list_print(v19); list_print(v20); list_print(v21); list_print(v22); list_print(v23);
    cout<<endl;
    /*
     * Test for list_t filter(list_t list, bool (*fn)(int))
     * Expected output:
     * "() (0) () (2) (2)"
     */
    list_t v24 = filter(v5,even);
    list_t v25 = filter(v6,even);
    list_t v26 = list_make();
    v26 = list_make(1,v26);
    v26 = filter(v26,even);
    list_t v27 = filter(v2,even);
    list_t v28 = filter(v1,even);
    list_print(v24); list_print(v25); list_print(v26); list_print(v27); list_print(v28);
    cout<<endl;
    /*
     * Test for list_t unique(list_t list)
     * Expected output:
     * "() (0) (4 3 2 1)"
     */
     list_t v29 = unique(v5);
     list_t v30 = unique(v6);
     list_t v31 = list_make();
     for (int i=1;i<=4;i++){
     	for (int j=1;j<=i;j++){
     		v31 = list_make(i,v31);
     	}
     }
     list_t v32 = unique(v31);//v32: (4 3 2 1)
     list_print(v29); list_print(v30); list_print(v32);
     cout<<endl;
     /*
     * Test for list_t unique(list_t list)
     * Expected output:
     * "() (0) (0) (4 3 2 1 3 2 1) (3 2 1 4 3 2 1) (4 3 3 2 1 2 1)"
     */
     list_t v33 = insert_list (v5,v5,0);
     list_t v34 = insert_list (v6,v5,1);
     list_t v35 = insert_list (v5,v6,0);
     list_t v36 = insert_list (v32,v1,4);
     list_t v37 = insert_list (v1,v32,3);
     list_t v38 = insert_list (v32,v1,2);
     list_print(v33); list_print(v34); list_print(v35);
     list_print(v36); list_print(v37); list_print(v38);
     cout<<endl;
     /*
     * Test for list_t chop(list_t list, unsigned int n)
     * Expected output:
     * "() () (0) (4 3)"
     */
     list_t v39 = chop (v5,0);
     list_t v40 = chop (v6,1);
     list_t v41 = chop (v6,0);
     list_t v42 = chop (v32,2);
     list_print(v39); list_print(v40); list_print(v41);list_print(v42);
     cout<<endl;
     /*
      * Test for int tree_sum(tree_t tree)
      * Expected output: "int tree_sum(tree_t tree) works well"
      */
      tree_t t1 = tree_make();
      // t1 is empty
      tree_t t2 = tree_make(1,tree_make(),tree_make());
      /* t2:
          1
         / \
      */
      tree_t t3 = tree_make(2,tree_make(1,tree_make(),tree_make()),tree_make());
      /* t3:
            2
           / \
          1
         / \
      */
      tree_t t4 = tree_make(2,tree_make(1,tree_make(),tree_make()),tree_make(1,tree_make(),tree_make()));
      /* t4:
            2
           / \
          1  1
         /\ /\
      */
      assert(tree_sum(t1)==0);
      assert(tree_sum(t2)==1);
      assert(tree_sum(t3)==3);
      assert(tree_sum(t4)==4);
      cout<<"int tree_sum(tree_t tree) works well"<<endl;
      /*
      * Test for bool tree_search(tree_t tree, int val)
      * Expected output: "bool tree_search(tree_t tree, int val) works well"
      */
      assert(!tree_search(t1,1));
      assert(tree_search(t2,1));
      assert(tree_search(t3,1));
      assert(tree_search(t3,2));
      assert(!tree_search(t3,3));
      cout<<"bool tree_search(tree_t tree, int val) works well"<<endl;
      /*
      * Test for int depth(tree_t tree)
      * Expected output: "int depth(tree_t tree) works well"
      */
      assert(depth(t1)==0);
      assert(depth(t2)==1);
      assert(depth(t3)==2);
      assert(depth(t4)==2);
      cout<<"int depth(tree_t tree) works well"<<endl;
      /*
      * Test for int tree_max(tree_t tree)
      * Expected output: "int tree_max(tree_t tree) works well"
      */
      assert(tree_max(t2)==1);
      assert(tree_max(t3)==2);
      assert(tree_max(t4)==2);
      cout<<"int tree_max(tree_t tree) works well"<<endl;
      /*
      * Test for list_t traversal(tree_t tree)
      * Expected output: "() (1) (1 2) (1 2 1) (2 6 3 7 4 5 8)"
      */
      tree_t t5 = tree_make(4, tree_make(2, tree_make(), tree_make(3, tree_make(6, tree_make(), tree_make()), tree_make(7, tree_make(), tree_make()))), tree_make(5, tree_make(), tree_make(8, tree_make(), tree_make())));
      /*t5:
                       4
                      / \
                     2  5
                    /\ / \
                     3   8
                    /\  /\
                   6 7
                  /\/\
       */
      list_print(traversal(t1));
      list_print(traversal(t2));
      list_print(traversal(t3));
      list_print(traversal(t4));
      list_print(traversal(t5));
      cout<<endl;
      /*
      * Test for bool tree_hasMonotonicPath(tree_t tree)
      * Expected output: "bool tree_hasMonotonicPath(tree_t tree) works well"
      */
      tree_t t8 = tree_make(1, tree_make(2, tree_make(), tree_make(1, tree_make(), tree_make())), tree_make(2, tree_make(), tree_make(1, tree_make(), tree_make())));
      assert(!tree_hasMonotonicPath(t1));
      assert(tree_hasMonotonicPath(t2));
      assert(tree_hasMonotonicPath(t3));
      assert(tree_hasMonotonicPath(t4));
      assert(tree_hasMonotonicPath(t5));
      assert(!tree_hasMonotonicPath(t8));
      cout<<"bool tree_hasMonotonicPath(tree_t tree) works well"<<endl;
      /*
      * Test for bool tree_allPathSumGreater(tree_t tree, int sum)
      * Expected output: "bool tree_allPathSumGreater(tree_t tree, int sum) works well"
      */
      assert(tree_allPathSumGreater(t2,0));
      assert(!tree_allPathSumGreater(t2,1));
      assert(tree_allPathSumGreater(t5,14));
      assert(!tree_allPathSumGreater(t5,15));
      cout<<"bool tree_allPathSumGreater(tree_t tree, int sum) works well"<<endl;
      /*
      * Test for bool covered_by(tree_t A, tree_t B)
      * Expected output: "bool covered_by(tree_t A, tree_t B) works well"
      */
      assert(covered_by(t1, t2));
      assert(!covered_by(t2, t1));
      assert(covered_by(t3, t4));
      assert(!covered_by(t4, t5));
      cout<<"bool covered_by(tree_t A, tree_t B) works well"<<endl;
      /*
      * Test for bool contained_by(tree_t A, tree_t B)
      * Expected output: "bool contained_by(tree_t A, tree_t B) works well"
      */
      tree_t t6 = tree_make(2, tree_make(), tree_make(3, tree_make(), tree_make()));
      /*t6:
                     2
                    / \
                      3
                     / \
      */
      assert(contained_by(t1, t2));
      assert(!contained_by(t2, t1));
      assert(contained_by(t2, t3));
      assert(contained_by(t3, t4));
      assert(contained_by(t2, t4));
      assert(!contained_by(t3, t5));
      assert(contained_by(t6, t5));
      cout<<"bool conntained_by(tree_t A, tree_t B) works well"<<endl;
      /*
      * Test for tree_t insert_tree(int elt, tree_t tree)
      * Expected output: "tree_t insert_tree(int elt, tree_t tree)"
      */
      tree_t t7 = tree_make(4, tree_make(2, tree_make(), tree_make(3, tree_make(), tree_make())), tree_make(5, tree_make(), tree_make()));
      /*
                   4
                  / \
                 2  5
                /\ /\
                 3
                /\
      */
      tree_print(insert_tree(1,t1));
      cout << endl;
      tree_print(insert_tree(1,t2));
      cout << endl;
      tree_print(insert_tree(2,t3));
      cout << endl;
      tree_print(insert_tree(3,t7));
      cout << endl;
}

void test_bool(list_t v, int i, bool (*fn) (list_t)){
	if (fn(v)){
		cout << "v" << i << " is true" << endl;
	}
	else {
		cout << "v" << i << " is false" << endl;
	}
}

bool even (int i){
	bool b;
	if (i%2==0){
		b=true;
	}
	else {
		b=false;
	}
	return b;
}
