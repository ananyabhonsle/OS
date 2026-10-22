#include <stdio.h>
void report(int n,int at[],int bt[],int ct[],int pr[],int showPr){
    int i,tat[100],wt[100]; float st=0,sw=0;
    if(showPr) printf("\\nPID\\tAT\\tBT\\tPR\\tCT\\tTAT\\tWT\\n");
    else printf("\\nPID\\tAT\\tBT\\tCT\\tTAT\\tWT\\n");
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i]; wt[i]=tat[i]-bt[i];
        if(showPr) printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
            i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);
        else printf("P%d\\t%d\\t%d\\t%d\\t%d\\t%d\\n",
            i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
        st+=tat[i]; sw+=wt[i];
    }
    printf("Average TAT = %.2f\\nAverage WT = %.2f\\n",st/n,sw/n);
}
void fcfs(int n,int at[],int bt[],int pr[]){
    int i,j,time=0,done[100]={0},ct[100];
    for(i=0;i<n;i++){
        int p=-1;
        for(j=0;j<n;j++) if(!done[j]&&(p==-1||at[j]<at[p])) p=j;
        if(time<at[p]) time=at[p];
        time+=bt[p]; ct[p]=time; done[p]=1;
    }
    report(n,at,bt,ct,pr,0);
}
void sjf(int n,int at[],int bt[],int pr[]){
    int i,time=0,done[100]={0},ct[100],completed=0;
    while(completed<n){
        int p=-1;
        for(i=0;i<n;i++) if(!done[i]&&at[i]<=time&&
            (p==-1||bt[i]<bt[p]||(bt[i]==bt[p]&&at[i]<at[p]))) p=i;
        if(p==-1){
            int next=-1;
            for(i=0;i<n;i++) if(!done[i]&&(next==-1||at[i]<at[next])) next=i;
            time=at[next]; continue;
        }
        time+=bt[p]; ct[p]=time; done[p]=1; completed++;
    }
    report(n,at,bt,ct,pr,0);
}
void priorityNP(int n,int at[],int bt[],int pr[]){
    int i,time=0,done[100]={0},ct[100],completed=0;
    while(completed<n){
        int p=-1;
        for(i=0;i<n;i++) if(!done[i]&&at[i]<=time&&
            (p==-1||pr[i]<pr[p]||(pr[i]==pr[p]&&at[i]<at[p]))) p=i;
        if(p==-1){
            int next=-1;
            for(i=0;i<n;i++) if(!done[i]&&(next==-1||at[i]<at[next])) next=i;
            time=at[next]; continue;
        }
        time+=bt[p]; ct[p]=time; done[p]=1; completed++;
    }
    report(n,at,bt,ct,pr,1);
}
void rr(int n,int at[],int bt[],int pr[],int q){
    int i,time=0,completed=0,rem[100],ct[100],added[100]={0};
    int queue[100000],front=0,rear=0;
    for(i=0;i<n;i++) rem[i]=bt[i];
    for(i=0;i<n;i++) if(at[i]<=time){queue[rear++]=i;added[i]=1;}
    while(completed<n){
        if(front==rear){
            int next=-1;
            for(i=0;i<n;i++) if(rem[i]>0&&!added[i]&&(next==-1||at[i]<at[next])) next=i;
            time=at[next];
            for(i=0;i<n;i++) if(rem[i]>0&&!added[i]&&at[i]<=time){
                queue[rear++]=i;added[i]=1;
            }
        }
        int p=queue[front++],run=(rem[p]<q)?rem[p]:q;
        time+=run; rem[p]-=run;
        for(i=0;i<n;i++) if(rem[i]>0&&!added[i]&&at[i]<=time){
            queue[rear++]=i;added[i]=1;
        }
        if(rem[p]>0) queue[rear++]=p;
        else {ct[p]=time;completed++;}
    }
    report(n,at,bt,ct,pr,0);
}
int main(void){
    int n,i,ch,q,at[100],bt[100],pr[100];
    printf("Number of processes (1-100): "); scanf("%d",&n);
    if(n<1||n>100){printf("Invalid number.\\n");return 1;}
    for(i=0;i<n;i++){
        printf("P%d Arrival Time and Burst Time: ",i+1); scanf("%d%d",&at[i],&bt[i]);
        printf("P%d Priority (smaller number = higher): ",i+1); scanf("%d",&pr[i]);
    }
    do{
        printf("\\n--- CPU Scheduling Menu ---\\n");
        printf("1. FCFS\\n2. SJF Non-Preemptive\\n3. Priority Non-Preemptive\\n4. Round Robin\\n0. Exit\\nChoice: ");
        scanf("%d",&ch);
        switch(ch){
            case 1: fcfs(n,at,bt,pr); break;
            case 2: sjf(n,at,bt,pr); break;
            case 3: priorityNP(n,at,bt,pr); break;
            case 4:
                printf("Time quantum: "); scanf("%d",&q);
                if(q<=0) printf("Quantum must be positive.\\n");
                else rr(n,at,bt,pr,q);
                break;
            case 0: printf("Exiting.\\n"); break;
            default: printf("Invalid choice.\\n");
        }
    }while(ch!=0);
    return 0;
}
