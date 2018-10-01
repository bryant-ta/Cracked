#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <string>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

#include "MyHash.h"
#include <cassert>
#include <fstream>

const string WORDLIST_FILE = "/Users/bta/Documents/0_School/CS 32/Project_4/wordlist.txt";

//string encrypt(string plaintext)
//{
//      // Generate a to z
//    char plaintextAlphabet[26+1];
//    iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
//    plaintextAlphabet[26] = '\0';
//
//      // Generate permutation
//    string ciphertextAlphabet(plaintextAlphabet);
//    default_random_engine e((random_device()()));
//    shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);
//
//      // Run translator (opposite to the intended direction)
//    Translator t;
//    t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
//    return t.getTranslation(plaintext);
//}
//
//bool decrypt(string ciphertext)
//{
//    Decrypter d;
//    if ( ! d.load(WORDLIST_FILE))
//    {
//        cout << "Unable to load word list file " << WORDLIST_FILE << endl;
//        return false;
//    }
//    for (const auto& s : d.crack(ciphertext))
//        cout << s << endl;
//    return true;
//}
//
//int main(int argc, char* argv[])
//{
//    if (argc == 3  &&  argv[1][0] == '-')
//    {
//        switch (tolower(argv[1][1]))
//        {
//          case 'e':
//            cout << encrypt(argv[2]) << endl;
//            return 0;
//          case 'd':
//            if (decrypt(argv[2]))
//                return 0;
//            return 1;
//        }
//    }
//
//    cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
//    cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
//    return 1;
//}

#include <vector>

int main()
{
//        MyHash<int, string> a;
//        a.associate(222, "Ethel");
//        a.associate(333, "Lucy");
//        a.associate(111, "Fred");
//
//    cout << a.getNumItems() << endl;
    //    cout << *a.find(250) << endl;
    //    cout << *a.find(2500) << endl;
    //    cout << *a.find(21234123) << endl;
    //    cout << a.getLoadFactor() << endl;
    //    cout << a.getNumItems() << endl;
    //
    //    a.reset();
    //    cout << a.getLoadFactor() << endl;
    //    cout << a.getNumItems() << endl;

    //    Tokenizer t(" ,.!");
    //    vector<string> v = t.tokenize("!");
    //    for (auto it : v)
    //        cout << it << endl;
    //    // v now contains "This", "is", "a", "test", "It's", "the", and "best"
    //    string s = "!!!!!"; v = t.tokenize(s);
    //    // v is now empty

//        WordList wl;
//        wl.loadWordList(WORDLIST_FILE);
//            if(wl.contains("I'm"))
//                cout << "yay" << endl;
//            else
//                cout << "aww" << endl;
//
//        wl.loadWordList(WORDLIST_FILE);
//
//        vector<string> c = wl.findCandidates("CAn't", "???'?");
//        for (auto word : c)
//            cout << word << endl;
//        c = wl.findCandidates("indeed", "??????");
//        for (auto word : c)
//            cout << word << endl;
//        c = wl.findCandidates("aback", "a???k");
//        for (auto word : c)
//            cout << word << endl;

    //    ifstream infile(WORDLIST_FILE);
    //
    //    string s;
    //    int c = 0;
    //    while(getline(infile, s))
    //    {
    //        c++;
    //    }
    //    cout << c << endl;

//    Translator t;
//    cout << t.getTranslation("gpph") << endl;
//    t.pushMapping("aBc", "zxC");
//    t.pushMapping("u", "I");
//    t.pushMapping("Q", "q");
//    t.pushMapping("Gpph", "good");
//    t.pushMapping("Gnmo", "gnmd");
//
//    cout << t.getTranslation("gnm") << endl;
//    t.popMapping();
//    cout << t.getTranslation("gpph") << endl;
//    cout << t.getTranslation("Uiotrq") << endl;
//    t.popMapping();
//    cout << t.getTranslation("uiotrQ") << endl;

    Decrypter d;
    cout << d.load(WORDLIST_FILE) << endl;

//    vector<string> ans = d.crack("G lbbm qfbbm GLMBBM!");
//    vector<string> ans = d.crack("yun't");
//    vector<string> ans = d.crack("y qook ra bdttook yqkook.");

//    vector<string> ans = d.crack("Trcy oyc koon oz rweelycbb vmobcb, wyogrcn oecyb; hjg ozgcy tc moox bo moya wg grc vmobck koon grwg tc ko yog bcc grc oyc trlvr rwb hccy oecyck zon jb. -Rcmcy Xcmmcn");
//    vector<string> ans = d.crack("");
//    vector<string> ans = d.crack("Jxwpjq qwrla glcu pcx qcn xkvv dw uclw ekarbbckpjwe dq jzw jzkpta jzrj qcn ekep\'j ec jzrp dq jzw cpwa qcn eke ec. -Urls Jxrkp");
//    vector<string> ans = d.crack("Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. -Lzjk Nqkkqcy");
//    vector<string> ans = d.crack("Axevfvu lvnelvp bxqp mvpprjv rgl bvoop Grnxvgkvuj dqupb jvbp buvrbvl be lqggvu.");
//    vector<string> ans = d.crack("smxsdg SGOSDG gfvgx!!");

    vector<string> ans = d.crack("abc abc");
    
    cout << ans.size() << endl;
    for (auto s : ans)
        cout << s << endl;
}



















