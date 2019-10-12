#include <iostream>
#include <fstream>
#include <vector>

#define NUM_OF_MARKS 4
#define MIN_MARK 8

using namespace std;

struct DATA_BASE {
    string surName;
    string initials;
    int year;
    int group;
    short marks[NUM_OF_MARKS];
    double avrMark;
};

void add(vector<DATA_BASE> &dataBase, ofstream &result);

void remove(vector<DATA_BASE> &dataBase);

void load(vector<DATA_BASE> &dataBase, fstream &file, ofstream &result);

void save(vector<DATA_BASE> &dataBase, fstream &file);

void list(vector<DATA_BASE> &dataBase);

void edit(vector<DATA_BASE> &database);

void commandFromUser(vector<DATA_BASE> dataBase);

int Index = 0;
ofstream result("result.txt", ofstream::out | ofstream::trunc);

int main() {
    cout << "Hello. This is a simple data base. You can use it by writing commands. For more information write 'help'";
    vector<DATA_BASE> dataBase;
    commandFromUser(dataBase);
    return 0;
}

void commandFromUser(vector<DATA_BASE> dataBase) {
    string commandFromUser;
    while (true) {
        cin >> commandFromUser;
        if (commandFromUser == "help") {
            cout << "\nlist of commands: \n'add': add new student \n'remove' or 'rm': remove student \n'list' or 'ls': list of students \n'edit': edit information about student \n'save': save database to file \n'exit': exit the program\n";
        } else if (commandFromUser == "add") {
            add(dataBase, result);
        } else if (commandFromUser == "remove" || commandFromUser == "rm") {
            remove(dataBase);
        } else if (commandFromUser == "ls" || commandFromUser == "list") {
            list(dataBase);
        } else if (commandFromUser == "edit") {
            edit(dataBase);
        } else if (commandFromUser == "save") {
            string fileName;
            cout << "\nWrite filename \n";
            cin >> fileName;
            fstream file(fileName, ofstream::out | ofstream::trunc);
            save(dataBase, file);
        } else if (commandFromUser == "load") {
            string fileName;
            cout << "\nWrite filename \n";
            cin >> fileName;;
            fstream file(fileName);
            if (file.is_open()) load(dataBase, file, result);
            else cout << "\nFailure";
        } else if (commandFromUser == "exit") {
            cout << "good luck";
            break;
        } else cout << "I don't now this command. To view commands list write help (" << commandFromUser << ")";
    }
}

void list(vector<DATA_BASE> &dataBase) {
    for (int i = 0; i < Index; ++i) {
        cout << i + 1 << "." << dataBase[i].surName << " " << dataBase[i].initials << " " << dataBase[i].year << " "
             << dataBase[i].group << " ";
        for (int j = 0; j < NUM_OF_MARKS; ++j) {
            cout << dataBase[i].marks[j] << " ";
        }
        cout << dataBase[i].avrMark << endl;
    }
}

void add(vector<DATA_BASE> &dataBase, ofstream &result) {
    int goodmarks = 0;
    DATA_BASE dataTemp;
    cout << "\nWrite new line in format 'surname' 'initials' 'year' 'group' 'mark1' 'mark2' 'markN'\n";
    dataTemp.avrMark = 0;
    cin >> dataTemp.surName >> dataTemp.initials >> dataTemp.year >> dataTemp.group;
    for (int i = 0; i < NUM_OF_MARKS; ++i) {
        cin >> dataTemp.marks[i];
        dataTemp.avrMark += dataTemp.marks[i];
        if (dataTemp.marks[i] >= MIN_MARK) goodmarks++;
    }
    dataTemp.avrMark = dataTemp.avrMark / NUM_OF_MARKS;

    if (goodmarks == NUM_OF_MARKS) {
        result << dataTemp.surName << " " << dataTemp.initials << " " << dataTemp.year << " " << dataTemp.group << " ";
        for (int j = 0; j < NUM_OF_MARKS; ++j) {
            result << dataTemp.marks[j] << " ";
        }
        result << dataTemp.avrMark;
    }
    dataBase.push_back(dataTemp);
    Index++;
    cout << "\nSuccessful";
}

