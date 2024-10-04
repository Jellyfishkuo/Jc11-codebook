const char sep = '/';     // 分數的分隔符
bool div0;      // 要記得適時歸零
using ll = long long;

struct Rational {
	ll p, q;
  
	Rational(ll a=0, ll b=1) {
		p = a, q = b;
    reduce();
	}
  
	Rational(string s) {
		if(s.find(sep) == string::npos) {
			p = stoll(s);
			q = 1;
		} else {
			p = stoll(s.substr(0, s.find(sep)));
			q = stoll(s.substr(s.find(sep)+1));
		}
		reduce();
	}
  
	void reduce() {
		ll t = abs(__gcd(p, q));
    if(t == 0) {
      div0 = true;
      return;
    }
		p /= t, q /= t;
		if(q < 0) p = -p, q = -q;
		return;
	}
  
	string toString() {
		if(q == 0) {
			div0 = true;
			return "INVALID";
		}
		if(p%q == 0) return to_string(p/q);
		return to_string(p) + sep + to_string(q);
	}
  
	friend istream& operator>>(
		istream& i, Rational& r) {
		string s;
		i >> s;
    r = Rational(s);
		return i;
	}
  
	friend ostream& operator<<(
		ostream& o, Rational r) {
    o << r.toString();
		return o;
	}
};

Rational operator+(Rational x, Rational y) {
	ll t = abs(__gcd(x.q, y.q));
  if(t == 0) return Rational(0, 0);
	return Rational(
		y.q/t*x.p + x.q/t*y.p, x.q/t*y.q);
}

Rational operator-(Rational x, Rational y) {
	return x + Rational(-y.p, y.q);
}

Rational operator*(Rational x, Rational y) {
	return Rational(x.p*y.p, x.q*y.q);
}

Rational operator/(Rational x, Rational y) {
	return x * Rational(y.q, y.p);
}