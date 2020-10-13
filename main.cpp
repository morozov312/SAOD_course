#include "list.hpp"
#include "tools.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path);
List CreateQueue(List list);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    while (true) {
        int res = Menu(dataBasePath);
        if (!res)
            break;
    }
    return 0;
}

int Menu(const char *path) {
    int key;
    cout << "�롥�� ���� ����:" << endl;
    cout << "0 - ��室" << endl;
    cout << "1 - �������� ���ଠ�� �� ��:" << endl;
    cout << "2 - ����஢�� ᫨ﭨ�� �� ���� 1-����⥫��⢮ 2-����:" << endl;
    cout << "3 - ������ ��ᨪ �� ���� �६ �㪢�� ����⥫��⢠:" << endl;
    cout << "4 - ����ந�� ��ॢ� ��⨬��쭮�� ���᪠ �1:" << endl;
    cout << "5 - ������஢��� �� ����� ����:" << endl;
    cin >> key;
    if (!CheckCin()) {
        key = -1;
    }
    switch (key) {
        case 0: {
            cout << "��室";
            return 0;
        }
        case 1: {
            List list = ReadFile(path);
            list.printList();
            break;
        }
        case 2: {
            List list = ReadFile(path);
            list.mergeSort();
            list.printList();
            break;
        }
        case 3: {
            List list = ReadFile(path);
            list.mergeSort();
            List queue;
            list.createIndexArray();
            queue = CreateQueue(list);
            queue.printList();
            break;
        }
        default: {
            cout << "������ �㭪� ���" << endl;
            break;
        }
    }
    return 1;
}
List CreateQueue(List list) {
    Node **arr = list.getIndexArray();
    const char searchKey[] = "���";
    List queue;
    int res = list.binarySearch(searchKey);
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
    return queue;
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