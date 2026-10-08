#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countPairs(vector<int>& arr, int st, int mid, int end) {
        long long count = 0;
        int j = mid + 1;

        for (int i = st; i <= mid; i++) {
            while (j <= end && (long long)arr[i] > 2LL * arr[j]) {
                j++;
            }

            count += j - (mid + 1);
        }

        return count;
    }

    void merge(vector<int>& arr, int st, int mid, int end) {
        vector<int> temp;
        int i = st;
        int j = mid + 1;

        while (i <= mid && j <= end) {
            if (arr[i] <= arr[j]) {
                temp.push_back(arr[i]);
                i++;
            } else {
                temp.push_back(arr[j]);
                j++;
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
            arr[st + idx] = temp[idx];
        }
    }

    long long mergeSort(vector<int>& arr, int st, int end) {
        if (st >= end) return 0;

        int mid = st + (end - st) / 2;

        long long count = 0;
        count += mergeSort(arr, st, mid);
        count += mergeSort(arr, mid + 1, end);
        count += countPairs(arr, st, mid, end);

        merge(arr, st, mid, end);
        return count;
    }

    int reversePairs(vector<int>& nums) {
        return (int)mergeSort(nums, 0, nums.size() - 1);
    }
};

int main() {
    vector<int> nums = {1, 3, 2, 3, 1};

    Solution solution;
    int answer = solution.reversePairs(nums);

    cout << "Input: ";
    for (int value : vector<int>{1, 3, 2, 3, 1}) {
        cout << value << " ";
    }

    cout << "\nReverse pairs: " << answer << '\n';

    cout << "Sorted array: ";
    for (int value : nums) {
        cout << value << " ";
    }
    cout << '\n';

    return 0;
}