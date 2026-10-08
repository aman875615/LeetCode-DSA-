#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long merge(vector<int>& arr, int st, int mid, int end) {
        vector<int> temp;
        int i = st;
        int j = mid + 1;
        long long count = 0;

        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {
                temp.push_back(arr[i]);
                i++;
            } else {
                temp.push_back(arr[j]);
                j++;

                // arr[i] se arr[mid] tak ke sab elements
                // current arr[j - 1] se bade hain.
                count += mid - i + 1;
            }
        }

        while (i <= mid) {
            temp.push_back(arr[i]);
            i++;
        }

        while (j <= end) {
            temp.push_back(arr[j]);
            j++;
        }

        for (int idx = 0; idx < temp.size(); idx++) {
            arr[idx + st] = temp[idx];
        }

        return count;
    }

    long long mergeSort(vector<int>& arr, int st, int end) {
        if (st >= end) {
            return 0;
        }

        int mid = st + (end - st) / 2;

        long long count = 0;
        count += mergeSort(arr, st, mid);
        count += mergeSort(arr, mid + 1, end);
        count += merge(arr, st, mid, end);

        return count;
    }

    long long inversionCount(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};