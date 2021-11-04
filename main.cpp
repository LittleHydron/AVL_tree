#include <bits/stdc++.h>
#include "Headers/Device.h"
#include "Headers/Binary_search_tree.h"

/**
Input for example:
7
p-n-p samsung 2021 12
n-p-n samsung 2000 1
n-p-n apple 2000 5
p-n-p iaomi 1991 4
p-n-p ziaomi 1991 4
p-n-p xiaomi 2012 4
p-n-p piaomi 1991 4
PRINT 2
DELETE 2000
PRINT 13
DELETE 2020
DELETE 2021
PRINT 3
STOP
**/

int keyForDelete;
double keyForPrint;

bool needToDelete(Device c){
    return (c.getYear() == keyForDelete);
}

bool needToPrint(Device c){
    return (c.getMaxVal() >= keyForPrint);
}

int main(){
    AVLtree < Device > tree;
    cout << "Enter initial number of devices: ";
    int n;
    cin >> n;
    for (int i=1; i<=n; i++){
        string type, mark;
        int year;
        double maxVal;
        cout << "Enter type, mark, year of creation and max value of your device (in this particular order): ";
        cin >> type >> mark >> year >> maxVal;
        tree.add(Device(type, mark, maxVal, year));
    }
    cout << "Tree content looks like:{\n";
    tree.printTree();
    cout << "}\n";
    while(1){
        cout << "Enter query(<TYPE> <NUMBER>, where <TYPE> == PRINT for printing by value and <TYPE> == DELETE for deleting by year and <TYPE> == STOP to stop):\n>";
        string type;
        cin >> type;
        if (type == "STOP") break;
        if (type == "PRINT"){
            cin >> keyForPrint;
            cout << "Devices with max value >= " << keyForPrint << ":{\n";
            tree.print_if(needToPrint);
            cout << "}\n";
        }else{
            if (type == "DELETE"){
                cin >> keyForDelete;
                tree.delete_if(needToDelete);
                cout << "Tree after deleting:{\n";
                tree.printTree();
                cout << "}\n";
            }
        }
    }
    return 0;
}

