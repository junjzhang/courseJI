#include <algorithm>
#include <iostream>

using namespace std;
// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void dfs(TreeNode *root);
void recoverTree(TreeNode *root);
int main() {
  TreeNode a(2), b(4), c(3);
  b.left = &a;
  b.right = &c;
  recoverTree(&b);
  cout << b.val << endl;
}
TreeNode *pre, *a, *b;
void recoverTree(TreeNode *root) {
  TreeNode *first = nullptr, *second = nullptr, *cur = root, *pre = nullptr;
  while (cur) {
    if (cur->left) {
      TreeNode *p = cur->left;
      while (p->right && p->right != cur)
        p = p->right;
      if (!p->right) {
        p->right = cur;
        cur = cur->left;
        continue;
      } else {
        p->right = NULL;
      }
    }
    if (pre && cur->val < pre->val) {
      if (!first)
        first = pre;
      second = cur;
    }
    pre = cur;
    cur = cur->right;
  }
  swap(first->val, second->val);
}