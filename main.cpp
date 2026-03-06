#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <string>
#include <sstream>

int runFIFO(int k, vector<int> r){
    vector<int> blockVect(k, -1);
    int missCounter = 0;
    vector<int> accessVect;

    for (int i = 0; i < r.size(); i++){
        bool complete = false;

        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                complete = true;
                break;
            }
            if (blockVect[j]==-1){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                complete = true;
                break;
            }
        }
        if (!complete){
            //request is not in cache
            for (int j = 0; j < blockVect.size(); j++){
                //find the cache block that has first in cache, replace it with the request
                if (blockVect[j] == accessVect[0]){
                    blockVect[j]=r[i];
                    break;
                }
            }
            //take out first item from FIFO list, make the request next in queue
            accessVect.erase(accessVect.begin());
            accessVect.push_back(r[i]);
            missCounter++;
        }
    }
    return missCounter;
}

int runLRU(int k, vector<int> r){
    vector<int> blockVect(k, -1);
    int missCounter = 0;
    vector<int> accessVect;

    for (int i = 0; i < r.size(); i++){
        bool complete = false;

        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                //remove request from LRU vector and place it on the end
                accessVect.erase(std::remove(accessVect.begin(), accessVect.end(), r[i]), accessVect.end());
                accessVect.push_back(r[i]);
                complete = true;
                break;
            }
            if (blockVect[j]==-1){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                complete = true;
                break;
            }
        }
        if (!complete){
            //request is not in cache
            for (int j = 0; j < blockVect.size(); j++){
                //find the cache block that has first in cache, replace it with the request
                if (blockVect[j] == accessVect[0]){
                    blockVect[j]=r[i];
                }
            }
            //take out first item from FIFO list, make the request next in queue
            accessVect.erase(accessVect.begin());
            accessVect.push_back(r[i]);
            missCounter++;
        }
    }
    return missCounter;
}

int runOPTFF(int k, vector<int> r){
    vector<int> blockVect(k, -1);
    int missCounter = 0;

    for (int i = 0; i < r.size(); i++){
        bool complete = false;

        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==r[i]){
                //cache hit
                complete = true;
                break;
            }
            if (blockVect[j]==-1){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                complete = true;
                break;
            }
        }
        if (!complete){
            //request is not in cache
            int maxDistance = -1;
            int blockToSwap = 0;

            //find the max (cache block next appearance distance)
            for (int j = 0; j < blockVect.size(); j++){
                int currdistance = INT_MAX;

                //last request, always a miss, break to replace block[0]
                if (i==r.size()-1){
                    break;
                }

                for (int p = i+1; p < r.size();p++){
                    if (r[p] == blockVect[j]){
                        currdistance = p - i; 
                        break;
                    }
                }
                if (currdistance > maxDistance){
                    maxDistance = currdistance;
                    blockToSwap = j;
                }
            }
            blockVect[blockToSwap] = r[i];
            missCounter++;
        }
    }
    return missCounter;
}

int main()
{
    ifstream file("input.txt");

    string line;
    vector<int> km;
    vector<int> r;

    //first line
    getline(file, line);
    istringstream l1(line);
    int num;
    while (l1 >> num){
        km.push_back(num);
    }

    //second line
    getline(file, line);
    istringstream l2(line);
    while (l2 >> num){
        r.push_back(num);
    }

    file.close();

    if (km.size() != 2){
        cout<< "wrong input format"<<endl;
        return -1;
    }

    int k = km[0];
    int m = km[1];

    if (k < 1){
        std::cout << "k needs to be greater than or equal to 1" << std:: endl;
        return -1;
    }
    if (m != r.size()){
        cout<< "stated request size is not the same as actual request size" <<endl;
        return -1;
    }

    //run cache replacement algorithms
    int missesFIFO = runFIFO(k, r);
    int missesLRU = runLRU(k, r);
    int missesOPTFF = runOPTFF(k, r);

    //write output
    ofstream outputFile;
    outputFile.open("output.txt");
    outputFile << "FIFO  : "<<missesFIFO<<"\n";
    outputFile << "LRU   : "<<missesLRU<<"\n";
    outputFile << "OPTFF : "<<missesOPTFF<<"\n";
    outputFile.close();
}