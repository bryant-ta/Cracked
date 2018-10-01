#include "provided.h"
#include <string>
#include <unordered_map>
using namespace std;

class TranslatorImpl
{
public:
    TranslatorImpl() : m_pushCount(0)
    {
        for (int i=65; i<91; i++)
        {
            currMap[i] = '?';
        }
        mapStack.push_back(currMap);
    };
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    unordered_map<char, char> currMap;
    vector<unordered_map<char, char>> mapStack;
    
    int m_pushCount;
};

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    // Check size equal and function input is all alpha
    if (ciphertext.size() != plaintext.size())
        return false;
    for (int i=0; i<ciphertext.size(); i++)
    {
        if (ciphertext[i] == '\'' && plaintext[i] == '\'')  // Doesn't follow spec?
            continue;
        if (! isalpha(ciphertext[i]) || ! isalpha(plaintext[i]))
            return false;
    }
    
    // Check for duplicate keys/values
    for (int k=0; k<ciphertext.size(); k++)
    {
        if (ciphertext[k] == '\'' && plaintext[k] == '\'')
            continue;
        for (auto x : currMap)
        {
            if ((toupper(ciphertext[k]) == x.first && x.second != '?') || tolower(plaintext[k]) == x.second)
            {
                if ((toupper(ciphertext[k]) == x.first && tolower(plaintext[k]) == x.second))
                {
                    break;
                }
                return false;
            }
        }
    }
    
    // Update map and push current map on stack, ignoring case (always A->c)
    for (int i=0; i<ciphertext.size(); i++)
    {
        if (ciphertext[i] == '\'' && plaintext[i] == '\'')
            continue;
        currMap[toupper(ciphertext[i])] = tolower(plaintext[i]);
    }
    mapStack.push_back(currMap);
    m_pushCount++;
    
    return true;
}

bool TranslatorImpl::popMapping()
{
    if (m_pushCount > 0)
    {
        mapStack.pop_back();
        currMap = mapStack.back();
        m_pushCount--;
        return true;
    }
    return false;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string translation = "";
    for (int i=0; i<ciphertext.size(); i++)
    {
        if (isalpha(ciphertext[i]) && currMap.find(toupper(ciphertext[i])) != currMap.end())
        {
            if (isupper(ciphertext[i]))
                translation += toupper(currMap.find(toupper(ciphertext[i]))->second);
            else
                translation += currMap.find(toupper(ciphertext[i]))->second;
        }
        else if (isalpha(ciphertext[i]))
        {
            translation += '?';
        }
        else
        {
            translation += ciphertext[i];
        }
    }
    
    return translation;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
