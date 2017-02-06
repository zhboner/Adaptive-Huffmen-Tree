#include "basic.cpp"
using namespace std;

string ahencode(string st, bool space){
    string s;

    int index = st.size();
    for (int i = 0; i < st.size(); ++i) {
        char input = st[i];
        index = input + 128;
        if (path[index] == "-1"){       // If the char don't exist
            if (NYT->id == base){        // Tree is empty
                s = bitset<8>(input).to_string();
            }
            else{
                if (space){
                    s.append(" ");
                }
                s.append(path[base]);
                s.append(bitset<8>(input).to_string());
            }

        }
        else{                           // If the char exist
            if (space){
                s.append(" ");
            }
            s.append(path[index]);
        }
        updateTree(input);
        updateId();
    }
    return s;
}

int main(int argc, char *argv[]) {
    availableId = base;
    Node NYTNode = Node(availableId--, 0, NULL, NULL, NULL, '\0');
    string in;
    bool space;

    if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 's'){
        space = true;
    }
    else{
        space = false;
    }

    while (getline(cin, in)){                   // Read a line and call ahencode() to encode.
        for (int k = 0; k < base + 1; ++k) {
            path[k] = "-1";
        }
        NYT = &NYTNode;
        availableId = base;
        root = NYT;

        str = string(in);

        if (str.size() == 0) break;
        string output = ahencode(str, space);
        cout<<output<<endl;
    }
}

