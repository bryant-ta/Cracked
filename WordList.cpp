#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <iostream>
#include <fstream>
using namespace std;

class WordListImpl
{
public:
    ~WordListImpl()
    {
        delete m_wordList;
        delete m_byPattern;
        m_wordList = nullptr;
        m_byPattern = nullptr;
    };
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<string, string>* m_wordList = nullptr;
    MyHash<string, vector<string>>* m_byPattern = nullptr;
    
    string letterPattern(string word) const;
};

bool WordListImpl::loadWordList(string filename)
{
    delete m_wordList;
    m_wordList = new MyHash<string, string>;
    
    delete m_byPattern;
    m_byPattern = new MyHash<string, vector<string>>;
    
    ifstream infile(filename);
    if (!infile)        {return false;}     // Failed to open file
    
    string s;
    bool invalidWord = false;
    while (getline(infile, s))
    {
        invalidWord = false;
        for (int i = 0; i < s.size(); i++)      // Where i does not exceed "some constant"
        {
            if (!isalpha(s[i]) && s[i] != '\'') // Only take lines with all letters/apostrophe
            {
                infile.ignore(10000, '\n');
                invalidWord = true;
                break;
            }
        }
        
        if (invalidWord)
            continue;
        
        // Hashing by word
        for (int i=0; i<s.size(); i++)
        {
            if (isalpha(s[i]))
                s[i] = tolower(s[i]);
        }
        m_wordList->associate(s, s);
        
        // Hashing by letter pattern
        vector<string> temp;
        string pattern = letterPattern(s);
        if (m_byPattern->find(pattern) != nullptr)
            temp = *m_byPattern->find(pattern);
        temp.push_back(s);
        m_byPattern->associate(letterPattern(s), temp);
    }
    return true;
}

bool WordListImpl::contains(string word) const
{
    for (int i=0; i<word.size(); i++)
    {
        if (isalpha(word[i]))
            word[i] = tolower(word[i]);
    }
    string* sp = m_wordList->find(word);
    if (sp == nullptr)
        return false;
    string s = *sp;
    for (int i=0; i<s.size(); i++)
    {
        if (isalpha(s[i]))
            s[i] = tolower(s[i]);
    }
    return word == s;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    vector<string> candidates;
    
    // Ensure inputs contain valid characters
    if (cipherWord.size() != currTranslation.size())
        return candidates;
    for (int i = 0; i < cipherWord.size(); i++)
    {
        if (!isalpha(cipherWord[i]) && cipherWord[i] != '\'') // Validate all letters/apostrophe
        {
            return candidates;
            break;
        }
        if (!isalpha(currTranslation[i]) && currTranslation[i] != '\'' && currTranslation[i] != '?') // Validate all letters/apostrophe/question mark
        {
            return candidates;
            break;
        }
        
        // Make all letters lowercase for case-insensitive
        if (isalpha(cipherWord[i]))
            cipherWord[i] = tolower(cipherWord[i]);
        if (isalpha(currTranslation[i]))
            currTranslation[i] = tolower(currTranslation[i]);
    }
    
    // Attempt to find cipherWords fitting currTranslation
    if (m_byPattern->find(letterPattern(cipherWord)) == nullptr)
        return candidates;
    
    bool accepted;
    vector<string> acceptedCandidates;
    candidates = *m_byPattern->find(letterPattern(cipherWord));
    for (int i = 0; i < candidates.size(); i++)
    {
        accepted = true;
        for (int j = 0; j < currTranslation.size(); j++)
        {
            if ((currTranslation[j] == '?' && !isalpha(candidates[i][j]))  ||
                (currTranslation[j] == '\'' && candidates[i][j] != '\'')   ||
                (isalpha(currTranslation[j]) && currTranslation[j] != tolower(candidates[i][j])))
            {
                accepted = false;
                break;
            }
        }
        if (accepted)
            acceptedCandidates.push_back(candidates[i]);
    }
    
    return acceptedCandidates;
}

// Extracting letter pattern
string WordListImpl::letterPattern(string word) const
{
    if (word == "")
        return "";
    int counter = 0;
    string pattern;
    bool matching = false;      // true = a matching letter-number was found
    for (int i = counter; i < word.size(); i++)
    {
        for (int j = 0; j < i; j++)         // Search through previously indexed chars
        {
            if (word[i] == word[j])         // Found matching char, add its id number
            {
                pattern += string(1,pattern[j]);
                matching = true;
                break;
            }
        }
        if (!matching)          // Did not find matching char, add incremented id number
        {
            counter++;
            pattern += to_string(counter);
        }
        matching = false;
    }
    return pattern;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
    return m_impl->findCandidates(cipherWord, currTranslation);
}
