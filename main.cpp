#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <string>

int runFIFO(int k, vector<int> r){
    int misses;
    cout << "FIFO: " << endl;

    vector<int> blockVect(k, -1);
    int missCounter = 0;
    int hitCounter = 0;
    vector<int> accessVect;

    for (int i = 0; i < r.size(); i++){
        cout<<"iteration " << i+1 << endl;
        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                hitCounter++;
                break;
            }
            if (blockVect[j]==-1){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                break;
            }
            if (j==blockVect.size()-1){
                //request is not in cache
                for (int k = 0; k < blockVect.size(); k++){
                    //find the cache block that has first in cache, replace it with the request
                    if (blockVect[k] == accessVect[0]){
                        blockVect[k]=r[i];
                    }
                }
                //take out first item from FIFO list, make the request next in queue
                accessVect.erase(accessVect.begin());
                accessVect.push_back(r[i]);
                missCounter++;
            }
        }
        for (int i = 0; i < blockVect.size(); i++) {
            cout << blockVect[i] << endl;
        }
    }
    misses=missCounter;
    cout << "number of FIFO misses: " << missCounter <<endl;
    cout << "number of FIFO hits: " << hitCounter <<endl;
    return misses;
}

int main()
{
    ifstream file("input.txt");
    string line;
    
    vector<int> km;
    vector<int> r;

    if (file.is_open()){
        //first line
        getline(file, line);
        string del = " ";
        auto pos = line.find(del);
        while (pos!=string::npos){
            km.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + del.length());
            pos = line.find(del);
        }
        km.push_back(stoi(line));
        //second line
        getline(file, line);
        del = " ";
        pos = line.find(del);
        while (pos!=string::npos){
            r.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + del.length());
            pos = line.find(del);
        }
        r.push_back(stoi(line));
    }

    int k = km[0];
    int m = km[1];

    if (k < 1){
        std::cout << "k needs to be greater than or equal to 1" << std:: endl;
        return -1;
    }

    cout << "k: " << k << endl;
    cout << "m: " << m << endl;
    cout << "r: ";
    for (int i = 0; i < r.size(); i++) {
        cout << r[i] << " ";
    }
    cout<<endl;

    int missesLRU;
    int missesOPTFF;

    int missesFIFO = runFIFO(k, r);

    cout << "LRU: " << endl;
    vector<int> accessVect;
    vector<int> blockVect2(k, NULL);
    vector<int> blockVect=blockVect2;
    int missCounter = 0;
    int hitCounter = 0;

    for (int i = 0; i < r.size(); i++){
        cout<<"iteration " << i+1 << endl;
        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                //remove request from LRU vector and place it on the end
                accessVect.erase(std::remove(accessVect.begin(), accessVect.end(), r[i]), accessVect.end());
                accessVect.push_back(r[i]);
                hitCounter++;
                break;
            }
            if (blockVect[j]==NULL){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                break;
            }
            if (j==blockVect.size()-1){
                //request is not in cache
                for (int k = 0; k < blockVect.size(); k++){
                    //find the cache block that has first in cache, replace it with the request
                    if (blockVect[k] == accessVect[0]){
                        blockVect[k]=r[i];
                    }
                }
                //take out first item from FIFO list, make the request next in queue
                accessVect.erase(accessVect.begin());
                accessVect.push_back(r[i]);
                missCounter++;
            }
        }
        for (int i = 0; i < blockVect.size(); i++) {
            cout << blockVect[i] << endl;
        }
    }
    missesLRU = missCounter;
    cout << "number of LRU misses: " << missCounter <<endl;
    cout << "number of LRU hits: " << hitCounter <<endl;






    cout << "OPTFF: " << endl;

    vector<int> blockVect3(k, NULL);
    blockVect=blockVect3;
    missCounter = 0;
    hitCounter = 0;

    int blockToSwap = 0;
    int max=0;
    int temp=0;
    int indexFar = 0;

    for (int i = 0; i < r.size(); i++){
        cout<<"iteration " << i+1 << endl;
        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                hitCounter++;
                break;
            }
            if (blockVect[j]==NULL){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                break;
            }
            if (j==blockVect.size()-1){
                //request is not in cache
                blockToSwap = 0;
                //find the max (cache block next appearance distance)
                for (int k = 0; k < blockVect.size(); k++){
                    //last request is a miss, replace first cache
                    if (i==r.size()-1){
                        blockVect[0] = r[i];
                        break;
                    }
                    temp = 1;
                    for (int p = i+1; p < r.size();p++){
                        cout<<"block: "<<k<<" | index: "<<p<< " | value: "<<r[p]<<" | temp: "<<temp<< " | max: "<<max<<endl;
                        if (r[p] == blockVect[k]){
                            if (temp > max){
                                max = temp;
                                indexFar = p;
                                break;
                            }
                            break;
                        }
                        temp++;
                        //cache block doesnt appear again
                        if ((p == r.size()-1) && (max!=INT_MAX)){
                            max = INT_MAX;  //ensure this is the block that is replaced
                            cout<<"looking for "<<blockVect[k]<<endl;
                            for (int v =0;v<r.size();v++){//indexFar is just some index that has the replace block
                                if (blockVect[k]==r[v]){
                                    indexFar=v;
                                    break;
                                }
                            }
                        }
                    }
                }
                cout<<"max val: "<<max<<endl;
                cout<<"far index: "<<indexFar<<endl;
                for (int k = 0; k < blockVect.size(); k++){
                    //find the cache block with same val at indexFar, replace it with request
                    if (blockVect[k] == r[indexFar]){
                        blockVect[k]=r[i];
                    }
                }
                missCounter++;
            }
            max=0;
        }
        for (int i = 0; i < blockVect.size(); i++) {
            cout << blockVect[i] << endl;
        }
    }
    missesOPTFF = missCounter;
    cout << "number of OPTFF misses: " << missCounter <<endl;
    cout << "number of OPTFF hits: " << hitCounter <<endl;



    ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << "FIFO  : "<<missesFIFO<<"\n";
    outputFile << "LRU   : "<<missesLRU<<"\n";
    outputFile << "OPTFF : "<<missesOPTFF<<"\n";
    outputFile.close();
}