#include "list.hpp"
#include "tools.hpp"
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(char *path);
int Menu(List &list);

int main() {
    char path[] = "testBase1.dat";
    List list = ReadFile(path);
    list.createIndexArray();
    while (true) {
        int res = Menu(list);
        if (!res)
            break;
    }
    return 0;
}

int Menu(List &list) {
    int key;
    cout << "�롥�� ���� ����:" << endl;
    cout << "0 - ��室" << endl;
    cout << "1 - �������� ���ଠ�� �� ��:" << endl;
    cout << "2 - ����஢�� ᫨ﭨ�� �� ���� 1-����⥫��⢮ 2-����:" << endl;
    cout << "3 - ������ ��ᨪ �� ���� �६ �㪢�� ����⥫��⢠:" << endl;
    cin >> key;
    if (CheckCin()) {
        key = -1;
    }
    switch (key) {
        case 0: {
            cout << "��室";
            return 0;
        }
        case 1: {
            list.printList();
            break;
        }
        case 2: {
            Node *tempHead = list.getHead();
            MergeSort(&tempHead);
            list.setHead(tempHead);
            list.createIndexArray();
            list.printList();
            break;
        }
        case 3: {
            Node *tempHead = list.getHead();
            MergeSort(&tempHead);
            list.setHead(tempHead);
            list.createIndexArray();
            int size = list.getSize();
            Node **arr = list.getIndexArray();
            char searchKey[] = "���";
            List queue;
            int res = BinarySearch(arr, 0, size, searchKey);
            if (res != -1) {
                queue.addNode(arr[res]->data);
            }
            while (res != -1) {
                res = BinarySearch(arr, res + 1, size, searchKey);
                if (res != -1) {
                    queue.addNode(arr[res]->data);
                }
            }
            queue.createIndexArray();
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
List ReadFile(char *path) {
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