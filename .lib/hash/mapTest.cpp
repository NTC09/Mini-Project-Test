#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <chrono>

using namespace std;

map<string, int> nameList;

unordered_map<string, int> table;

string name = "";
int nameIndex = 0;

void resCreateName(int count){
    if (nameIndex == 200000)
        return;
    if (count == 10){
        //cout << name << endl;
        nameList[name] = nameIndex++;
        return;
        
    }
    for (char x = 'z'; x >= 'a'; x--){
        name.push_back(x);
        resCreateName(count+1);
        name.pop_back();
    }
}

void resCreateName2(int count){
    if (nameIndex == 400000)
        return;
    if (count == 10){
        //cout << name << endl;
        nameList[name] = nameIndex++;
        return;
        
    }
    for (char x = 'a'; x <= 'z'; x++){
        name.push_back(x);
        resCreateName(count+1);
        name.pop_back();
    }
}

int main(){


    // Insertion
    table.insert(make_pair("mrbean", 999));
    table["mrbean"] = 111; // this also change the value or use to find

    cout << table["mrbean"] << endl;

    // Deletion
    table.erase("something");

    // Find
    auto it = table.find("anyone");
    it->first;  // string value
    it->second; // int value
    /*auto st = chrono::high_resolution_clock::now();
    resCreateName(0);
    resCreateName2(0);
    //map<string, int> a;
    //for (int i=0;i<1000;i++)
    for ( auto a = nameList.begin();a != nameList.end(); a++){
        //cout << a->first << endl;
        a->second++;
    }
    auto a = --nameList.end();
    cout << a->first << endl;

    auto en = chrono::high_resolution_clock::now();
    double time = chrono::duration_cast<chrono::microseconds>(en-st).count();
    cout << time/1.0e6 << endl;// << nameIndex;*/
    return 0;
}




/**
 * @brief 
 * 
 * 
 * 
 * 
 */
