#include <stdio.h>

int doalg(int n, int k, int* Best){
    int arr[10001]={};
    int sort[40]={};
    for(int i=0;i<=n;i++) arr[i]=i;
    sort[0]=arr[1];

    for(int i=2;i<=n;i++) {
        int l=0, r=(i>40)?40:i-1;
        while(l<r) {
            int mid=l+(r-l)/2;
            if(COMPARE(arr[i],sort[mid])==1) {
                r=mid;
            } else {
                l=mid+1;
            }
        }
        int k=(i>40)?38:i-2;
        while(k>=l) {
            sort[k+1]=sort[k];
            k--;
        }
        sort[l]=arr[i];
    }

    for(int i=0;i<40;i++) {
        Best[i]=sort[i];
    }
    return 1;
}