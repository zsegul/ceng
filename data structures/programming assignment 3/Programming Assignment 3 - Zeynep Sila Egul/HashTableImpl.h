#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

//=======================//
// Implemented Functions //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::PRIMES[3] = {102523, 100907, 104659};

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintLine(int tableIndex) const
{
    const HashData& data = table[tableIndex];

    // Using printf here it is easier to format
    if(data.sentinel == SENTINEL_MARK)
    {
        printf("[%03d]         : SENTINEL\n", tableIndex);
    }
    else if(data.sentinel == EMPTY_MARK)
    {
        printf("[%03d]         : EMPTY\n", tableIndex);
    }
    else
    {
        printf("[%03d] - [%03d] : ", tableIndex, data.lruCounter);
        printf("(%-5s) ", data.isCostWeighted ? "True" : "False");
        size_t sz = data.intArray.size();
        for(size_t i = 0; i < sz; i++)
        {
            if(i % 2 == 0)
                printf("[%03d]", data.intArray[i]);
            else
                printf("/%03d/", data.intArray[i]);

            if(i != sz - 1)
                printf("-->");
        }
        printf("\n");
    }
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintTable() const
{
    printf("____________________\n");
    printf("Elements %d\n", elementCount);
    printf("[IDX] - [LRU] | DATA\n");
    printf("____________________\n");
    for(int i = 0; i < MAX_SIZE; i++)
    {
        PrintLine(i);
    }
}

//=======================//
//          TODO         //
//=======================//
template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Hash(int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    
    int primesProduct = 0;
    if (isCostWeighted == true) {
        primesProduct = PRIMES[0] * startInt + PRIMES[1] * endInt + PRIMES[2];
    } else {
        primesProduct = PRIMES[0] * startInt + PRIMES[1] * endInt;
    }
    
    return primesProduct;
}

template<int MAX_SIZE>
HashTable<MAX_SIZE>::HashTable()
{
    /* TODO */
    elementCount = 0;
    
    for (int i = 0; i < MAX_SIZE; ++i) {
        table[i].sentinel = EMPTY_MARK;
        table[i].lruCounter = 0;
    }
}

template<int MAX_SIZE>
int HashTable<MAX_SIZE>::Insert(const std::vector<int>& intArray, bool isCostWeighted)
{
    /* TODO */
    if(intArray.empty()) throw InvalidTableArgException();
    
    int ind = (Hash(intArray.front(), intArray.back(), isCostWeighted)) % MAX_SIZE;
    int probe = 1, lru = 0, emptySlot = -1;

    while (probe <= MAX_SIZE) {
        if (table[ind].sentinel != OCCUPIED_MARK) {
            if (emptySlot == -1) emptySlot = ind; 
            break;
        }

        if (table[ind].startInt == intArray.front() && table[ind].endInt == intArray.back() &&
            table[ind].isCostWeighted == isCostWeighted) {
            table[ind].lruCounter++;
            return table[ind].lruCounter;
        }

        ind = (ind + probe * probe) % MAX_SIZE;
        probe++;
    }

    if(elementCount > MAX_SIZE/2) throw TableCapFullException(elementCount);
    
    if (emptySlot != -1) ind = emptySlot; 

    if (table[ind].sentinel == OCCUPIED_MARK) {
        lru = table[ind].lruCounter;
    } else {
        elementCount++;
    }

    table[ind].intArray = intArray;
    table[ind].isCostWeighted = isCostWeighted;
    table[ind].startInt = intArray.front();
    table[ind].endInt = intArray.back();
    table[ind].sentinel = OCCUPIED_MARK;
    table[ind].lruCounter++;

    return lru;
}

template<int MAX_SIZE>
bool HashTable<MAX_SIZE>::Find(std::vector<int>& intArray,
                               int startInt, int endInt, bool isCostWeighted,
                               bool incLRU)
{
    /* TODO */
    int ind = Hash(startInt, endInt, isCostWeighted) % MAX_SIZE;
    int probe = 1;
    
    while (table[ind].sentinel != EMPTY_MARK) {
        if (table[ind].startInt == startInt && table[ind].endInt == endInt && table[ind].isCostWeighted == isCostWeighted) {
            if (incLRU == true) {
                table[ind].lruCounter++;
            }
            intArray = table[ind].intArray;
            return true;
        }

        ind = (ind + probe * probe) % MAX_SIZE;
        probe++;
    }
    
    return false;
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::InvalidateTable()
{
    /* TODO */
    for (int i = 0; i < MAX_SIZE; ++i) {
        if (table[i].sentinel == OCCUPIED_MARK) {
                table[i].intArray.clear();
                table[i].sentinel = EMPTY_MARK;
                table[i].lruCounter = 0;
        }
    }
    elementCount = 0; 
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::GetMostInserted(std::vector<int>& intArray) const
{
    /* TODO */
    int ind = -1;
    int maxLru = -1;
    
    for(int i = 0; i<MAX_SIZE; i++){
        if(table[i].sentinel == OCCUPIED_MARK) {
            if(table[i].lruCounter > maxLru){
                maxLru = table[i].lruCounter;
                ind = i;
            }
        }
    }
    
    if(maxLru == -1) intArray.clear();
    else intArray = table[ind].intArray; 
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::Remove(std::vector<int>& intArray,
                                 int startInt, int endInt, bool isCostWeighted)
{
    /* TODO */
    int ind = Hash(startInt, endInt, isCostWeighted) % MAX_SIZE;
    int probe = 1;
    
     while (table[ind].sentinel != EMPTY_MARK) {
        if (table[ind].startInt == startInt && table[ind].endInt == endInt && table[ind].isCostWeighted == isCostWeighted) {
            intArray = table[ind].intArray;
            table[ind].sentinel = SENTINEL_MARK;
            elementCount--;
            return;
        }

        ind = (ind + probe * probe) % MAX_SIZE;
        probe++;
    } 
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::RemoveLRU(int lruElementCount)
{
    /* TODO */
    MinPairHeap<int, int> pq;

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (table[i].sentinel == OCCUPIED_MARK) {
            pq.push({table[i].lruCounter, i});
        }
    }

    while (lruElementCount > 0 && !pq.empty()) {
        int indexToRemove = pq.top().value;
        pq.pop();

        if (table[indexToRemove].sentinel == OCCUPIED_MARK) {
            table[indexToRemove].sentinel = SENTINEL_MARK;
            elementCount--;
        }

        lruElementCount--;
    }  
}

template<int MAX_SIZE>
void HashTable<MAX_SIZE>::PrintSortedLRUEntries() const
{
    /* TODO */
    MaxPairHeap<int, int> pq;

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (table[i].sentinel == OCCUPIED_MARK && table[i].lruCounter > 0) {
            pq.push({table[i].lruCounter, i});
        }
    }

    while (!pq.empty()) {
        int index = pq.top().value;
        PrintLine(index); 
        pq.pop();
    } 
}

#endif // HASH_TABLE_HPP