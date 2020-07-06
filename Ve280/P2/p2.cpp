#include"p2.h"

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

static list_t reverse_helper(list_t list, list_t result);
static list_t unique_helper(list_t list,list_t list_pop,list_t result);
static list_t chop_helper(list_t list, unsigned int n);
static bool tree_MP_helper(tree_t tree, int last_value);

int size(list_t list)
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
{
    if (list_isEmpty(list)) {
        return 0;
    }
    else{
        return size(list_rest(list))+1;
    }
}

bool memberOf(list_t list, int val)
// EFFECTS: Returns true if the value "val" appears in "list".
//          Returns false otherwise.
{
    if(list_isEmpty(list)){
        return false;
    }
    else if(list_first(list)==val){
        return true;
    }
    else{
        return memberOf(list_rest(list),val);
    }
}

int dot(list_t v1, list_t v2)
// REQUIRES: Both "v1" and "v2" are non-empty
//
// EFFECTS: Treats both lists as vectors. Returns the dot
//          product of the two vectors. If one list is longer
//          than the other, ignore the longer part of the vector.
{
    if(list_isEmpty(v1)||list_isEmpty(v2)){
        return 0;
    }
    else{
        return (dot(list_rest(v1),list_rest(v2)) + list_first(v1)*list_first(v2));
    }
}

bool isIncreasing(list_t v)
// EFFECTS: Checks if the list of integers is increasing.
//          A list is increasing if and only if no element
//          is smaller than its previous element. By default,
//          an empty list and a list of a single element are
//          increasing.
//
//          For example: (), (2), (1, 1), and (1, 2, 3, 3, 5) are
//          all increasing. (2, 1) and (1, 2, 3, 2, 5) are not.
{
    if(list_isEmpty(v)||list_isEmpty(list_rest(v))){
        return true;
    }
    else if(list_first(v)>list_first(list_rest(v))){
        return false;
    }
    else{
        return isIncreasing(list_rest(v));
    }
}

list_t reverse(list_t list)
// EFFECTS: Returns the reverse of "list".
//
//          For example: the reverse of ( 3 2 1 ) is ( 1 2 3 ).
{
    return reverse_helper(list,list_make());
}

static list_t reverse_helper(list_t list, list_t result)
//EFFECTS: Returns list_make(list_first(list),result)
{
    if (list_isEmpty(list)){
        return result;
    }
    else{
        return reverse_helper(list_rest(list),list_make(list_first(list),result));
    }
}

list_t append(list_t first, list_t second)
// EFFECTS: Returns the list (first second).
//
//          For example: append(( 2 4 6 ), ( 1 3 )) gives
//          the list ( 2 4 6 1 3 ).
{
    if (list_isEmpty(first)){
        return second;
    }
    else{
        return list_make(list_first(first),append(list_rest(first),second));
    }
}

bool isArithmeticSequence(list_t v)
// EFFECTS: Checks if the list of integers forms an
//          arithmetic sequence. By default, an empty list and
//          a list of a single element are arithmetic sequences.
//
//          For example: (), (1), (1, 3, 5, 7), and (2, 8, 14, 20)
//          are arithmetic sequences. (1, 2, 4), (1, 3, 3),
//          and (2, 4, 8, 10) are not.
{
    if (list_isEmpty(v)||list_isEmpty(list_rest(v))||list_isEmpty(list_rest(list_rest(v)))){
        return true;
    }
    else if ((list_first(v)-list_first(list_rest(v)))!=(list_first(list_rest(v))-list_first(list_rest(list_rest(v))))){
        return false;
    }
    else{
        return isArithmeticSequence(list_rest(v));
    }
}

list_t filter_odd(list_t list)
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value,
//          in the order in which they appeared in list.
//
//          For example, if you apply filter_odd to the list
//          ( 3 4 1 5 6 ), you would get the list ( 3 1 5 ).
{
    if (list_isEmpty(list)){
        return list_make();
    }
    else{
        if (list_first(list)%2){
            return list_make(list_first(list),filter_odd(list_rest(list)));
        }
        else{
            return filter_odd(list_rest(list));
        }
    }
}

list_t filter(list_t list, bool (*fn)(int))
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
//
//          For example, if predicate bool odd(int a) returns true
//          if a is odd, then the function filter(list, odd) has
//          the same behavior as the function filter_odd(list).
{
    if (list_isEmpty(list)){
        return list_make();
    }
    else{
        if (fn(list_first(list))){
            return list_make(list_first(list),filter(list_rest(list),fn));
        }
        else{
            return filter(list_rest(list),fn);
        }
    }
}

