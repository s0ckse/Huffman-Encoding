#include<bits/stdc++.h>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left,*right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();
 
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
 
    return node;
}
bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }
 
    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != "") ? str : "1";
    }
 
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }
 
    // found a leaf node
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}

class Compare
{
public:
    bool operator() (Node* left,Node* right)
    {
        return left->freq>right->freq;
    }
};

void Huffman(string text){
    if(text==""){
        return;
    }

    unordered_map<char, int> freq;
    unordered_map<char, int>::iterator itr;
    for (long i = 0; i < text.length(); i++)
        freq[text[i]]++;

    priority_queue <Node*, vector<Node*>, Compare > pq;
    
    for (auto traverse:freq){
        pq.push(getNode(traverse.first,traverse.second,nullptr,nullptr));
    }
    
    do{
        Node* left= pq.top();
        pq.pop();
        Node* right= pq.top();
        pq.pop();
        int newfreq= left->freq + right->freq;
        pq.push(getNode('\0',newfreq,left,right));

    }while (pq.size()!=1);

    Node* root = pq.top();
    unordered_map<char,string> Huff;
    encode(root,"",Huff);

     cout << "Huffman Codes are:\n" << endl;
    for (auto pair:Huff) {
        cout << pair.first << " " << pair.second << endl;
    }
 
    cout << "\nThe original string is:\n" << text << endl;
 
    string str;
    for (char ch: text) {
        str += Huff[ch];
    }
 
    cout << "\nThe encoded string is:\n" << str << endl;
    cout << "\nThe decoded string is:\n";
 
    if (isLeaf(root))
    {
        // Special case: For input like a, aa, aaa, etc.
        while (root->freq--) {
            cout << root->ch;
        }
    }
    else {
        // Traverse the Huffman Tree again and this time,
        // decode the encoded string
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }
}


int main(){
    string text;
    cout<<"Enter the text to be encoded\n";
    getline(cin, text);
    Huffman(text);
    return 0;
}
