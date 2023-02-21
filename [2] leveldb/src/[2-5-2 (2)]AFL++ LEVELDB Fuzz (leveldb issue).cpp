//bytetest.cpp
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

using namespace std;


void addKeyValues(leveldb::DB *db, std::ifstream& file) {
    if (file.is_open()) {
        leveldb::Status s;
        string line;
        string key;
        string value;

        //RANDOM VALUE
        srand((unsigned int)time(NULL));

        int rnd = rand();
        rnd = (int)rnd % 210000000;

				//0 < value < 210000000 
        if (rnd == 0) {
                rnd = 1;
        }

        cout << "rnd is" << rnd << endl;

        double tmp = 100000000;
        while (getline(file, line)) {
            key = line;
            value = string(tmp+rnd,'h');
            string get_value;
            s=db->Put(leveldb::WriteOptions(), key, value);
            if (s.ok())
                s = db->Get(leveldb::ReadOptions(), key, &get_value);
            if (s.ok())
                std::cout << get_value.size() << std::endl;


        }
    } else {
        cout << "File not opened" << endl;
        return;
    }
    return;
}

int main(int argc, char * argv[])
{
    leveldb::DB *db = nullptr;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./testdb", &db);
    assert(status.ok());
    cout<<sizeof(size_t)<<endl;

    string filename = argv[1];
    std::ifstream file(filename);

    addKeyValues(db, file);  //custom function to load DB with key-value pairs
    delete db;
    return 0;
}