list_t unique(list_t list)
// EFFECTS: Returns a new list comprising of each unique element
//          in "list". The order is determined by the first
//          occurrence of each unique element in "list".
//
//          For example, if you apply unique to the list
//          (1 1 2 1 3 5 5 3 4 5 4), you would get (1 2 3 5 4).
//          If you apply unique to the list (0 1 2 3), you would
//          get (0 1 2 3)
{
    return reverse(unique_helper(list,list_make(),list_make()));
}

static list_t unique_helper(list_t list,list_t list_pop,list_t result)
//EFFECTS: If list_first(list) is unique, then return unique_helper(list_rest(list),
//list_make(list_first(list),result))
{
    if (list_isEmpty(list)){
        return result;
    }
    else{
        if (memberOf(list_pop,list_first(list))){
            return unique_helper(list_rest(list),list_pop,result);
        }
        else if (memberOf(list_rest(list),list_first(list))){
            return unique_helper(list_rest(list),list_make(list_first(list),list_pop),list_make(list_first(list),result));
        }
        else{
            return unique_helper(list_rest(list),list_pop,list_make(list_first(list),result));
        }
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n)
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//          followed by any remaining elements of "first".
//
//          For example: insert(( 1 2 3 ), ( 4 5 6 ), 2)
//          gives ( 1 2 4 5 6 3 ).
{
    if(n==0){
        return append(second,first);
    }
    else{
        return list_make(list_first(first),insert_list(list_rest(first),second,n-1));
    }
}

list_t chop(list_t list, unsigned int n)
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
{
     return chop_helper(list,size(list)-n);
}

static list_t chop_helper(list_t list, unsigned int n)
{
    if(n==0){
        return list_make();
    }
    else{
        return list_make(list_first(list),chop_helper(list_rest(list),n-1));
    }
}
//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree)
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
{
    if (tree_isEmpty(tree)){
        return 0;
    }
    else{
        return tree_sum(tree_left(tree))+tree_sum(tree_right(tree))+tree_elt(tree);
    }
}

bool tree_search(tree_t tree, int val)
// EFFECTS: Returns true if the value "val" appears in "tree".
//          Returns false otherwise.
{
    if (tree_isEmpty(tree)){
        return false;
    }
    else if (tree_elt(tree)==val){
        return true;
    }
    else {
        return (tree_search(tree_left(tree),val)||tree_search(tree_right(tree),val));
    }
}

int depth(tree_t tree)
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero if "tree" is empty.
//
// For example, the tree
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3        8
//                        / \      / \
//                       6   7
//                      / \ / \
//
// has depth 4.
// The element 4 is on the first layer.
// The elements 2 and 5 are on the second layer.
// The elements 3 and 8 are on the third layer.
// The elements 6 and 7 are on the fourth layer.
//
{
    if (tree_isEmpty(tree)){
        return 0;
    }
    else{
        return 1+max(depth(tree_left(tree)),depth(tree_right(tree)));
    }
}

int tree_max(tree_t tree)
// REQUIRES: "tree" is non-empty.
//
// EFFECTS: Returns the largest element in "tree".
{
    if(tree_isEmpty(tree)){
    }
    if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))){
        return tree_elt(tree);
    }
    else if (tree_isEmpty(tree_left(tree))){
        return max(tree_elt(tree),tree_max(tree_right(tree)));
    }
    else if (tree_isEmpty(tree_right(tree))){
        return max(tree_elt(tree),tree_max(tree_left(tree)));
    }
    else{
        return max(tree_elt(tree),max(tree_max(tree_left(tree)),tree_max(tree_right(tree))));
    }
}

list_t traversal(tree_t tree)
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal. An in-order traversal prints
//          the "left most" element first, then the second-left-most,
//          and so on, until the right-most element is printed.
//
//          For any node, all the elements of its left subtree
//          are considered as on the left of that node and
//          all the elements of its right subtree are considered as
//          on the right of that node.
//
// For example, the tree:
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3
//                        / \
//
// would return the list
//
//       ( 2 3 4 5 )
//
// An empty tree would print as:
//
//       ( )
//
{
    if (tree_isEmpty(tree)){
        return list_make();
    }
    else{
        return append(traversal(tree_left(tree)),list_make(tree_elt(tree),traversal(tree_right(tree))));
    }
}

