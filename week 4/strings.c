/* Custom versions of standard string functions. */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define and &&
#define or ||
#define not !

// Find the length of a string, assuming it has a null terminator (like strlen).
int length(const char s[]) {
    int length = 0;
    for (; s[length] != 0; length++);
    return length;
}

// Copy string s into the character array t (like strcpy).
void copy(char t[], const char s[]) {
    for (size_t index = 0;; index++){
        t[index] = s[index];
        if (s[index] == 0){
            break;
        }
    }
}

// Compare two strings, returning negative, zero or positive (like strcmp).
int compare(const char s[], const char t[]) {
    size_t index = 0;
    for (;; index++){
        char difference = s[index] - t[index];
        if (difference < 0){
            return -1;
        }
        else if (difference > 0){
            return 1;
        }
        if (not s[index] and not t[index]){
            return 0;
        }
        else if (not s[index]){
            return -1;
        }
        else if (not t[index]){
            return 1;
        }
    }
}

// Join string s to the end of string t (like strcat).
void append(char t[], const char s[]) {
    int index1 = length(t);
    for (size_t index2 = 0;; index2++, index1++){
        t[index1] = s[index2];
        if (s[index2] == 0){
            break;
        }
    }
}

// Find the (first) position of s in t, or return -1 (like strstr).
int find(const char t[], const char s[]) {
    for (size_t index = 0; t[index] != 0; index++){
        if (t[index] == s[0]){
            size_t index2 = 0;
            bool flag = true;
            for (; t[index + index2] != 0 and s[index2] != 0; index2++){
                if (t[index + index2] != s[index2]){
                    flag = false;
                    break;
                }
            }
            if (flag){
                return index;
            }
        }
    }
    return -1;
}

// -----------------------------------------------------------------------------
// Tests and user interface

// Custom assert function to replace the one in assert.h. Reports the test
// number, not the line number.
void assert(bool b) {
    static int testNumber = 0;
    testNumber++;
    if (! b) {
        printf("Test %d failed\n", testNumber);
        exit(1);
    }
}

// Tests 1 to 5
void testLength() {
    assert(length("") == 0);
    assert(length("c") == 1);
    assert(length("ca") == 2);
    assert(length("cat") == 3);
    char s[] = "dog";
    assert(length(s) == 3);
}

// Tests 6 to 9
void testCopy() {
    char t[10];
    copy(t, "cat");
    assert(t[0] == 'c' && t[1] =='a' && t[2] == 't' && t[3] =='\0');
    copy(t, "at");
    assert(t[0] == 'a' && t[1] =='t' && t[2] =='\0');
    copy(t, "t");
    assert(t[0] == 't' && t[1] =='\0');
    copy(t, "");
    assert(t[0] == '\0');
}

// Tests 10 to 17
void testCompare() {
    assert(compare("cat", "dog") < 0);
    assert(compare("dog", "cat") > 0);
    assert(compare("cat", "cat") == 0);
    assert(compare("an", "ant") < 0);
    assert(compare("ant", "an") > 0);
    assert(compare("", "a") < 0);
    assert(compare("a", "") > 0);
    assert(compare("", "") == 0);
}

// Tests 18 to 20
void testAppend() {
    char t[10] = {'c', 'a', 't', '\0', 'x'};
    append(t, "");
    assert(t[0]=='c' && t[1]=='a' && t[2]=='t' && t[3]=='\0' && t[4]=='x');
    char u[10] = {'c', 'a', '\0', 'x', 'x'};
    append(u, "t");
    assert(u[0]=='c' && u[1]=='a' && u[2]=='t' && u[3]=='\0' && u[4]=='x');
    char v[10] = {'\0', 'x', 'x', 'x', 'x'};
    append(v, "cat");
    assert(v[0]=='c' && v[1]=='a' && v[2]=='t' && v[3] =='\0' && v[4]=='x');
}

// Tests 21 to 25
void testFind() {
    assert(find("cat", "cat") == 0);
    assert(find("cat", "c") == 0);
    assert(find("cat", "t") == 2);
    assert(find("cat", "x") == -1);
    assert(find("banana", "an") == 1);
}

// Test the functions.
int main() {
    testLength();
    testCopy();
    testCompare();
    testAppend();
    testFind();
    printf("Tests all pass.");
    return 0;
}
