#include <stdio.h>

int doalg(int n, int k, int* Best){
    int arr[10001]={};
    int sort[40]={};
    for(int i=0;i<=n;i++) 
        arr[i]=i;
    // Use insertion sort for first 40 elements
    sort[0] = arr[1];
    for(int i=2;i<=40;i++) {
        int j=i-2;
        // Order it from high value to low value
        // arr[i]=key > sort[j], move it ahead.
        while(j>=0 && COMPARE(arr[i],sort[j])==1) {
            sort[j+1] = sort[j];
            j--;
        }
        sort[j+1] = arr[i];
    }

    // Now we got a sorted array, so we're able to use binary search to insert new elements
    for(int i=41;i<=n;i++) {
        int l=0,r=40;
        while(l<r) {
            int mid = l+(r-l)/2;
            if(COMPARE(arr[i],sort[mid])==1) {
                r=mid;
            } else {
                l=mid+1;
            }
        }
        // Insert arr[i] into sort[l], but we have to move each element after "l"
        int k = 38;
        while(k >= l) {
            sort[k+1] = sort[k];
            k--;
        }
        sort[l] = arr[i];
    }

    for(int i=0;i<40;i++) {
        Best[i] = sort[i];
    }
    return 1;
}