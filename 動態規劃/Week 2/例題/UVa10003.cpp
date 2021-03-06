#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
#define MAX_N 49
#define INF 1E9
using namespace std;
/* 
 *  ｜－｜－－－｜－－｜－－－－｜
 *  
 * 如果在4的位置下去的話，會變成....
 *  |－｜－－－｜　　　　　　｜－－｜－－－－｜
 * 
 * 問題就轉換成計算這兩根棍子的最佳切割成本了。
 * dp(i, j) 代表從第i個位置到第j個位置間的木棍的最佳切割成本，則：
 * dp(i, j) = min( dp(i, j), L[j] - L[i] + dp(i, k) + dp(k, j) )
 */
int L[MAX_N+2], length, N;
int dp[MAX_N+2][MAX_N+2];
void init(){
	for(int i = 0; i < N+2; i++){
		for(int j = 0; j < N+2; j++){
			dp[i][j] = INF;
		}
		if(i < N+1) dp[i][i+1] = 0;
	}
}
int main(){
	while(cin>>length){
		if(length == 0) break;
		cin>>N;
		L[0] = 0, L[N+1] = length;
		for(int i = 1; i <= N; i++){
			scanf("%d\n", L+i);
		}
		init();
		for(int k = 2; k < N+2; k++){
			for(int i = 0; i+k < N+2; i++){
				int j = i+k;
				for(int m = i+1; m < j; m++){
					dp[i][j] = min(dp[i][j], L[j] - L[i] + dp[i][m]+dp[m][j]);
				}
			}
		}
		printf("The minimum cutting is %d.\n", dp[0][N+1]);
	}
	return 0;
}
			
