const int maxc = 26;        // 單字字符數
const char minc = 'a';      // 首個 ASCII

struct TrieNode {
  bool isWord;
  TrieNode* child[maxc];

  TrieNode() {
    isWord = false;
    for(auto& node : child) {
      node = nullptr;
    }
  }
};

struct Trie {
  TrieNode* root;
  
  Trie() { root = new TrieNode(); }
  
  void insert(string word) {
    TrieNode* cur = root;
    for(auto& ch : word) {
      int c = ch - minc;
      if(!cur->child[c])
        cur->child[c] = new TrieNode();
      cur = cur->child[c];
    }
    cur->isWord = true;
  }
  
  // 字典裡有出現 word
  bool search(string word, bool prefix=0) {
    TrieNode* cur = root;
    for(auto& ch : word) {
      int c = ch - minc;
      if(!(cur=cur->child[c])) return false;
    }
    return cur->isWord || prefix;
  }
  
  // 字典裡有 word 的前綴為 prefix
  bool startsWith(string prefix) {
    return search(prefix, true);
  }
};