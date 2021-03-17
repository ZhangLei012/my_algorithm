// 1563. 石子游戏 V
// 几块石子 排成一行 ，每块石子都有一个关联值，关联值为整数，由数组 stoneValue 给出。
// 游戏中的每一轮：Alice 会将这行石子分成两个 非空行（即，左侧行和右侧行）；Bob 负责计算每一行的值，即此行中所有石子的值的总和。Bob 会丢弃值最大的行，Alice 的得分为剩下那行的值（每轮累加）。如果两行的值相等，Bob 让 Alice 决定丢弃哪一行。下一轮从剩下的那一行开始。
// 只 剩下一块石子 时，游戏结束。Alice 的分数最初为 0 。
// 返回 Alice 能够获得的最大分数 。
//1.O(n^3)解法
class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        //dp[i][j]表示从nums[i]到nums[j]所获得的最大分数
        int sum[510][510];
        int n = stoneValue.size();
        for(int i = 0; i < n; i++){
            sum[i][i] = stoneValue[i];
            for(int j = i + 1; j < n; j++){
                sum[i][j] = sum[i][j-1] + stoneValue[j];
                sum[j][i] = sum[i][j];
            }
        }

        int dp[510][510];
        memset(dp, 0, sizeof(dp));

        for(int l = 2; l <= n; l++){
            for(int i = 0; i + l - 1< n; i++){
                for(int k = i; k < i + l - 1; k++){
                    if(sum[i][k] < sum[k+1][i+l-1]){
                        dp[i][i+l-1] = max(dp[i][i+l-1], dp[i][k] + sum[i][k]);
                    }
                    else if(sum[i][k] == sum[k+1][i+l-1]){
                        dp[i][i+l-1] = max({dp[i][i+l-1], dp[i][k] + sum[i][k], dp[k+1][i+l-1] + sum[k+1][i+l-1]});                        
                    }else{
                        dp[i][i+l-1] = max({dp[i][i+l-1], dp[k+1][i+l-1] + sum[k+1][i+l-1]}); 
                    }
                }
            }
        }
        return dp[0][n-1];
    }
};

//2.O(n^2)算法，在计算的过程中为下一次迭代考虑，计算出dp[i][k]+sum[i][k]的最大值，后面可以直接用。
int stoneGameV(vector<int>& stoneValue) {
    int sum[510][510];
    int dp[510][510];//dp[i][j]表示从nums[i]到nums[j]所获得的最大分数
    memset(dp, 0, sizeof(dp));
    int maxl[510][510];//maxl[i][j]表示max{dp[i][k]+sum[i][k]}, k=i,i+1,...,j
    memset(maxl, 0, sizeof(maxl));
    int maxr[510][510];//maxr[i][j]表示max{dp[k][j]+sum[k][j]}, k=i,i+1,...,j
    memset(maxr, 0, sizeof(maxr));
    int n = stoneValue.size();
    for(int i = 0; i < n; i++){
        sum[i][i] = stoneValue[i];
        maxl[i][i] = stoneValue[i];
        maxr[i][i] = stoneValue[i];
        for(int j = i + 1; j < n; j++){
            sum[i][j] = sum[i][j-1] + stoneValue[j];
            sum[j][i] = sum[i][j];
        }
    }
    int g[510][510];//g[i][j]=mid表示mid是第一个sum[i][mid] >= sum[mid+1][j]的mid
    memset(g, 0, sizeof(g));
    for(int i = 0; i < n; i++){
        g[i][i] = i;
        for(int j = i+1; j < n; j++){
            int mid = g[i][j-1];
            while(mid < j && sum[i][mid] < sum[mid+1][j]){
                mid++;
            }
            g[i][j] = mid;
        }
    }

    for(int l = 2; l <= n; l++){
        for(int i = 0; i + l - 1 < n; i++){
            int j = i + l - 1;
            int mid = g[i][j];//sum[i][mid] >= sum[mid+1][j]
            if(mid == j){
                //在最后面，就只考虑前面了
                dp[i][j] = max(dp[i][j], maxl[i][mid-1]);   
            }else{
                int suml = sum[i][mid];
                int sumr = sum[mid+1][j];
                if(suml == sumr){
                    dp[i][j] = max(dp[i][j], maxl[i][mid]);//用上maxl
                    dp[i][j] = max(dp[i][j], maxr[mid+1][j]);//用上maxr
                }else{
                    if(mid > i){
                        //mid是第一个满足sum[i][mid] >= sum[mid+1][j]的位置，所以mid-1肯定不满足
                        dp[i][j] = max(dp[i][j], maxl[i][mid-1]);
                    }                    
                    dp[i][j] = max(dp[i][j], maxr[mid+1][j]);
                }
            }             
            int v = dp[i][j] + sum[i][j];
            maxl[i][j] = max(maxl[i][j-1], v);
            maxr[i][j] = max(maxr[i+1][j], v);      
        }
    }
    return dp[0][n-1];
}