void remove(vector<DATA_BASE> &dataBase) {
    cout << "\nwrite line for deletion";
    int ind;

    while (true) {
        cin >> ind;
        ind--;
        if (ind >= 0 && ind < Index) break;
        else cout << "Write num 0<n<" << Index;
    }

    cout << "deleted: \n" << dataBase[ind].surName << " " << dataBase[ind].initials << " " << dataBase[ind].year << " "
         << dataBase[ind].group << " ";
    for (int j = 0; j < NUM_OF_MARKS; ++j) {
        cout << dataBase[ind].marks[j] << " ";
    }
    cout << dataBase[ind].avrMark;

    dataBase.erase(dataBase.begin() + ind);
    Index--;

    cout << "\nSuccessful";
}

void load(vector<DATA_BASE> &dataBase, fstream &file, ofstream &result) {
    int goodmarks;
    string str;
    DATA_BASE dataTemp;
    while (getline(file, str)) {
        goodmarks = 0;
        dataTemp.avrMark = 0;
        file >> dataTemp.surName >> dataTemp.initials >> dataTemp.year >> dataTemp.group;
        for (int j = 0; j < NUM_OF_MARKS; ++j) {
            file >> dataTemp.marks[j];
            dataTemp.avrMark = dataTemp.avrMark + dataTemp.marks[j];
            if (dataTemp.marks[j] >= MIN_MARK) goodmarks++;
        }
        dataTemp.avrMark = dataTemp.avrMark / NUM_OF_MARKS;

        if (goodmarks == NUM_OF_MARKS) {
            result << dataTemp.surName << " " << dataTemp.initials << " " << dataTemp.year << " " << dataTemp.group
                   << " ";
            for (int j = 0; j < NUM_OF_MARKS; ++j) {
                result << dataTemp.marks[j] << " ";
            }
            result << dataTemp.avrMark << endl;
        }

        dataBase.push_back(dataTemp);
        Index++;
    }
    cout << "\nSuccessful";
}

void save(vector<DATA_BASE> &dataBase, fstream &file) {
    file << "surname" << "    year " << "group  " << " marks";
    for (int i = 0; i < Index; ++i) {
        file << endl;
        file << dataBase[i].surName << " " << dataBase[i].initials << " " << dataBase[i].year << " "
             << dataBase[i].group;

        for (int j = 0; j < NUM_OF_MARKS; ++j) {
            file << " " << dataBase[i].marks[j];
        }
    }
    file.close();
    cout << "\nSuccessful";
}

void edit(vector<DATA_BASE> &database) {
    int command;
    int ind;
    cout << "If you want to see database write 1\n";
    cin >> command;
    if (command == 1)list(database);

    cout << "write index of element, those you want to rewrite\n";
    cin >> ind;
    ind--;
    if (ind > Index) {
        cout << "your value too big";
        commandFromUser(database);
    }
    cout << "original line:\n" << ind + 1 << "." << database[ind].surName << " " << database[ind].initials << " "
         << database[ind].year << " " << database[ind].group << " ";
    for (int j = 0; j < NUM_OF_MARKS; ++j) {
        cout << database[ind].marks[j] << " ";
    }
    cout << database[ind].avrMark << endl;
    cout << "Write new line in format 'surname' 'initials' 'year' 'group' 'mark1' 'mark2' 'markN'\n";
    database[ind].avrMark = 0;
    cin >> database[ind].surName >> database[ind].initials >> database[ind].year >> database[ind].group;
    for (int i = 0; i < NUM_OF_MARKS; ++i) {
        cin >> database[ind].marks[i];
        database[ind].avrMark += database[ind].marks[i];
    }
    database[ind].avrMark = database[ind].avrMark / NUM_OF_MARKS;
    cout << "\nSuccessful";
}

