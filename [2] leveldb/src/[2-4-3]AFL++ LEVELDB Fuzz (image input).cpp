// test.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>
#include <chrono>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char *argv[]) {
    // Create DB
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/testdb", &db);
    assert(status.ok());

    // Read File 
    string filename(argv[1]);
    ifstream fin;
    fin.open(filename, ios::binary);
    if (fin.fail()) {
        return -1;
    }
    // Put the file in stream
    ostringstream oss;
    oss << fin.rdbuf();
    string data(oss.str());

    // Get current time
    auto now = chrono::system_clock::now();
    time_t key = chrono::system_clock::to_time_t(now);

    // Check the data
    leveldb::Status s;
    cout << "Current Time: " << key << endl;
    cout << "Image: " << data << endl;

    // Put the key-value pair
    s = db->Put(leveldb::WriteOptions(), key, data);
    string val;
    if (s.ok()) s=db->Get(leveldb::ReadOptions(), key, &val);
    cout << val << endl;
    // Close DB
    delete db;
    // Close file
    fin.close();

    return 0;
}
