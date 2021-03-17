//长度为n厘米的蜡烛，随机将蜡烛分成两段，每段的距离都为整数，点燃两段蜡烛，每分钟燃烧的长度为1厘米，等一段的蜡烛燃烧完后，若剩余一段蜡烛长度大于1则再进行一次随机分割，同时点燃分割出来的一段蜡烛。之后便等待蜡烛燃烧结束。
//求蜡烛燃烧结束时间的数学期望。n为4时，期望为2.
#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
//平心静气！
double dp[10010][3];
double dfs(int n, int depth) {
	if (n == 1) {
		return 1;
	}
	if (dp[n][depth] != 0) {
		return dp[n][depth];
	}
	double t = 0;
	for (int i = 1; i < n; i++) {
		int left = n - i;
		if (i < left) {
			t += 1.0 / (n-1) * (i + dfs(left - i, depth - 1));
		}
		else if (i == left) {
			t += 1.0 / (n-1) * i;
		}
		else {
			t += 1.0 / (n-1) * (dfs(i - left, depth - 1) + left);
		}
	}
	dp[n][depth] = t;
	//cout << n << " " << depth << " "<<t<<endl;
	return t;
}
int main() {
	int n;
	cin >> n;
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < 10010; i++) {
		dp[i][0] = i;
	}
	for (int j = 1; j <= 2; j++) {
	}
	cout << dfs(n, 2) << endl;
	return 0;
}