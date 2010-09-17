using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

template <class T> string toStr(const T &x){ stringstream s; s << x; return s.str(); }
template <class T> int toInt(const T &x){ stringstream s; s << x; int r; s >> r; return r; }

#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define foreach(x, v) for (typeof (v).begin() x = (v).begin(); x != (v).end(); ++x)
#define D(x) cout << #x " = " << (x) << endl

const int N = 50005;
// Begins Suffix Arrays implementation
// O(n log n) - Manber and Myers algorithm

//Usage:
// Fill str with the characters of the string.
// Call SuffixSort(n), where n is the length of the string stored in str.
// That's it!

//Output:
// pos = The suffix array. Contains the n suffixes of str sorted in lexicographical order.
//       Each suffix is represented as a single integer (the position of str where it starts).
// rank = The inverse of the suffix array. rank[i] = the index of the suffix str[i..n)
//        in the pos array. (In other words, pos[i] = k <==> rank[k] = i)
//        With this array, you can compare two suffixes in O(1): Suffix str[i..n) is smaller
//        than str[j..n) if and only if rank[i] < rank[j]

int str[N]; //input
int rank[N], pos[N]; //output
int cnt[N], next[N]; //internal
bool bh[N], b2h[N];

bool smaller_first_char(int a, int b){
    return str[a] < str[b];
}

