#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    char character;
    unsigned frequency;
    Node* left;
    Node* right;

    Node(char character, unsigned frequency) {
        this->character = character;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

void PrintCodes(Node* root, string code) {
    if (root == nullptr) return;
    if (root->character != '$') cout << root->character << ": " << code << endl;
    PrintCodes(root->left, code + "0");
    PrintCodes(root->right, code + "1");
}

Node* BuildHuffmanTree(char characters[], int frequencies[], int size) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* sum = new Node('$', left->frequency + right->frequency);
        sum->left = left;
        sum->right = right;
        minHeap.push(sum);
    }

    return minHeap.top();
}

int main() {
    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(characters) / sizeof(characters[0]);

    Node* root = BuildHuffmanTree(characters, frequencies, size);

    PrintCodes(root, "");

    return 0;
}
