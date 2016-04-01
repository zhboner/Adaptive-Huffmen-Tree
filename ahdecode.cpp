#include "basic.cpp"

using namespace std;

string ahdecode(string st){
    string code, out;
    char input, tmp;
    int i = 0;
    bitset<8> x;
    Node *node = root;

    while (i < st.size()){
        if (NYT->id == base){
            code = st.substr(i, i + 8);

            x = bitset<8>(code);
            input = static_cast<char>(x.to_ulong());
            out += input;
            i += 8;

            updateTree(input);
            updateId();
            node = root;
        }
        else{
            tmp = st[i];

            if (tmp == ' '){
                i++;
                continue;
            }
            // Move one step
            if (tmp == '0'){
                node = node->leftNode;
            }
            else{
                node = node->rightNode;
            }

            // Justify the node
            if (node->isLeaf() && node->weight != 0){           // Leaf node
                out += node->value;

                updateTree(node->value);
                updateId();

                node = root;
                i++;
            }
            else{
                if (node->weight == 0){     // NYT node
                    code = st.substr(i + 1, i + 9);

                    x = bitset<8>(code);
                    input = static_cast<char>(x.to_ulong());
                    out += input;
                    i += 9;

                    node = root;

                    updateTree(input);
                    updateId();
                }
                else{                       // Internal node
                    i++;
                }
            }
        }
    }
    return out;
}

int main() {
    availableId = base;
    Node NYTNode = Node(availableId--, 0, NULL, NULL, NULL, '\0');
    char in[8000];

    while (true){
        for (int k = 0; k < base + 1; ++k) {
            path[k] = "-1";
        }
        NYT = &NYTNode;
        availableId = base;
        root = NYT;

        cin.getline(in, 8000);
        str = string(in);

        if (str.size() == 0) break;

        string output = ahdecode(str);
        cout<<output<<endl;
    }
}
