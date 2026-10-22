#include <stdio.h>
int main(void) {
    int n, i, time=0, completed=0;
    printf("Number of processes: "); scanf("%d",&n);
    int at[n],bt[n],pr[n],ct[n],tat[n],wt[n],done[n];
    for(i=0;i<n;i++){
        printf("P%d Arrival Burst Priority: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&pr[i]); done[i]=0;
    }
    while(completed<n){
        int p=-1;
        for(i=0;i<n;i++){
            if(!done[i] && at[i]<=time &&
               (p==-1 || pr[i]<pr[p] ||
                (pr[i]==pr[p] && at[i]<at[p]))) p=i;
        }
        if(p==-1){
            int next=-1;
            for(i=0;i<n;i++)
                if(!done[i] && (next==-1 || at[i]<at[next])) next=i;
            time=at[next]; continue;
        }
        time+=bt[p]; ct[p]=time; done[p]=1; completed++;
    }
    printf("\\nPID\\tAT\\tBT\\tPR\\tCT\\tTAT\\tWT\\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i];
        printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
               i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
    }
    return 0;
}
