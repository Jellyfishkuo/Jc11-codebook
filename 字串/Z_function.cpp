const int maxn = 1e6 + 10;

int z[maxn];    // s[0:z[i]) = s[i:i+z[i])
string s;

void makeZ() {   // z[0] = 0
  for(int i=1, l=0, r=0; i<s.length(); i++) {
    if(i<=r && z[i-l]<r-i+1) z[i] = z[i-l];
    else {
      z[i] = max(0, r-i+1);
      while(i+z[i]<s.length() && s[z[i]]==s[i+z[i]]) z[i]++;
    }
    if(i+z[i]-1 > r) l = i, r = i+z[i]-1;
  }
}