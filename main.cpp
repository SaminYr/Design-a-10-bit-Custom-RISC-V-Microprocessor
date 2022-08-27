#include<bits/stdc++.h>
using namespace std;

int main()
{
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    vector<string> rtype = {"add", "sub", "and", "or"}, itype = {"addi", "subi"};
    map<string, string> str_to_bin;
    str_to_bin["add"] = "0010";
    str_to_bin["sub"] = "0011";
    str_to_bin["and"] = "0000";
    str_to_bin["or"] = "0001";   
    str_to_bin["addi"] = "0010";
    str_to_bin["subi"] = "0011";
    fprintf(out, "v2.0 raw\n");
    char l[1000];
    int idx = 1;
    while(fgets(l, 100, inp))
    {
        vector<string> op;
        l[strlen(l)-1] = '\0';
        string line(l);
        string field;
        int i;
        for(i=0; i<line.size(); i++)
        {
            if(line[i] == ' ' || line[i] == ',')
            {
                if(field.size()) op.push_back(field);
                field.clear();
                continue;
            }
            field+=line[i];
        }
        if(field.size()) op.push_back(field);
        string bin_op;
        if(find(rtype.begin(), rtype.end(), op[0]) != rtype.end())
        {
            bin_op+=str_to_bin[op[0]];
            bitset<2> b1(stoi(op[1].substr(1, op[1].size())));
            bitset<2> b2(stoi(op[2].substr(1, op[2].size())));
            bin_op+=b2.to_string();
            if (op[0] != "not")
            {
                bitset<2> b3(stoi(op[3].substr(1, op[3].size())));
                bin_op += b3.to_string();
                bin_op += b1.to_string();
            }
            else
            {
                bin_op += b1.to_string();
                bin_op += "00";
            }
        }
        else if(find(itype.begin(), itype.end(), op[0]) != itype.end())
        {
            bin_op+=str_to_bin[op[0]];
            bitset<2> b1(stoi(op[1].substr(1, op[1].size())));
            bitset<2> b2(stoi(op[2].substr(1, op[2].size())));
            bin_op+=b2.to_string();
            bin_op+=b1.to_string();
            bitset<2> b3(stoi(op[3]));
            bin_op+=b3.to_string();
        }
         else
        {
            cout<<"Error"<<endl;
            cin.get();
            exit(1);
        }
        bitset<10> b1(bin_op);
        int int_op = b1.to_ulong();
//        printf("%x\n", int_op);
        fprintf(out,"%x\n", int_op);
    }
    cin.get();
}