//2.错误解法，未通过[98,77,24,49,6,12,2,44,51,96]，结果因为330，二分在逻辑上应该是不正确的。
 int stoneGameV(vector<int>& stoneValue) {
        //dp[i][j]表示从nums[i]到nums[j]所获得的最大分数
        int sum[510][510];
        int presum[510];
        int n = stoneValue.size();
        for(int i = 0; i < n; i++){
            sum[i][i] = stoneValue[i];
            for(int j = i + 1; j < n; j++){
                sum[i][j] = sum[i][j-1] + stoneValue[j];
                sum[j][i] = sum[i][j];
            }
        }

        int dp[510][510];
        memset(dp, 0, sizeof(dp));

        for(int l = 2; l <= n; l++){
            for(int i = 0; i + l - 1< n; i++){
                int low = i;
                int high = i + l - 1;
                int pos = high; //pos第一个大于等于的下标
                while(low <= high){
                    int mid = (low + high) / 2;
                    if(sum[i][mid] < sum[mid+1][i+l-1]){
                        low = mid + 1;
                    }else{
                        pos = mid;
                        high = mid - 1;
                    }
                }

                if(pos == i){
                    dp[i][i+l-1] = dp[i+1][i+l-1] + sum[i+1][i+l-1];
                }else{
                    //用pos
                    if(sum[i][pos] == sum[pos+1][i+l-1]){
                        dp[i][i+l-1] = max({dp[i][pos] + sum[i][pos], dp[pos+1][i+l-1] + sum[pos+1][i+l-1]});
                    }else if(sum[i][pos] > sum[pos+1][i+l-1]){
                        if(pos < i + l - 1){
                            dp[i][i+l-1] = dp[pos+1][i+l-1] + sum[pos+1][i+l-1];
                        }
                    }
                    //不用pos
                    dp[i][i+l-1] = max(dp[i][i+l-1], dp[i][pos-1] + sum[i][pos-1]);
                }
                //cout<<i<<" "<<i+l-1<<" "<<pos<<" "<<dp[i][i+l-1]<<endl;
            }
        }
        return dp[0][n-1];
    }

//2021.03.16
//求一个字符串的子回文序列数
//dp[i][j]表示i到j之间的子回文序列数
//s[i] != s[j] --> dp[i][j] = dp[i][j-1] - dp[i+1][j-1] + dp[i+1][j] - dp[i+1][j-1] + dp[i+1][j-1]
//s[i] == s[j] --> 若s[i],s[j]之间没有和s[i]/s[j]相同的字符dp[i][j] = 2 * dp[i+1][j-1] + 2;
//             --> 有1个相同的字符 dp[i][j] = 2 * dp[i+1][j-1] + 1
//             --> 有2个或者以上相同的字符 dp[i][j] = 2 * dp[i+1][j-1] - dp[l+1][r-1]
class Solution {
public:
    int countPalindromicSubsequences(string S) {
        int n = S.size();
        long long int dp[n+1][n+1];
        memset(dp, 0, sizeof(dp));
        vector<vector<int>> pos(256, vector<int>(0));
        for(int i = 0; i < n; i++){
            dp[i][i] = 1;
        }
        long long int mod = 1000000007;
        for(int len = 2; len <= n; len++){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len - 1;
                if(S[i] == S[j]){
                    int l = i+1;
                    int r = j-1;
                    while(l <= r && S[l] != S[i]){
                        l++;
                    }
                    while(l <= r && S[r] != S[j]){
                        r--;
                    }
                    if(l > r){
                        dp[i][j] = 2 * dp[i+1][j-1] + 2;
                    }else if(l == r){
                        dp[i][j] = 2 * dp[i+1][j-1] + 1;
                    }else{
                        dp[i][j] = 2 * dp[i+1][j-1] - dp[l+1][r-1];
                    }
                }else{
                    dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
                }
                dp[i][j] = (dp[i][j] + mod) % mod;
                //cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
            }
        }
        return dp[0][n-1];
    }
};