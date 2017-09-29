#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
/*
目前可用的用法：
(1)BigInteger * BigInteger
(2)BigInteger * int (or long long)
(3)BignInteger + BigInteger
除法明天再說
減法...別逼我...
*/
using namespace std;

struct BigInteger {
  static const int BASE = 100000000;
  static const int WIDTH = 8;
  vector<long long> s;

  BigInteger(long long num = 0) { *this = num; } // 构造函数
  BigInteger operator = (long long num) { // 赋值运算符
    s.clear();
    do {
      s.push_back(num % BASE);
      num /= BASE;
    } while(num > 0);
    return *this;
  }
  BigInteger operator = (const string& str) { // 赋值运算符
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
      int end = str.length() - i*WIDTH;
      int start = max(0, end - WIDTH);
      sscanf(str.substr(start, end-start).c_str(), "%d", &x);
      s.push_back(x);
    }
    return *this;
  }
  BigInteger operator + (const BigInteger& b) const {
    BigInteger c;
    c.s.clear();
    for(int i = 0, g = 0; ; i++) {
      if(g == 0 && i >= s.size() && i >= b.s.size()) break;
      int x = g;
      if(i < s.size()) x += s[i];
      if(i < b.s.size()) x += b.s[i];
      c.s.push_back(x % BASE);
      g = x / BASE;
    }
    return c;
  }
  BigInteger operator * (const BigInteger& b) const{
	  BigInteger c;
	  c.s.resize(s.size(), 0);
	  for(int j = 0; j < b.s.size(); j++){
		  long long x = 0;
		  for(int i = 0;; i++){
			  if(x == 0 && i >= s.size()) break;
			  if(i < s.size()){ 
					x += s[i]*b.s[j];
			  }
			  if(i+j < c.s.size()) c.s[i+j] = x % BASE;
			  else c.s.push_back(x % BASE);
			  x /= BASE;
		  }
	  }
	  return c;
  }
  BigInteger operator * (const long long& sum) const{
	  BigInteger c = sum;
	  return *this * c;
  }
 /* BigInteger operator / (const int& b) const{
    BigInteger c;
    c.s.clear();
    vector<int> temp;
    long long x = 0;
    for(int i = s.size()-1; i >= 0; i--){
	x = x * BASE + s[i];
	temp.push_back(x / b);
	x  = x % b;
    }
    for(int i = temp.size()-1; i >= 0; i--){
	    c.s.push_back(temp[i]);
    }
    return c;
  }*/
	


};

ostream& operator << (ostream &out, const BigInteger& x) {
	//最後一個不一定是八個數字，所以要先輸出
  out << x.s.back();
  for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[20];
    sprintf(buf, "%08d", x.s[i]);
    for(int j = 0; j < strlen(buf); j++) out << buf[j];
  }
  return out;
}

istream& operator >> (istream &in, BigInteger& x) {
  string s;
  if(!(in >> s)) return in;
  x = s;
  return in;
}

int  main(){
    BigInteger A, i;
    while(cin>>A>>i){
    	cout<<A*i<<endl;
    }
    return 0;
}