void SuffixSort(int n){
    //sort suffixes according to their first character
    for (int i=0; i<n; ++i){
        pos[i] = i;
    }
    sort(pos, pos + n, smaller_first_char);
    //{pos contains the list of suffixes sorted by their first character}

    for (int i=0; i<n; ++i){
        bh[i] = i == 0 || str[pos[i]] != str[pos[i-1]];
        b2h[i] = false;
    }

    for (int h = 1; h < n; h <<= 1){
        //{bh[i] == false if the first h characters of pos[i-1] == the first h characters of pos[i]}
        int buckets = 0;
        for (int i=0, j; i < n; i = j){
            j = i + 1;
            while (j < n && !bh[j]) j++;
            next[i] = j;
            buckets++;
        }
        if (buckets == n) break; // We are done! Lucky bastards!
        //{suffixes are separted in buckets containing strings starting with the same h characters}

        for (int i = 0; i < n; i = next[i]){
            cnt[i] = 0;
            for (int j = i; j < next[i]; ++j){
                rank[pos[j]] = i;
            }
        }

        cnt[rank[n - h]]++;
        b2h[rank[n - h]] = true;
        for (int i = 0; i < n; i = next[i]){
            for (int j = i; j < next[i]; ++j){
                int s = pos[j] - h;
                if (s >= 0){
                    int head = rank[s];
                    rank[s] = head + cnt[head]++;
                    b2h[rank[s]] = true;
                }
            }
            for (int j = i; j < next[i]; ++j){
                int s = pos[j] - h;
                if (s >= 0 && b2h[rank[s]]){
                    for (int k = rank[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
                }
            }
        }
        for (int i=0; i<n; ++i){
            pos[rank[i]] = i;
            bh[i] |= b2h[i];
        }
    }
    for (int i=0; i<n; ++i){
        rank[pos[i]] = i;
    }
}
// End of suffix array algorithm

// Algorithm GetHeight
// input: A text A and its suffix array Pos
//    1 for i:=1 to n do
//    2     Rank[Pos[i]] := i
//    3 od
//    4 h:=0
//    5 for i:=1 to n do
//    6     if Rank[i] > 1 then
//    7        k := Pos[Rank[i]-1]
//    8        while A[i+h] = A[j+h] do
//    9           h := h+1
//    10       od
//    11       Height[Rank[i]] := h
//    12       if h > 0 then h := h-1 fi
//    13    fi
//    14 od
int height[N];
// height[i] = length of the longest common prefix of suffix pos[i] and suffix pos[i-1]
// height[0] = 0
void getHeight(int n){
    for (int i=0; i<n; ++i) rank[pos[i]] = i;
    height[0] = 0;
    for (int i=0, h=0; i<n; ++i){
        if (rank[i] > 0){
            int j = pos[rank[i]-1];
            while (i + h < n && j + h < n && str[i+h] == str[j+h]) h++;
            height[rank[i]] = h;
            if (h > 0) h--;
        }
    }
}

// Gets the longest common prefix from Sx and Sy in a string of lenght n
// lcp(x,y) = min(lcp(x,x+1), lcp(x+1, x+2), ... , lcp(y-1, y))
// Runs in O(|x-y|)
int lcp(int x, int y, int n){
    if(x > y) return lcp(y,x,n);
    if(x == y) return n-pos[x];
    int lc = n+1;
    for(int i = x+1; i<=y; ++i) if (height[i] != 0) lc = min(lc, height[i]); else return 0;
    return lc;
}


string s;

void print_suffix_array(){
    puts("Suffix Array");
    int n = s.size();
    string tmp;
    for(int i=0;i<n;++i){
        tmp = s.substr(pos[i]);
        printf("pos[%d] = %2d \t suffix = %s \t height[%d] = %d\n",i,pos[i],tmp.c_str(), i, height[i]);
    }
}

// You need a string W that represents the pattern
// Not really tested. Pseudo-tested
int match_prefix(int n){
    string W; // Fill this outside
    if(W[0] < s[pos[0]]) return -1; // Is not here!
    if(W[0] > s[pos[n-1]]) return -1; // Not here too!
    if(W == s.substr(pos[0])) return pos[0];
    // Binary search for the W pattern
    int l = 0, r = n-1, m;
    while(r-l > 1){
        m = (l+r)/2;
        if(W >= s.substr(pos[m]))
            l = m;
        else
            r = m;
    }
    // r is the i-sth smallest suffix
    // that means that pos[r] is the actual index
    if(W != s.substr(pos[r], W.size())) return -1; // not here at all!
    printf("Matched at %d\n", r);
    return pos[r];
}

// Get the biggest repeated substring and how many times it appears
// First, get the biggest repeated string (it's, obviously the biggest height[i])
// Then count it's repetitions
void get_the_biggest_repeated_substring(){
  int n = s.size();
  for(int i=0;i<n;++i) str[i] = s[i];
  SuffixSort(n);
  getHeight(n);
  int longest = 0, position = -1;
  for(int i=1;i<n;++i){
    if(longest < height[i]) { longest = height[i]; position = i - 1;}
  }
  int cnt = 1;
  for(int i=position+1;i<n;++i){
    if(height[i] >= longest) cnt++;
    else break;
  }
  if(longest != 0)
    cout << s.substr(pos[position], longest) << " " << cnt << endl;
  else
    puts("No repetitions found!");
}

// If you have the i-th smaller suffix, Si, it's length will be |Si| = n - pos[i]
// Now, height[i] stores the number of common letters between Si and Si (s.substr(pos[i]) and s.substr(pos[i-1]))
// so, you have |Si| - height[i] different strings from these two suffixes => n - pos[i] - height[i]
void number_of_different_substrings(){
    int n = s.size();
    //for (int i=0; i<n; ++i) str[i] = s[i]; uncomment if reading s and not str
    //Build suffix array and height array
    int ans = 0;
    for(int i=0;i<n;++i) ans += n-pos[i]-height[i];
    cout << ans << endl;
}

// Number of substrings that appear at least twice in the text.
// The trick is that all 'spare' substrings that can give us 
// Lcp(i - 1, i) can be obtained by Lcp(i - 2, i - 1) 
// due to the ordered nature of our array. And the overall answer is:
// Lcp(0, 1) + Sum(max[0, Lcp(i, i - 1) - Lcp(i - 2, i - 1)]), 2 <= i < n
void number_of_repeated_substrings(){
    int n = s.size();
    if(n==1){ cout << 0 << endl;  return; }
    //for (int i=0; i<n; ++i) str[i] = s[i]; uncomment if reading s and not str
    //build suffix array and height array
    int cnt = height[1];
    for(int i=2;i<n;++i){
        cnt += max(0, height[i] - height[i-1]);
    }
    cout << cnt << endl;  
}

// Given a string s and an int m, find the size
// of the biggest substring repeated m times (find the rightmost pos)
// if a string is repeated m+1 times, then it's repeated m times too

// The answer is the maximum, over i, of the longest common prefix
// between suffix i+m-1 in the sorted array.
// remember that the lcp(x,y) = min(lcp(x,x+1), lcp(x+1, x+2), ... , lcp(y-1, y))
void repeated_m_times(int m){
    int n = strlen(str);//s.size();
    //for (int i=0; i<n; ++i) str[i] = ss[i];
    SuffixSort(n);
    getHeight(n);
    int length = 0, position = -1, t;
    for(int i=0;i<=n-m;++i){
        if((t=lcp(i,i+m-1,n)) > length){
            length = t;
            position = pos[i];
        }else if(t == length) { position = max(position, pos[i]); }
    }

    // Here you'll get the rightmost position (that means, the last time the substring appears)
    for(int i = 0; i < n; ){
        if(pos[i] + length > n) {++i; continue;}
        int ps = 0, j = i+1;
        while(j<n && height[j] >= length){
            ps = max(ps,pos[j]);
            j++;
        }
        if(j - i >= m) position = max(position, ps);
        i = j;
    }
    if(length != 0)
        printf("%d %d\n", length, position);
    else
        puts("none");
}
