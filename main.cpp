#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
    int k = 2;
    int m=9;

    vector<int> r{1,2,3,3,2,1};
        r.push_back(2);
        r.push_back(1);
        r.push_back(3);

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


    cout << "FIFO: " << endl;

    vector<int> blockVect(k, NULL);
    int missCounter = 0;
    int hitCounter = 0;
    vector<int> accessVect;

    for (int i = 0; i < r.size(); i++){
        cout<<"iteration " << i+1 << endl;
        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==NULL){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                break;
            }
            if (blockVect[j]==r[i]){
                //cache hit
                hitCounter++;
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
    cout << "number of FIFO misses: " << missCounter <<endl;
    cout << "number of FIFO hits: " << hitCounter <<endl;


    



    cout << "LRU: " << endl;

    vector<int> blockVect2(k, NULL);
    blockVect=blockVect2;
    missCounter = 0;
    hitCounter = 0;
    accessVect.clear();

    for (int i = 0; i < r.size(); i++){
        cout<<"iteration " << i+1 << endl;
        for (int j = 0; j < blockVect.size(); j++){
            if (blockVect[j]==NULL){
                //empty cache
                blockVect[j] = r[i];
                missCounter++;
                accessVect.push_back(blockVect[j]);
                break;
            }
            if (blockVect[j]==r[i]){
                //cache hit
                //remove request from LRU vector and place it on the end
                accessVect.erase(std::remove(accessVect.begin(), accessVect.end(), r[i]), accessVect.end());
                accessVect.push_back(r[i]);
                hitCounter++;
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
    cout << "number of LRU misses: " << missCounter <<endl;
    cout << "number of LRU hits: " << hitCounter <<endl;

}