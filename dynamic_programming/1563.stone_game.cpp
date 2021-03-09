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