/*Một siêu thị tổ chức việc thanh toán cho khách hàng với bốn quầy thu ngân và bốn hàng
khách (được đánh số 1,2,3,4). Hoạt động thanh toán được thực hiện như mô tả sau:
- Khi có yêu cầu thanh toán, một nhân viên điều phối thông thường sẽ hướng dẫn
khách hàng vào cuối một trong các hàng theo nguyên tắc phân phối round-robin
(gửi vào lần lượt từng hàng và quay vòng lại: VD: 1,2,3,4,1,2,3,4,...). Khách hàng
được phát một mã số để tiến hành gọi khi checkout. Mã số khách hàng là một số
nguyên, tăng dần cho từng khách hàng mới (bắt đầu từ 1).
o Nhân viên điều phối tốt có thể hướng dẫn khách hàng vào hàng có ít
người nhất. Việc điều phối này không ảnh hưởng đến thứ tự phân phối của
nhân viên thông thường (hàng tiếp theo trong phân phối round-robin sẽ giữ
nguyên).

- Nhân viên thu ngân tại quầy thanh toán thứ i sẽ gọi lần lượt các khách hàng trong
hàng thứ i để thực hiện checkout.
- Tùy thuộc vào số lượng khách hàng mà siêu thị quyết định mở thêm một quầy thu
ngân mới (cùng với hàng khách mới) hoặc đóng một quầy thu ngân.
o Trong trường hợp mở thêm quầy thu ngân mới, quầy mới sẽ được đặt cuối
cùng trong danh sách quầy. Số hiệu quầy mới và hàng tương ứng sẽ được

đặt tăng dần, bắt đầu từ 5. Lưu ý hàng tiếp theo trong phân phối round-
robin có thể thay đổi khi mở thêm quầy mới (VD. có 4 hàng và đã phân

phối đến hàng thứ 4, khi thêm vào quầy mới vào cuối danh sách, hàng mới
sẽ là hàng tiếp theo trong phân phối).
o Trong trường hợp đóng một quầy thu ngân, số hiệu quầy thu ngân và hàng
còn lại sẽ được giữ nguyên. Lần lượt từng khách hàng trong hàng tương
ứng với quầy bị đóng(thứ tự từ đầu đến cuối hàng) sẽ được chuyển sang các
hàng còn lại theo nguyên tắc round-robin, bắt đầu từ quầy tiếp theo trong
phân phối này. Lưu ý hàng bị đóng có thể chính là hàng tiếp theo trong
phân phối round-robin, khi đó cần dịch chuyển tiếp tục giá trị này trước khi
đóng quầy.
Chỉ được đóng quầy khi số lượng quầy >= 2.

    
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
