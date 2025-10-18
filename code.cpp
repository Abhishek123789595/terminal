#include <bits/stdc++.h>
using namespace std;

// --------------------------------------------------------------
// 1️⃣ STACK & QUEUE
// --------------------------------------------------------------

void stackDemo() {
    stack<int> st;
    st.push(10); st.push(20); st.push(30);
    cout << "Stack top: " << st.top() << "\n";
    st.pop();
    cout << "After pop, top: " << st.top() << "\n";
}

void queueDemo() {
    queue<string> q;
    q.push("A"); q.push("B"); q.push("C");
    cout << "Queue front: " << q.front() << "\n";
    q.pop();
    cout << "After dequeue, front: " << q.front() << "\n";
}

// --------------------------------------------------------------
// 2️⃣ LINKED LIST
// --------------------------------------------------------------

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }
    void display() {
        Node* cur = head;
        while (cur) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << "\n";
    }
};

// --------------------------------------------------------------
// 3️⃣ BINARY SEARCH TREE
// --------------------------------------------------------------

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BST {
    TreeNode* root;
    TreeNode* insertRec(TreeNode* node, int val) {
        if (!node) return new TreeNode(val);
        if (val < node->val) node->left = insertRec(node->left, val);
        else if (val > node->val) node->right = insertRec(node->right, val);
        return node;
    }
    void inorderRec(TreeNode* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->val << " ";
        inorderRec(node->right);
    }
    bool searchRec(TreeNode* node, int val) {
        if (!node) return false;
        if (node->val == val) return true;
        return val < node->val ? searchRec(node->left, val) : searchRec(node->right, val);
    }
public:
    BST() : root(nullptr) {}
    void insert(int val) { root = insertRec(root, val); }
    void inorder() { inorderRec(root); cout << "\n"; }
    bool search(int val) { return searchRec(root, val); }
};

// --------------------------------------------------------------
// 4️⃣ GRAPH (BFS, DFS, Dijkstra)
// --------------------------------------------------------------

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj;
public:
    void addEdge(string u, string v, int w = 1) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void bfs(string start) {
        queue<string> q;
        unordered_set<string> vis;
        q.push(start);
        vis.insert(start);
        cout << "BFS: ";
        while (!q.empty()) {
            string node = q.front(); q.pop();
            cout << node << " ";
            for (auto& [nbr, w] : adj[node]) {
                if (!vis.count(nbr)) {
                    vis.insert(nbr);
                    q.push(nbr);
                }
            }
        }
        cout << "\n";
    }

    void dfsHelper(string node, unordered_set<string>& vis) {
        vis.insert(node);
        cout << node << " ";
        for (auto& [nbr, w] : adj[node]) {
            if (!vis.count(nbr)) dfsHelper(nbr, vis);
        }
    }

    void dfs(string start) {
        unordered_set<string> vis;
        cout << "DFS: ";
        dfsHelper(start, vis);
        cout << "\n";
    }

    void dijkstra(string start) {
        unordered_map<string, int> dist;
        for (auto& p : adj) dist[p.first] = INT_MAX;
        dist[start] = 0;
        using pii = pair<int, string>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "Dijkstra (" << start << "):\n";
        for (auto& [node, d] : dist)
            cout << "  " << node << ": " << d << "\n";
    }
};

// --------------------------------------------------------------
// 5️⃣ SORTING
// --------------------------------------------------------------

void bubbleSort(vector<int>& a) {
    for (int i = 0; i < a.size() - 1; i++)
        for (int j = 0; j < a.size() - i - 1; j++)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void quickSort(vector<int>& a, int low, int high) {
    if (low >= high) return;
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    int p = i + 1;
    quickSort(a, low, p - 1);
    quickSort(a, p + 1, high);
}

vector<int> mergeSort(vector<int> arr) {
    if (arr.size() <= 1) return arr;
    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    left = mergeSort(left);
    right = mergeSort(right);
    vector<int> result;
    merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result));
    return result;
}

// --------------------------------------------------------------
// 6️⃣ SEARCHING
// --------------------------------------------------------------

int linearSearch(vector<int>& a, int target) {
    for (int i = 0; i < a.size(); i++)
        if (a[i] == target) return i;
    return -1;
}

int binarySearch(vector<int>& a, int target) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == target) return m;
        else if (a[m] < target) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// --------------------------------------------------------------
// 7️⃣ DYNAMIC PROGRAMMING
// --------------------------------------------------------------

int fibonacci(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fibonacci(n - 1, memo) + fibonacci(n - 2, memo);
}

int knapsack(vector<int>& wt, vector<int>& val, int W, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// --------------------------------------------------------------
// 8️⃣ MAIN DEMO
// --------------------------------------------------------------

int main() {
    cout << "=== STACK & QUEUE ===\n";
    stackDemo();
    queueDemo();

    cout << "\n=== LINKED LIST ===\n";
    LinkedList ll;
    ll.append(10); ll.append(20); ll.append(30);
    ll.display();

    cout << "\n=== BST ===\n";
    BST bst;
    for (int v : {8, 3, 10, 1, 6, 14, 4, 7, 13}) bst.insert(v);
    bst.inorder();
    cout << "Search 7: " << (bst.search(7) ? "Found" : "Not Found") << "\n";

    cout << "\n=== GRAPH ===\n";
    Graph g;
    g.addEdge("A", "B", 4);
    g.addEdge("A", "C", 2);
    g.addEdge("B", "D", 10);
    g.addEdge("C", "D", 3);
    g.bfs("A");
    g.dfs("A");
    g.dijkstra("A");

    cout << "\n=== SORTING ===\n";
    vector<int> arr = {10, 3, 5, 2, 8, 1};
    vector<int> arr2 = arr;
    bubbleSort(arr);
    cout << "Bubble: "; for (int x : arr) cout << x << " "; cout << "\n";
    quickSort(arr2, 0, arr2.size() - 1);
    cout << "Quick: "; for (int x : arr2) cout << x << " "; cout << "\n";
    auto ms = mergeSort(arr);
    cout << "Merge: "; for (int x : ms) cout << x << " "; cout << "\n";

    cout << "\n=== SEARCHING ===\n";
    int target = 5;
    cout << "Linear: " << linearSearch(arr, target) << "\n";
    cout << "Binary: " << binarySearch(arr, target) << "\n";

    cout << "\n=== DYNAMIC PROGRAMMING ===\n";
    vector<int> memo(20, -1);
    cout << "Fibonacci(10): " << fibonacci(10, memo) << "\n";
    vector<int> wt = {2, 3, 4, 5};
    vector<int> val = {3, 4, 5, 6};
    cout << "Knapsack(5): " << knapsack(wt, val, 5, wt.size()) << "\n";

    return 0;
}
