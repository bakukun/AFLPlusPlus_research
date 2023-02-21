// test.cpp

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "leveldb/db.h"

using namespace std;

// C++에는 내장된 split함수가 없어서 직접 구현
vector<string> split(string str, char Delimiter) {
    istringstream iss(str);
    string buffer;

    vector<string> result;

    while (getline(iss, buffer, Delimiter)) {
        result.push_back(buffer);
    }

    return result;
}

int main(int argc, char *argv[]) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    assert(status.ok());

    leveldb::Status s;

    string file_name = argv[1];  //.txt 파일의 이름이 들어갈 자리이다.
    std::ifstream file(file_name);

    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            vector<string> result = split(line, ' ');
            string key1 = result[0];
            string value1 = result[1];
            string value;
            
            s=db->Put(leveldb::WriteOptions(), key1, value1);
            s=db->Get(leveldb::ReadOptions(), key1, &value);

            cout << key1 << "'s value == " << value << endl;
        }
        file.close();
    } else {
        cout << "Failed to open file" << endl;
    }

    delete db;

    return 0;
}
