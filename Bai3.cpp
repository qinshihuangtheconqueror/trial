#include<bits/stdc++.h>
using namespace std;
int cur_number = 1;
int cur_queue = 1;
queue<int>q[1000];
int total_cus = 0;
int cnt[1000]={0};
int max_queue = 4;
int total_queue = 4;
int status[1000] = {0};
int main()
{
    for(int i =1 ; i<=4 ; i++) status[i] = 1;
    char c[20];
    while(1)
    {
        cin >> c;
        if(strcmp(c,"***")==0) break;
        if(strcmp(c,"$Enter") == 0)
        {
            while(status[cur_queue] == 0)
            {
                if(cur_queue < max_queue) cur_queue++;
                else cur_queue = 1;
            }
            cout << cur_number << ' ' << cur_queue << '\n';
            q[cur_queue].push(cur_number);
            cnt[cur_queue]++;
            cur_number++;
            if(cur_queue < max_queue) cur_queue++;
            else cur_queue = 1;
            total_cus++;
        }
        else if(strcmp(c,"$Checkout") == 0)
        {
            int x; cin >> x;
            cout << q[x].front() << '\n';
            q[x].pop();
            cnt[x]--;
            total_cus--;
        }
        else if(strcmp(c,"$AdvancedEnter") == 0)
        {
            int Min = 1;
            for(int i=1; i<=total_queue;i++)
            {
                if(cnt[i] < cnt[Min]) Min = i;
            }
            cout << cur_number << ' ' << Min << '\n';
            q[Min].push(cur_number);
            cnt[Min]++;
            cur_number++;
            total_cus++;
        }
        else if(strcmp(c,"$CountNumberCustomerInLine") == 0)
        {
            int x; cin >> x;
            cout << cnt[x] << '\n';
        }
         else if(strcmp(c,"$ListCustomerInLine") == 0)
        {
            int x; cin >> x;
            for(int i = 1 ; i<=cnt[x]; i++ )
            {
               cout << q[x].front() << ' ' ;
               q[x].push(q[x].front());
               q[x].pop();

            }
            cout << '\n';
        }
        else if(strcmp(c,"$CountNumberCustomerInAllLines") == 0)
        {
            cout << total_cus << '\n';
        }
        else if(strcmp(c,"$OpenCashier") == 0)
        {
            max_queue++;
            total_queue++;
            status[max_queue]=1;
            cout << max_queue << '\n';
        }
         else if(strcmp(c,"$CloseCashier") == 0)
        {
            int x; cin >> x;
            status[x]=0;
            for(int i= 1 ; i<= cnt[x];i++)
            {
                 while(status[cur_queue] != 1)
                 {
                    if(cur_queue < max_queue) cur_queue++;
                    else cur_queue = 1;
                 }
                  q[cur_queue].push(q[x].front());
                        cnt[cur_queue]++;
                        cur_queue++;
                        q[x].pop();

            }
            cout << "Closed" << '\n';
        }
    }
}
