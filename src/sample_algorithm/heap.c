#include <iostream>
using namespace std;

// adjust heap, from top to end, ensure that start is put to proper place
void adjustHeap(int arr[], int start, int end){
    int parent = start;
    int child = parent*2+1;
    int tmp;
    while(child < end){
        if(child+1 < end && arr[child] < arr[child+1]){
            child++;
        }
        if(arr[parent] >= arr[child]){
            return;
        }
        tmp = arr[parent];
        arr[parent] = arr[child];
        arr[child] = tmp;
        parent = child;
        child = parent*2+1;
    }
}

// ensure all non-leaf node
void initHeap(int arr[], int len){
    for(int i = len/2-1; i >= 0; i--){
        adjustHeap(arr, i, len);
    }
}

// shrink heap size, put heap top to tail, form a sorted array
void heapSort(int arr[], int len){
    int tmp;
    initHeap(arr, len);
    for(int i = len-1; i > 0; i--){
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        adjustHeap(arr, 0, i);
    }
}

// put last element to the top, return top
int heapPop(int arr[], int n){
    int ret = arr[0];
    arr[0] = arr[n-1];
    adjustHeap(arr, 0, n-1);
    return ret;
}

// append new element to end, then bubble it up (the bubble up path is sorted)
void heapPush(int arr[], int n, int num){
    int parent, child = n, tmp;
    arr[n] = num;
    while(child > 0){
        parent = (child-1)/2;
        if(arr[parent] > arr[child]){
            break;
        }else{
            tmp = arr[parent];
            arr[parent] = arr[child];
            arr[child] = tmp;
            child = parent;
        }
    }
}

int main(){
    int arr[] = {1,2,9,4,8,6,7,5,3};
    initHeap(arr, sizeof(arr)/sizeof(arr[0]));
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
    heapPop(arr, sizeof(arr)/sizeof(arr[0]));
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
    heapPush(arr, sizeof(arr)/sizeof(arr[0])-1, 88);
    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        cout << arr[i] << ' ';
    }
    cout << endl;
}
