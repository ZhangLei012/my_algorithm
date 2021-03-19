//992. K 个不同整数的子数组
//给定一个正整数数组 A，如果 A 的某个子数组中不同整数的个数恰好为 K，则称 A 的这个连续、不一定不同的子数组为好子数组。
//（例如，[1,2,3,1,2] 中有 3 个不同的整数：1，2，以及 3。）
//返回 A 中好子数组的数目。
class Window{
private:
    int uniq;
    unordered_map<int, int> rec;
public:
    Window(){
        uniq = 0;
    }
    void add(int x){
        if(rec[x] == 0){
            uniq++;
        }
        rec[x]++;
    }
    void remove(int x){
        rec[x]--;
        if(rec[x] == 0){
            uniq--;
        }
    }
    int unique(){
        return uniq;
    }
};
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& A, int K) {
        int left1 = 0;
        int left2 = 0;
        Window w1, w2;
        int ret = 0;
        for(int i = 0; i < A.size(); i++){
            w1.add(A[i]);
            w2.add(A[i]);
            while(w1.unique() > K){
                w1.remove(A[left1]);
                left1++;
            }

            while(w2.unique() >= K){
                w2.remove(A[left2]);
                left2++;
            }

            ret += left2 - left1;
        }
        return ret;
    }
};

//最小覆盖子串问题，使用滑动串口特别好理解，也不容易出错。思路：先通过面向对象的方式定义出窗口来，方便操作。
class Window{
private:
    int count[256];
    int cur_count[256];
    int covered_char_num;
public:
    Window(string s) : covered_char_num(0) {
        memset(count, 0, sizeof(count));
        for(auto c : s){
            count[c]++;
        }

        memset(cur_count, 0, sizeof(cur_count));
    }

    void add(char c){
        cur_count[c]++;
        if(cur_count[c] == count[c]){
            covered_char_num++;
        }
    }

    void remove(char c){
        if(cur_count[c] == count[c]){
            covered_char_num--;
        }
        cur_count[c]--;
    }

    int get_covered_char_num(){
        return covered_char_num;
    }
};
class Solution {
public:
    //求在s的所有子串中覆盖t的长度最小的子串
    string minWindow(string s, string t) {
        if(s.size() < t.size()){
            return "";
        }
        Window w1(t);
        int left = 0;
        int t_unique = 0;
        int t_count[256];
        memset(t_count, 0, sizeof(t_count));
        for(auto c : t){
            t_count[c]++;
            if(t_count[c] == 1){
                t_unique++;
            }
        }
        int min_len = s.size();
        int start_index = -1;
        for(int i = 0; i < s.size(); i++){
            w1.add(s[i]);
            while(w1.get_covered_char_num() >= t_unique){
                if(i - left + 1 <= min_len){
                    min_len = i - left + 1;
                    start_index = left;
                }
                w1.remove(s[left]);
                left++;
            }
        }
        return start_index == -1 ? "" :s.substr(start_index, min_len);
    }
};

//2021.3.18 
//209. 长度最小的子数组
//给定一个含有 n 个正整数的数组和一个正整数 target 。
//找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
class Window{
private:
    int sum;
public:
    Window():sum(0){
    }
    void add(int x){
        sum += x;
    }
    void remove(int x){
        sum -= x;
    }
    int inWindowSum(){
        return sum;
    }
};
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        Window w;
        int ret = nums.size() + 1;
        for(int i = 0; i < nums.size(); i++){
            w.add(nums[i]);
            while(w.inWindowSum() >= target){
                ret = min(ret, i - left + 1);
                w.remove(nums[left]);
                left++;
            }
        }
        return ret == nums.size() + 1 ? 0 : ret;
    }
};


//替换后的最长重复子串
//给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
//注意：字符串长度 和 k 不会超过 104。
//法1：每次只考虑一种字符
class CharWindow{
public:
    CharWindow(char c):c_(c), c_count_(0), window_size_(0){};
    void add(char x){
        if(c_ == x){
            c_count_++;
        }
        window_size_++;
    }
    void remove(char x){
        if(c_ == x){
            c_count_--;
        }
        window_size_--;
    }
    int getWindowSize(){
        return window_size_;
    }
    int neededReplaceTimes(){
        return window_size_ - c_count_;
    }
private:
    char c_;
    int c_count_;
    int window_size_;
};
class Solution {
public:
    int characterReplacement(string s, int k) {
        int ret = 0;
        for(char c = 'A'; c <= 'Z'; c++){
            CharWindow win(c);
            int win_left = 0;
            for(int i = 0; i < s.size(); i++){
                win.add(s[i]);
                while(win.neededReplaceTimes() > k){
                    win.remove(s[win_left]);
                    win_left++;
                }
                ret = max(ret, win.getWindowSize());
            }
        }
        return ret;
    }
};

//法2：同时考虑多种字符
class CharWindow{
public:
    CharWindow():max_count(0), window_size_(0){
        memset(char_count, 0, sizeof(char_count));
    };
    void add(char x){
        char_count[x]++;
        window_size_++;
        if(char_count[x] > max_count){
            max_count = char_count[x];
        }
    }
    void remove(char x){
        char_count[x]--;
        window_size_--;
        if(char_count[x] == max_count - 1){
            max_count = *max_element(char_count, char_count + 256);
        }
    }
    int getWindowSize(){
        return window_size_;
    }
    int neededReplaceTimes(){
        return window_size_ - max_count;
    }
private:
    int max_count;
    int char_count[256];
    int window_size_;
};
class Solution {
public:
    int characterReplacement(string s, int k) {
        int ret = 0;
        CharWindow win;
        int left = 0;
        for(int i = 0; i < s.size(); i++){
            win.add(s[i]);
            while(win.neededReplaceTimes() > k){
                win.remove(s[left]);
                left++;
            }
            ret = max(ret, win.getWindowSize());
        }
        return ret;
    }
};