#include <stdio.h>
int main(void) {
    int n,i,time=0,completed=0,q;
    printf("Number of processes: "); scanf("%d",&n);
    int at[n],bt[n],rem[n],ct[n],tat[n],wt[n],added[n];
    for(i=0;i<n;i++){
        printf("P%d Arrival and Burst: ",i+1);
        scanf("%d%d",&at[i],&bt[i]);
        rem[i]=bt[i]; added[i]=0;
    }
    printf("Time quantum: "); scanf("%d",&q);
    if(q<=0){ printf("Quantum must be positive.\\n"); return 1; }
    int queue[100000],front=0,rear=0;
    for(i=0;i<n;i++)
        if(at[i]<=time){ queue[rear++]=i; added[i]=1; }
 
    while(completed<n){
        if(front==rear){
            int next=-1;
            for(i=0;i<n;i++)
                if(rem[i]>0 && !added[i] &&
                   (next==-1 || at[i]<at[next])) next=i;
            time=at[next];
            for(i=0;i<n;i++)
                if(rem[i]>0 && !added[i] && at[i]<=time){
                    queue[rear++]=i; added[i]=1;
                }
        }
        int p=queue[front++];
        int run=(rem[p]<q)?rem[p]:q;
        time+=run; rem[p]-=run;
 
        /* New arrivals join before the unfinished process re-enters. */
        for(i=0;i<n;i++)
            if(rem[i]>0 && !added[i] && at[i]<=time){
                queue[rear++]=i; added[i]=1;
            }
        if(rem[p]>0) queue[rear++]=p;
        else { ct[p]=time; completed++; }
    }
    printf("\\nPID\\tAT\\tBT\\tCT\\tTAT\\tWT\\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i];
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    return 0;
}
