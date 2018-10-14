#include <stdio.h>

int doalg(int n, int k, int* Best){
    int arr[10001]={};
    int heap[41]={};
    int h_cnt = 0;
    for(int i=1;i<=n;i++) arr[i]=i;
    for(int i=1;i<=n;i++) {
        if(!h_cnt)        
            heap[h_cnt++] = arr[i];
        else {
            int cur_loc = h_cnt;
            // 接40th之前
            if(h_cnt >= 40 && COMPARE(heap[0], arr[i])==1){
                continue;
            } else {
                heap[h_cnt] = arr[i];
                while(COMPARE(heap[cur_loc], heap[(cur_loc-1)/2])==2){
                    cur_loc = (cur_loc-1)/2;
                    heap[h_cnt] = heap[h_cnt]^heap[(h_cnt-1)/2];
                    heap[(h_cnt-1)/2] = heap[h_cnt]^heap[(h_cnt-1)/2];
                    heap[h_cnt] = heap[h_cnt]^heap[(h_cnt-1)/2];
                }
                h_cnt = (h_cnt < 40) ? h_cnt+1 : 40;
            }
        }
        if( h_cnt >= 40) {
            heap[0] = arr[i];
            int cur = 0;
            int l = 1;
            int r = 2;
            while(l <= 40 && r <= 40) {
                // printf("i=%d, cur=%d\n",i,cur);
                l = cur*2+1;
                r = cur*2+2;
                
                if((COMPARE(heap[cur],heap[l])==2) && (COMPARE(heap[cur], heap[r])==2))
                    break;
                if(COMPARE(heap[l], heap[r])==1) {
                    // 走右邊
                    if(COMPARE(heap[cur], heap[r])==1) {
                        heap[cur] = heap[cur]^heap[r];
                        heap[r] = heap[cur]^heap[r];
                        heap[cur] = heap[cur]^heap[r];
                        cur = r;
                    }
                } else {
                    if(COMPARE(heap[cur], heap[l])==1) {
                        heap[cur] = heap[cur]^heap[l];
                        heap[l] = heap[cur]^heap[l];
                        heap[cur] = heap[cur]^heap[l];
                        cur = l;
                    }
                }
                
                // printf("HEAPIFY!\n");
            } 
        }
    }
    
    for(int i=0;i<40;i++) {
        printf("%d\n", heap[i]);
    }
    int cnt = 0;
    for(int i=n;i>=n-k;i--) {
        Best[cnt++] = arr[i];
    }
    return 1;
}