#pragma once

#include <iostream>
class word {
    std::string actualword;
    int count;
    int status;
public:
    word() {
        actualword = "EMPTY";
        count = 0;
        status = 0;
    }

    word(std::string s) {
        actualword = s;
        count = 1;
        status = 1;
    }

    std::string returnword() {
        return actualword;
    }

    int returncount() {
        return count;
    }

    void increment_count() {
        count++;
    }
    int getstatus() {
        return status;
    }
    void word_delete() {
        status = -1;
    }
};


class MyHash {
private:
    word* HTable;
    int length;
    int hashSize;
    word* countarray;
public:
    MyHash(int size) {
        if (size <= 0) {
            std::cout << "please enter a valid size" << std::endl;
        }
        else {
            HTable = new word[size];
            length = 0;
            hashSize = size;
            countarray = new word[30000];
        }

    }

    int hashTheWord(std::string w) {
        int sum = 0;
        for (int i = 0; i < w.size(); i++) {
            sum += (int)w[i];
        }
        return sum % hashSize;
    }

    void insert(std::string s) {
        int x = 1;
        int a = 0;
        int hashIndex = hashTheWord(s);
        word item(s);
        if (length == hashSize) {
            std::cout << "array is full" << std::endl;
        }
        else {
            while (HTable[hashIndex].getstatus() == 1 && HTable[hashIndex].returnword() != item.returnword() && a < 2 *hashSize/3) {
                a++;
                hashIndex = (hashIndex + x * x) % hashSize;
                x++;
            }
            if (HTable[hashIndex].getstatus() != 1) {
                HTable[hashIndex] = item;
                length++;
            }
            else if (HTable[hashIndex].returnword() == item.returnword())
                HTable[hashIndex].increment_count();
        }

    }

    void print() {

        for (int i = 0; i < hashSize; i++) {

            if (HTable[i].getstatus() == 1) {
                std::cout << "word:" << HTable[i].returnword() << " " << "count:" << HTable[i].returncount() << " , " << "index:" << i << std::endl;

            }
        }
      
    }

    void remove(std::string s) {
        int hashIndex = hashTheWord(s);
        int x = 1;
        int a = 0;
        while (HTable[hashIndex].getstatus() != 0 && HTable[hashIndex].returnword() != s&&a<2*hashSize/3) {
            a++;
            hashIndex = (hashIndex + x * x) % hashSize;
            x++;
        }
        if (HTable[hashIndex].getstatus() == 1 && HTable[hashIndex].returnword() == s) {
            hashIndex = hashIndex;
            HTable[hashIndex].word_delete();
            length--;
        }
       
    }

    int getlength() {
        return length;
    }
    int getsize() {
        return hashSize;
    }
 
    void arraysort() {
        for (int i = 0; i < hashSize; i++) {
            int index;
            if (HTable[i].getstatus() == 1) {
                index = HTable[i].returncount();
                countarray[index] = HTable[i];
            }
        }
    }

    void printtopten() {
        int i = 30000;
        int x = 0;
        while (x < 10) {
            if (countarray[i - 1].getstatus() == 1) {
                std::cout << countarray[i - 1].returnword() << " " << countarray[i - 1].returncount() << std::endl;
                x++;
            }
            i--;
        }
    }

    ~MyHash() {
        delete[] HTable;
        delete[] countarray;
    }


};




