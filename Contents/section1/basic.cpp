/*
====================================== LIMITS ======================================
[Type]                  [size]          [max val]               [min val]
char                    1               127                     -128
signed char             1               127                     -128
unsigned char           1               255
short                   2               32767                   -32768
int                     4               2147483647              -2147483648
unsigned int            4               4294967295
long                    4               2147483647              -2147483648
unsigned long           4               18446744073709551615
long long               8               9223372036854775807     -9223372036854775808
double                  8               1.79769e+308            2.22507e-308
long double             16              1.18973e+4932           3.3621e-4932
float                   4               3.40282e+38             1.17549e-38
unsigned long long      8               18446744073709551615
string                  32
=============================== Printable characters ===============================
int     char    int     char    int     char    int     char    int     char
32              51      3       70      F       89      Y       108     l
33      !       52      4       71      G       90      Z       109     m
34      "       53      5       72      H       91      [       110     n
35      #       54      6       73      I       92      \       111     o
36      $       55      7       74      J       93      ]       112     p
37      %       56      8       75      K       94      ^       113     q
38      &       57      9       76      L       95      _       114     r
39      '       58      :       77      M       96      `       115     s
40      (       59      ;       78      N       97      a       116     t
41      )       60      <       79      O       98      b       117     u
42      *       61      =       80      P       99      c       118     v
43      +       62      >       81      Q       100     d       119     w
44      ,       63      ?       82      R       101     e       120     x
45      -       64      @       83      S       102     f       121     y
46      .       65      A       84      T       103     g       122     z
47      /       66      B       85      U       104     h       123     {
48      0       67      C       86      V       105     i       124     |
49      1       68      D       87      W       106     j       125     }
50      2       69      E       88      X       107     k       126     ~
====================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class ListProblem {
    vector<int> nums={};
public:
    void solve() {
        return;
    }

    ListNode* buildList(int idx) {
        if(idx == nums.size()) return NULL;
        ListNode *current=new ListNode(nums[idx++],current->next);
        return current;
    }

    void deleteList(ListNode* root) {
        if(root == NULL) return;
        deleteList(root->next);
        delete root;
        return;
    }
};

class TreeProblem {
    int null = INT_MIN;
    vector<int> nums = {}, result;
public:
    void solve() {

        return;
    }

    TreeNode* buildBinaryTreeUsingDFS(int left, int right) {
        if((left > right) || (nums[(left+right)/2] == null)) return NULL;
        int mid = (left+right)/2;
        TreeNode* current = new TreeNode(
            nums[mid],
            buildBinaryTreeUsingDFS(left,mid-1),
            buildBinaryTreeUsingDFS(mid+1,right));
        return current;
    }

    TreeNode* buildBinaryTreeUsingBFS() {
        int idx = 0;
        TreeNode* root = new TreeNode(nums[idx++]);
        queue<TreeNode*> q;
        q.push(root);
        while(idx < nums.size()) {
            if(nums[idx] != null) {
                TreeNode* left = new TreeNode(nums[idx]);
                q.front()->left = left;
                q.push(left);
            }
            idx++;
            if((idx < nums.size()) && (nums[idx] != null)) {
                TreeNode* right = new TreeNode(nums[idx]);
                q.front()->right = right;
                q.push(right);
            }
            idx++;
            q.pop();
        }
        return root;
    }

    Node* buildNAryTree() {
        int idx = 2;
        Node *root = new Node(nums.front());
        queue<Node*> q;
        q.push(root);
        while(idx < nums.size()) {
            while((idx < nums.size()) && (nums[idx] != null)) {
                Node *current = new Node(nums[idx++]);
                q.front()->children.push_back(current);
                q.push(current);
            }
            idx++;
            q.pop();
        }
        return root;
    }

    void deleteBinaryTree(TreeNode* root) {
        if(root->left != NULL) deleteBinaryTree(root->left);
        if(root->right != NULL) deleteBinaryTree(root->right);
        delete root;
        return;
    }

    void deleteNAryTree(Node* root) {
        if(root == NULL) return;
        for(int i=0; i<root->children.size(); i++) {
            deleteNAryTree(root->children[i]);
            delete root->children[i];
        }
        delete root;
        return;
    }

    void inorderTraversal(TreeNode* root) {
        if(root == NULL) return;
        inorderTraversal(root->left);
        cout<<root->val<<' ';
        inorderTraversal(root->right);
        return;
    }
};

int main() {

    return 0;
}
