#include "list.hpp"
#include "tools.hpp"
#include "tree.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path, List &list, List &queue, Tree &DOPA1);
void CreateQueue(List &list, List &queue);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    List list, searchQueue;
    Tree DOPA1;
    while (true) {
        int res = Menu(dataBasePath, list, searchQueue, DOPA1);
        if (!res) break;
    }
    return 0;
}

int Menu(const char *path, List &list, List &queue, Tree &DOPA1) {
    int key;
    cout << "Select a menu item:" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Download database on dynamic memory" << endl;
    cout << "2 - Print current database state" << endl;
    cout << "3 - Merge sort by fields: 1 - publisher 2 - author" << endl;
    cout << "4 - Binary search by first three letters publisher house" << endl;
    cout << "5 - Print queue by search results" << endl;
    cout << "6 - Build optimal binary search tree A1" << endl;
    cout << "7 - Tree traversal LNR" << endl;
    cout << "8 - Search in tree by year" << endl;
    cout << "9 - Encode database by Fano code" << endl;
    cin >> key;
    if (!CheckCin()) {
        cout << "Incorrect menu item selection!" << endl;
        return -1;
    }
    switch (key) {
        case 0: {
            cout << "Exit";
            return 0;
        }
        case 1: {
            if (list.isEmpty()) list = ReadFile(path);
            cout << "Database recorded on dynamic memory" << endl;
            break;
        }
        case 2: {
            list.printList();
            break;
        }
        case 3: {
            if (list.isEmpty()) {
                cout << "List is empty!" << endl;
            } else {
                if (!list.isSorted()) list.mergeSort();
                cout << "List successfully sorted " << endl;
            }
            break;
        }
        case 4: {
            list.createIndexArray();
            CreateQueue(list, queue);
            if (queue.isEmpty()) {
                cout << "No records found for this search key!" << endl;
            } else {
                queue.createIndexArray();
                cout << "Queue successfully build" << endl;
            }
            break;
        }
        case 5: {
            if (queue.isEmpty())
                cout << "Queue not built yet!" << endl;
            else
                queue.printList();
            break;
        }
        case 6: {
            if (queue.isEmpty()) {
                cout << "Queue for tree build doesn't ready!" << endl;
                break;
            } else if (DOPA1.isEmpty()) {
                DOPA1.setIndexArray(queue.getIndexArray(), queue.getIndexArraySize());
                DOPA1.buildTreeA1();
            }
            cout << "Tree successfully build" << endl;
            break;
        }
        case 7: {
            if (DOPA1.isEmpty())
                cout << "Tree doesn't ready" << endl;
            else {
                Vertex *root = DOPA1.getRoot();
                DOPA1.printLeftToRight(root);
            }
            break;
        }
        case 8: {
            if (DOPA1.isEmpty()) {
                cout << "Tree doesn't ready" << endl;
            } else {
                Vertex *root = DOPA1.getRoot();
                int searchKey;
                cout << "Please enter year for records search: ";
                cin >> searchKey;
                if (!CheckCin()) {
                    cout << "Incorrect entry of the search field!" << endl;
                    break;
                }
                List result = DOPA1.search(searchKey, root);
                if (result.isEmpty())
                    cout << "No records with this year were found in queue!" << endl;
                else
                    result.printList();
            }
            break;
        }
        case 9: {
            cout << "Fano code doesn't ready!" << endl;
            // todo Fano code
            break;
        }
        default: {
            cout << "There is no such item in the menu!" << endl;
            break;
        }
    }
    return 1;
}
char charToUppercase(char symbol) {
    if ((int) symbol > -96 && (int) symbol < -64)
        return (char) (symbol - 32);
    return symbol;
}
void CreateQueue(List &list, List &queue) {
    Node **arr = list.getIndexArray();
    char searchKey[4];
    int tryCounter = 0;
    cout << "Enter the first three letters of the publisher to search for: ";
    while (true) {
        cin >> searchKey;
        if (tryCounter != 0) {
            cout << "Input Error! try again" << endl;
        }
        tryCounter++;
        if (CheckCin()) break;
    }
    searchKey[0] = charToUppercase(searchKey[0]);
    int res = list.binarySearch(searchKey);
    queue.setFoundIndex(res);
    if (res != -1) {
        queue.addNode(arr[res]->data);
        do {
            res++;
            if (strncmp(arr[res]->data.publishingHouse, searchKey, strlen(searchKey)) == 0) {
                queue.addNode(arr[res]->data);
            } else {
                break;
            }
        } while (true);
    }
}
List ReadFile(const char *path) {
    List tempList;
    record temp{};
    ifstream file(path, ios::in | ios::binary);
    if (!file) {
        cout << "File open error !!!";
        return tempList;
    }
    while (file.read((char *) (&temp), sizeof(record))) {
        tempList.addNode(temp);
    }
    file.close();
    return tempList;
}
