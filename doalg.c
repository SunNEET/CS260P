#include <stdio.h>

int doalg(int n, int k, int* Best){
    // Array "sort" stores largest 40
    int sort[40]={};
    // Give the first element initial smallest value.
    sort[0]=1;

    for(int i=2;i<=n;i++) {
        int l=0, r=(i>k)?k:i-1;
        
        // If the incoming number is smaller than 
        // the smallest number in largest 40, skip it
        if(i>k && COMPARE(i,sort[k-1])==2)
            continue;
        
        // Else do binary search to find right position
        // for it, 
        while(l<r) {
            int mid=l+(r-l)/2;
            if(COMPARE(i,sort[mid])==1) {
                r=mid;
            } else {
                l=mid+1;
            }
        }

        // Move i to the right position in sort[]
        int j=(i>k)?k-2:i-2;
        // push every element smaller than i
        // one step forward to empty the space for i
        while(j>=l) {
            sort[j+1]=sort[j];
            j--;
        }
        // put i into that position
        sort[l]=i;
    }

    // Copy sort[] to Best[]
    for(int i=0;i<40;i++) {
        Best[i]=sort[i];
    }
    return 1;
}