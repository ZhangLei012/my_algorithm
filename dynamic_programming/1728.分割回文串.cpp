
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