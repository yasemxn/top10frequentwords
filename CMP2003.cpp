#include <fstream>
#include "hash.h"
#include <ctime>
int main() {
    clock_t start = clock();

    double duration;
    std::string s;
    std::string stpwords;
    std::ifstream stopfile;
    stopfile.open("stopwords.txt");
    std::string stopwordsarray[571];
    for (int i = 0; i < 571; i++) {
        stopfile >> stopwordsarray[i];
    }
   
    size_t firstocurrance;
    size_t secondoccurance;
    size_t thirdoccurance;
    size_t fourthoccurance;
    MyHash hashT(100000);
    stopfile.close();
    bool betweenbody = false;
    std::string array[22] = { "reut2-000.sgm", "reut2-001.sgm", "reut2-002.sgm", "reut2-003.sgm", "reut2-004.sgm", "reut2-005.sgm", "reut2-006.sgm", "reut2-007.sgm",
                              "reut2-008.sgm", "reut2-009.sgm", "reut2-010.sgm", "reut2-011.sgm", "reut2-012.sgm", "reut2-013.sgm", "reut2-014.sgm", "reut2-015.sgm",
                              "reut2-016.sgm", "reut2-017.sgm", "reut2-018.sgm", "reut2-019.sgm", "reut2-020.sgm", "reut2-021.sgm" };

    for (int i = 0; i < 22; i++) {
        std::ifstream fileread;
        fileread.open(array[i]);
        while (fileread >> s) {
            if (s.find("<BODY>") != std::string::npos) {
                s.erase(0, 17);
                betweenbody = true;
            }
            else if (s.find("</BODY>") != std::string::npos) {
                betweenbody = false;
            }
            if (betweenbody) {
                while ((s.back() <= 64 || (s.back() >= 91 && s.back() <= 96) || s.back() >= 123) && s.size() > 1) {

                    s.erase(s.size() - 1);

                }
                while ((s.front() <= 64 || (s.front() >= 91 && s.front() <= 96) || s.front() >= 123) && s.size() > 1) {
                    s.erase(0, 1);
                }
                if (s[0] > '@' && s.size() > 1) {
                    if ((s.find("-") != std::string::npos || s.find("/") != std::string::npos) && s.find("...") == std::string::npos) {
                        int num = 0;

                        for (size_t j = 0; j < s.size(); j++) {
                            if (s[j] == '-' || s[j] == '/') {
                                s[j] = '#';
                                num++;
                            }
                        }
                        if (num == 1) {
                            firstocurrance = s.find("#");
                            std::string first = s.substr(0, firstocurrance);
                            std::string second = s.substr(firstocurrance + 1);

                            for (size_t i = 0; i < first.size(); i++) {
                                first[i] = tolower(first[i]);
                            }
                            hashT.insert(first);
                            for (size_t i = 0; i < second.size(); i++) {
                                second[i] = tolower(second[i]);
                            }
                            if ((second[0] >= 'A' && second[0] <= 'Z') || (second[0] >= 'a' && second[0] <= 'z')) {
                                hashT.insert(second);
                            }
                        }
                        else if (num == 2) {
                            firstocurrance = s.find("#");
                            std::string first = s.substr(0, firstocurrance);
                            std::string second = s.substr(firstocurrance + 1);
                            secondoccurance = second.find("#");
                            second = s.substr(firstocurrance + 1, secondoccurance);
                            std::string third = s.substr(firstocurrance + secondoccurance + 2);

                            for (size_t i = 0; i < first.size(); i++) {
                                first[i] = tolower(first[i]);
                            }
                            hashT.insert(first);
                            if ((second[0] >= 'A' && second[0] <= 'Z') || (second[0] >= 'a' && second[0] <= 'z')) {
                                for (size_t i = 0; i < second.size(); i++) {
                                    second[i] = tolower(second[i]);
                                }
                                hashT.insert(second);
                            }
                            if ((third[0] >= 'A' && third[0] <= 'Z') || (third[0] >= 'a' && third[0] <= 'z')) {
                                for (size_t i = 0; i < third.size(); i++) {
                                    third[i] = tolower(third[i]);
                                }
                                hashT.insert(third);
                            }


                        }
                        else if (num == 3) {
                            firstocurrance = s.find("#");
                            std::string first = s.substr(0, firstocurrance);
                            std::string middle = s.substr(firstocurrance + 1);
                            secondoccurance = middle.find("#");
                            std::string secondword = s.substr(firstocurrance + 1, secondoccurance);
                            std::string last = s.substr(firstocurrance + secondoccurance + 2);
                            thirdoccurance = last.find("#");
                            std::string thirdword = last.substr(0, thirdoccurance);
                            std::string finalword = last.substr(thirdoccurance + 1);

                            hashT.insert(first);
                            if ((secondword[0] >= 'A' && secondword[0] <= 'Z') || (secondword[0] >= 'a' && secondword[0] <= 'z')) {
                                for (size_t i = 0; i < secondword.size(); i++) {
                                    secondword[i] = tolower(secondword[i]);
                                }
                                hashT.insert(secondword);
                            }
                            if ((thirdword[0] >= 'A' && thirdword[0] <= 'Z') || (thirdword[0] >= 'a' && thirdword[0] <= 'z')) {
                                for (size_t i = 0; i < thirdword.size(); i++) {
                                    thirdword[i] = tolower(thirdword[i]);
                                }
                                hashT.insert(thirdword);
                            }
                            if ((finalword[0] >= 'A' && finalword[0] <= 'Z') || (finalword[0] >= 'a' && finalword[0] <= 'z')) {
                                for (size_t i = 0; i < finalword.size(); i++) {
                                    finalword[i] = tolower(finalword[i]);
                                    
                                }
                                hashT.insert(finalword);
                            }

                        }
                        else if (num == 4) {
                            firstocurrance = s.find("#");
                            std::string first = s.substr(0, firstocurrance);
                            std::string middle = s.substr(firstocurrance + 1);
                            secondoccurance = middle.find("#");
                            std::string secondword = s.substr(firstocurrance + 1, secondoccurance);
                            std::string last = s.substr(firstocurrance + secondoccurance + 2);
                            thirdoccurance = last.find("#");
                            std::string thirdword = last.substr(0, thirdoccurance);
                            std::string finalsub = last.substr(thirdoccurance + 1);
                            fourthoccurance = finalsub.find("#");
                            std::string fourthword = finalsub.substr(0, fourthoccurance);
                            std::string fifthword = finalsub.substr(fourthoccurance + 1);
                            hashT.insert(first);
                            if ((secondword[0] >= 'A' && secondword[0] <= 'Z') || (secondword[0] >= 'a' && secondword[0] <= 'z')) {
                                for (size_t i = 0; i < secondword.size(); i++) {
                                    secondword[i] = tolower(secondword[i]);
                                }
                                hashT.insert(secondword);
                            }
                            if ((thirdword[0] >= 'A' && thirdword[0] <= 'Z') || (thirdword[0] >= 'a' && thirdword[0] <= 'z')) {
                                for (size_t i = 0; i < thirdword.size(); i++) {
                                    thirdword[i] = tolower(thirdword[i]);
                                }
                                hashT.insert(thirdword);
                            }
                            if ((fourthword[0] >= 'A' && fourthword[0] <= 'Z') || (fourthword[0] >= 'a' && fourthword[0] <= 'z')) {
                                for (size_t i = 0; i < fourthword.size(); i++) {
                                    fourthword[i] = tolower(fourthword[i]);
                                    
                                }
                                hashT.insert(fourthword);
                            }
                        }
                    }
                    else if (s.find("...") != std::string::npos) {

                        firstocurrance = s.find("...");
                        std::string first = s.substr(0, firstocurrance);
                        std::string second = s.substr(firstocurrance + 3);

                        for (size_t i = 0; i < first.size(); i++) {
                            first[i] = tolower(first[i]);
                        }

                        hashT.insert(first);
                        for (size_t i = 0; i < second.size(); i++) {
                            second[i] = tolower(second[i]);
                        }

                        if (second[0] >= 97 && second[0] <= 122) {
                            hashT.insert(second);

                        }

                    }
                    else if (s.find("#") == std::string::npos && s.find(".") == std::string::npos) {
                        for (size_t i = 0; i < s.size(); i++) {
                            s[i] = tolower(s[i]);
                        }
                        hashT.insert(s);

                    }

                }

            }
        }
        fileread.close();
    }
    for (int i = 0; i < 571; i++) {
        hashT.remove(stopwordsarray[i]);
    }
 
    hashT.arraysort();
    hashT.printtopten();
    duration = (clock() - start) / (double)CLOCKS_PER_SEC;
    std::cout << "Total elapsed time:" << duration << " seconds";


    return 0;
}
