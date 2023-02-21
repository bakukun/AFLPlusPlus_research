	// test.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cassert>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

using namespace std;

string put(leveldb::DB *db, string key, int value) {
    string val;
    leveldb::Status s;

    // check if the given key exists in the DB
    s = db->Get(leveldb::ReadOptions(), key, &val);

    if (!s.ok()) {
        s = db->Put(leveldb::WriteOptions(), key, to_string(value));
        s = db->Get(leveldb::ReadOptions(), key, &val);
    } else {
        leveldb::WriteBatch batch;
        batch.Delete(key);
        batch.Put(key, to_string(value));
        s = db->Write(leveldb::WriteOptions(), &batch);
        s = db->Get(leveldb::ReadOptions(), key, &val);
    }

    return val;
}

//generate random number from 1-10 for value
int getRandomNumber() {
    srand((unsigned int)time(NULL));

    int tmp = rand();
    tmp = (int) tmp % 10;
    if (tmp == 0) tmp = 1;

    return tmp;
}

int main(int argc, char *argv[]) {
    // create DB
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);

    // Persistent Mode
    __AFL_INIT();
    while (__AFL_LOOP(10000)) {
        // Open file
        string filename = argv[1];
        std::ifstream file(filename);

        if (file.is_open()) {
            string line;
            string key;
            int value;

            getline(file, line);
            key = line;
            value = getRandomNumber();
            cout << "value inserted: " << put(db, key, value) << endl;
        } else {
            cout << "File not Opened" << endl;
        }
    }

    delete db;

    return 0;
}
