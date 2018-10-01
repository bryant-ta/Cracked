// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.

const int INITIAL_TABLE_SIZE = 100;

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5) : m_numItems(0), m_size(INITIAL_TABLE_SIZE), m_maxLoadFactor(maxLoadFactor)//, m_resizing(false)
    {
        if (maxLoadFactor <= 0)         m_maxLoadFactor = 0.5;
        else if (maxLoadFactor > 2)     m_maxLoadFactor = 2.0;
        m_hashTable = new Pair*[INITIAL_TABLE_SIZE];
        for (int i = 0; i < INITIAL_TABLE_SIZE; i++)
        {
            m_hashTable[i] = nullptr;
        }
    };
    ~MyHash()
    {
        reset();
        delete [] m_hashTable;
    };
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const         {return m_numItems;};
    double getLoadFactor() const    {return static_cast<double>(m_numItems) / static_cast<double>(m_size);};
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    
private:
    class Pair
    {
    public:
        KeyType p_key;
        ValueType p_value;
        Pair* p_next;
    };
    
    Pair** m_hashTable;
    int m_numItems;
    int m_size;
    double m_maxLoadFactor;
    
    void clearHashTable();
};

// Reset m_hashTable (deleting data) to default state with size INITIAL_TABLE_SIZE
template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    for (int i = 0; i < m_size; i++)
    {
        Pair* temp = m_hashTable[i];
        while (temp != nullptr)
        {
            Pair* prev = temp;
            temp = temp->p_next;
            delete prev;
        }
    }
    delete[] m_hashTable;
    m_hashTable = new Pair*[INITIAL_TABLE_SIZE];
    for (int i = 0; i < INITIAL_TABLE_SIZE; i++)
    {
        m_hashTable[i] = nullptr;
    }
    m_size = INITIAL_TABLE_SIZE;
    m_numItems = 0;
    
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType &key, const ValueType &value)
{
    unsigned int hash(const KeyType& k);            // prototype
    unsigned int h = hash(key);
    int index = h % m_size;
    
    // Adding data
    if (m_hashTable[index] == nullptr)  // Nothing there
    {
        m_hashTable[index] = new Pair;
        m_hashTable[index]->p_key = key;
        m_hashTable[index]->p_value = value;
        m_hashTable[index]->p_next = nullptr;
        m_numItems++;
    }
    else                                // A Pair already there
    {
        Pair* temp = m_hashTable[index];
        while (temp->p_next != nullptr)
        {
            if (temp->p_key == key)
                break;
            temp = temp->p_next;
        }
        if (temp->p_key == key)
        {
            temp->p_value = value;
        }
        else
        {
            temp->p_next = new Pair;
            temp->p_next->p_key = key;
            temp->p_next->p_value = value;
            temp->p_next->p_next = nullptr;
        }
        m_numItems++;
    }
    
    // Resizing table
    if (getLoadFactor() > m_maxLoadFactor)
    {
        // Make copy of current m_hashTable
        Pair** copyHashTable = new Pair*[m_size];
        for (int i = 0; i < m_size; i++)
        {
            copyHashTable[i] = nullptr;
        }
        for (int i = 0; i < m_size; i++)
        {
            if (m_hashTable[i] != nullptr)
            {
                copyHashTable[i] = m_hashTable[i];
            }
        }
        
        delete[] m_hashTable;       // Delete m_hashTable
        
        // Allocate new table with twice size
        m_hashTable = new Pair*[m_size*2];
        m_size *= 2;
        m_numItems = 0;
        for (int i = 0; i < m_size; i++)
        {
            m_hashTable[i] = nullptr;
        }
        
        // Rehash all old data from copy
        for (int i = 0; i < m_size/2; i++)
        {
            Pair* temp = copyHashTable[i];
            while(temp != nullptr)
            {
                associate(temp->p_key, temp->p_value);
                temp = temp->p_next;
            }
        }
        
        // Delete copyHashTable
        for (int i = 0; i < m_size/2; i++)
        {
            Pair* temp = copyHashTable[i];
            while (temp != nullptr)
            {
                Pair* prev = temp;
                temp = temp->p_next;
                delete prev;
            }
        }
        delete[] copyHashTable;
    }
}

template<typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    // Determine index of key with hash
    unsigned int hash(const KeyType& k);            // prototype
    unsigned int h = hash(key);
    int index = h % m_size;
    
    // Return pointer to corresponding value
    Pair* temp = m_hashTable[index];
    while(temp != nullptr)
    {
        if (temp->p_key == key)
        {
            return &temp->p_value;
        }
        temp = temp->p_next;
    }
    return nullptr;
}

// Only deletes all data in table(resetting numItems). Retains maxLoadFactor, size
template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::clearHashTable()
{
    for (int i = 0; i < m_size; i++)
    {
        Pair* temp = m_hashTable[i];
        while (temp != nullptr)
        {
            Pair* prev = temp;
            delete prev;
            temp = temp->p_next;
        }
    }
    m_numItems = 0;
}
