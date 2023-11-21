#include <iostream>
#include <vector>
using namespace std;

vector<int> append(vector<int> a, vector<int> b){
    vector<int> bog;

    for(int i = 0;i < a.size();i++){
        bog.push_back(a[i]);
    }

    for(int j = 0; j < b.size();j++){
        bog.push_back(b[j]);
    }
    return bog;
}

int main(){
    vector<int> A = {1,2,3,4,5};
    vector<int> B = {9,3,4,5,6};

    vector<int> result = append(A, B);

    for(int i = 0; i < result.size();i++){
        cout << result[i] << " ";
    }

    cout << endl;
    return 0;
}