bool tree_hasMonotonicPath(tree_t tree)
// EFFECTS: Returns true if and only if "tree" has at least one
//          root-to-leaf path such that all the elements along the
//          path form a monotonically increasing or decreasing
//          sequence.
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
//
//          An empty tree has no root-to-leaf path.
//
//          A monotonically increasing (decreasing) sequence is a
//          sequence of numbers where no number is smaller (larger)
//          than its previous number.
//
// For example, the tree:
//
//                           4
//                         /   \
//                        /
//                       8
//                      / \
//                     3   16
//                    / \  / \
//
// has two root-to-leaf paths: 4->8->3 and 4->8->16.
// Since the numbers on the path 4->8->16 form a monotonically
// increasing sequence, the function should return true.
// If we change 8 into 20, there is no such a path.
// Thus, the function should return false.
{
    if (tree_isEmpty(tree)){
        return false;
    }
    else if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))){
        return true;
    }
    else{
        return (tree_MP_helper(tree_left(tree),tree_elt(tree))||tree_MP_helper(tree_right(tree),tree_elt(tree)));
    }
}

static bool tree_MP_helper(tree_t tree, int last_value)
//EFFECTS: Compares tree_elt(tree) with elts of left and right 
//chidren, if the trend of decreasing or in increasing continue
//then, return tree_MP_helper of left and right children.
{
    if (tree_isEmpty(tree)){
        return false;
    }
    else if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))){
        return true;
    }
    else if(tree_isEmpty(tree_left(tree))){
        if ((tree_elt(tree_right(tree))-tree_elt(tree))*(tree_elt(tree)-last_value)<0){
            return false;
        }
        else{
        return tree_MP_helper(tree_right(tree), tree_elt(tree));
        }
    }
    else if(tree_isEmpty(tree_right(tree))){
        if((tree_elt(tree_left(tree))-tree_elt(tree))*(tree_elt(tree)-last_value)<0){
            return false;
        }
        else{
            return tree_MP_helper(tree_left(tree),tree_elt(tree));
        }
    }
    else{
        if(((tree_elt(tree_left(tree))-tree_elt(tree))*(tree_elt(tree)-last_value)<0)&&((tree_elt(tree_right(tree))-tree_elt(tree))*(tree_elt(tree)-last_value)<0)){
            return false;
        }
        else{
            return (tree_MP_helper(tree_left(tree),tree_elt(tree))||tree_MP_helper(tree_right(tree),tree_elt(tree)));
        }
    }
}

bool tree_allPathSumGreater(tree_t tree, int sum)
// REQUIRES: tree is not empty
//
// EFFECTS: Returns true if and only if for each root-to-leaf
//          path of "tree", the sum of all elements along the path
//          is greater than "sum".
//
//          A root-to-leaf path is a sequence of elements in a tree
//          starting with the root element and proceeding downward
//          to a leaf (an element with no children).
//
// For example, the tree:
//
//                           4
//                         /   \
//                        /     \
//                       1       5
//                      / \     / \
//                     3   6
//                    / \ / \
//
// has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
// Given sum = 9, the path 4->5 has the sum 9, so the function
// should return false. If sum = 7, since all paths have the sums
// greater than 7, the function should return true.
{
    if (tree_isEmpty(tree)){
        return true;
    }
    else if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))){
        if((sum-tree_elt(tree))<0){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return (tree_allPathSumGreater(tree_left(tree), sum-tree_elt(tree))&&tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree)));
    }
}

bool covered_by(tree_t A, tree_t B)
// EFFECTS: Returns true if tree A is covered by tree B.
{
    if (tree_isEmpty(A)){
        return true;
    }
    else if (tree_isEmpty(B)){
        return false;
    }
    else if (tree_elt(A)!=tree_elt(B)){
        return false;
    }
    else{
        return (covered_by(tree_left(A),tree_left(B))&&covered_by(tree_right(A),tree_right(B)));
    }
}

bool contained_by(tree_t A, tree_t B)
// EFFECTS: Returns true if tree A is covered by tree B
//          or a subtree of B.
{
    if(covered_by(A,B)){
        return true;
    }
    else if(tree_isEmpty(B)){
        return false;
    }
    else{
        return (contained_by(A, tree_left(B))||contained_by(A, tree_right(B)));
    }
}

tree_t insert_tree(int elt, tree_t tree)
// REQUIRES: "tree" is a sorted binary tree.
//
// EFFECTS: Returns a new tree with elt inserted at a leaf such that
//          the resulting tree is also a sorted binary tree.
//
// For example, inserting 1 into the tree:
//
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                         3
//                        / \
//
// would yield
//                           4
//                         /   \
//                        /      \
//                       2        5
//                      / \      / \
//                     1   3
//                    / \ / \
//
{
    if (tree_isEmpty(tree)){
        return tree_make(elt,tree_make(),tree_make());
    }
    else if (tree_elt(tree)<=elt){
        return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt,tree_right(tree)));
    }
    else {
        return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)),tree_right(tree));
    }
}
