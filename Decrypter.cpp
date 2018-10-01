#include "provided.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class DecrypterImpl
{
public:
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList m_wl;
    Translator m_tr;
    
    void crackHelper(vector<string> &decryptions, vector<string> tokens, string ciphertext, int currIndex);
};

bool DecrypterImpl::load(string filename)
{
    return m_wl.loadWordList(filename);
}

vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    vector<string> decryptions;
    vector<string> tokens;
    
    if (ciphertext != "")
        crackHelper(decryptions, tokens, ciphertext, 0);
    
    sort(decryptions.begin(), decryptions.end());
    
    return decryptions;
}

void DecrypterImpl::crackHelper(vector<string> &decryptions, vector<string> tokens, string ciphertext, int currIndex)
{
    // Step 2
    Tokenizer to(" ,;:.!()[]{}-\"#$%^&");
    tokens = to.tokenize(ciphertext);
    
    // Step 2 & 3
    string decryptedWord = m_tr.getTranslation(tokens[currIndex]);
    
    // Step 4
    vector<string> candidates = m_wl.findCandidates(tokens[currIndex], decryptedWord);
    
    // Step 5
    if (candidates.empty())
    {
        m_tr.popMapping();
        return;
    }
    
    // Step 6
    for (string p : candidates)
    {
        // a - make new mapping
        tokens = to.tokenize(ciphertext);
        
        if (!m_tr.pushMapping(tokens[currIndex], p))
        {
            continue;
        }
        
        // b - translate entire msg with new mapping
        for (int i=0; i<tokens.size(); i++)
        {
            tokens[i] = m_tr.getTranslation(tokens[i]);
        }
        // now tokens holds translated
        
        // c - validate words
        bool allFullyTranslated = true;
        bool validWordsButNotFullyTranslatedFlag = false;
        for (int i=0; i<tokens.size(); i++)
        {
            bool wordFullyTranslated = true;
            for (int j=0; j<tokens[i].size(); j++)
            {
                if (tokens[i][j] == '?')
                {
                    wordFullyTranslated = false;
                    allFullyTranslated = false;
                    break;
                }
            }
            
            if (wordFullyTranslated && !m_wl.contains(tokens[i]))
            {
                m_tr.popMapping();
                validWordsButNotFullyTranslatedFlag = true;
                break;                  // i.
            }
        }
        if (validWordsButNotFullyTranslatedFlag)
            continue;       // i
        
        if (allFullyTranslated)
        {
            decryptions.push_back(m_tr.getTranslation(ciphertext));
            m_tr.popMapping();          // iii.
        }
        else
        {
            crackHelper(decryptions, tokens, ciphertext, currIndex+1);      //ii.
        }
    }
    
    m_tr.popMapping();
    return;
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
    return m_impl->crack(ciphertext);
}

