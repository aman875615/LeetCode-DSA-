#include <bits/stdc++.h>

using namespace std;

void mergeSort(vector<int>&nums,int l,int mid,int r){
    vector<int>temp;

    int i=l, j=mid+1;
    while(i<=mid && j<=r){
        if(nums[i]<=nums[j]){
            temp.push_back(nums[i]);
            i++;
        }
        else{
            temp.push_back(nums[j]);
            j++;
        }
    }
    while(i<=mid){
        temp.push_back(nums[i]);
        i++;
    }
    while(j<=r){
        temp.push_back(nums[j]);
        j++;
    }
    for(int i=l;i<=r;i++){
        nums[i] = temp[i-l];
    }

}

void merge(vector<int>&nums, int l, int r){
    if(l>=r) return ;
    int mid = l + (r-l) /2;
    merge(nums,l,mid);
    merge(nums,mid+1,r);
    mergeSort(nums,l,mid,r);
}


int main(){
    cout<<"Hare Krishna"<<endl;
    vector<int>nums = {1,90,3,4,9,6,7};
    int n= nums.size();
    int l =0,r=n-1;
    merge(nums,0,n-1);

    for(int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }

    return 0;
}
