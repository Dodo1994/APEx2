

#include "IDCreator.h"

string IDCreator::create(bool save) {
    static unsigned long count = 10000000000;
    if(!save) {
        static bool opened = false;
        if (!opened) {
            count = IDCreator::loadCount();
            opened = true;
        }
        stringstream stream;
        stream << std::hex << count;
        string result(stream.str());
        count++;
        return result;
    }
    else{
        ofstream file("Count.txt");
        if (file.fail()) {
            cerr << "Error opening file" << endl;
            exit(1);
        }
        file << count;
        return "";
    }
}

unsigned long IDCreator::loadCount() {
    ifstream file("Count.txt");
    // Check error.
    if (file.fail()) {
        return 10000000000;
    }
    unsigned long count;
    file >> count;
    return count;
}

IDCreator::IDCreator() = default;
