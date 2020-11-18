#include "list.hpp"
#include "tools.hpp"
#include "tree.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

List ReadFile(const char *path);
int Menu(const char *path, List &list, List &queue);
void CreateQueue(List &list, List &queue);

int main() {
    const char dataBasePath[] = "testBase1.dat";
    List list, searchQueue;
    while (true) {
        int res = Menu(dataBasePath, list, searchQueue);
        if (!res) break;
    }
    return 0;
}

int Menu(const char *path, List &list, List &queue) {
    int key;
    cout << "�롥�� ���� ����:" << endl;
    cout << "0 - ��室" << endl;
    cout << "1 - ����㧨�� �� � ���������� ������" << endl;
    cout << "2 - �뢮� ⥪�饣� ���ﭨ� ��" << endl;
    cout << "3 - ����஢�� ᫨ﭨ�� �� ���� 1-����⥫��⢮ 2-����:" << endl;
    cout << "4 - ������ ��ᨪ �� ���� �६ �㪢�� ����⥫��⢠:" << endl;
    cout << "5 - ����ந�� ��ॢ� ��⨬��쭮�� ���᪠ �1:" << endl;
    cout << "6 - ������஢��� �� ����� ����:" << endl;
    cin >> key;
    if (!CheckCin()) {
        cout << "�����४�� �롮� �㭪� ����!" << endl;
        return -1;
    }
    switch (key) {
        case 0: {
            cout << "��室";
            return 0;
        }
        case 1: {
            list = ReadFile(path);
            cout << "���� ������ �뫠 ����㦥�� � ���������� ������" << endl;
            break;
        }
        case 2: {
            list.printList();
            break;
        }
        case 3: {
            list.mergeSort();
            cout << "���᮪ �ᯥ譮 �����஢��!" << endl;
            break;
        }
        case 4: {
            list.createIndexArray();
            CreateQueue(list, queue);
            if (queue.isEmpty())
                cout << "�� ������� ����� ���᪠ ����ᥩ �� �������!" << endl;
            else
                queue.printList();
            break;
        }
        case 5: {
            if (queue.isEmpty()) {
                break;
            } else {
                Tree DOPA1(queue.getIndexArray(), queue.getIndexArraySize());
                DOPA1.buildTreeA1();
                Vertex *root = DOPA1.getRoot();
                DOPA1.printLeftToRight(root);
                cout << endl;
            }
            break;
        }
        case 6: {
            cout << "����஢�� �� �� ��⮢�" << endl;
            // todo Fano code
            break;
        }
        default: {
            cout << "������ �㭪� ���" << endl;
            break;
        }
    }
    return 1;
}
void CreateQueue(List &list, List &queue) {
    Node **arr = list.getIndexArray();
    char searchKey[3];
    int tryCounter = 0;
    cout << "������ ���� �� �㪢� ����⥫��⢠ ��� ���᪠: ";
    while (true) {
        cin >> searchKey;
        if (tryCounter != 0) {
            cout << "�訡�� �����! ���஡�� �� ࠧ" << endl;
        }
        tryCounter++;
        if (CheckCin()) break;
    }
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