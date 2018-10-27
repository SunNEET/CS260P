#include <stdio.h>

int doalg(int n, int k, int* Best){
    int arr[10001]={};
    int sort[40]={};
    sort[0]=1;

    for(int i=2;i<=n;i++) {
        int l=0, r=(i>k)?k:i-1;
        if(i>k && COMPARE(i,sort[k-1])==2)
            continue;
        while(l<r) {
            int mid=l+(r-l)/2;
            if(COMPARE(i,sort[mid])==1) {
                r=mid;
            } else {
                l=mid+1;
            }
        }
        int j=(i>k)?k-2:i-2;
        while(j>=l) {
            sort[j+1]=sort[j];
            j--;
        }
        sort[l]=i;
    }

    for(int i=0;i<40;i++) {
        Best[i]=sort[i];
    }
    return 1;
}