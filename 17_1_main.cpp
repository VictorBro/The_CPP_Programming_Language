#include <iostream>
#include "17_1_sha256.h"
 
using std::string;
using std::cout;
using std::endl;
 
int main(int argc, char *argv[])
{
    string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string cyphertext = "b3fee038469792aaa0110e023c530bb5981b3236b95aa31503b7e18360a8b84e";
    string plaintext = "h9Sm6vDzFvlGlxRP";
    
    //sha256(ABCD+fa7QoweGTJP31lOO) == 49ef3f7f7b836896fecab4152d4e84480fa0ae4075ca2e469b0a945b26716a11 (ABCD can only contain ascii leters and digits)
    for (char ch1 : alphabet)
        for (char ch2 : alphabet)
            for (char ch3 : alphabet)
                for (char ch4 : alphabet)
                {
                    string input = string(1, ch1) + string(1, ch2) + string(1, ch3) + string(1, ch4) + plaintext;
                    string output1 = sha256(input);
                    if (output1 == cyphertext) {
                        cout << "sha256('"<< input << "'):" << output1 << endl;
                        return 0;
                    }
                }
}