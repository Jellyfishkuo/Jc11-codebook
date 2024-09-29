using ll = long long;

struct Rational {
	ll p, q;

	Rational(ll a=0, ll b=1) {
		p = a, q = b;
		reduce();
	}

	void reduce() {
		ll t = abs(__gcd(p, q));
		p /= t, q /= t;
		if(q < 0) p = -p, q = -q;
	}
	
	friend istream& operator>>(
		istream& i, Rational& r) {
		string s;
		i >> s;
		if(s.find('/') == string::npos) {
			r.p = stoi(s);
			r.q = 1;
		} else {
			r.p = stoi(s.substr(0, s.find('/')));
			r.q = stoi(s.substr(s.find('/')+1));
		}
		r.reduce();
		return i;
	}

	friend ostream& operator<<(
		ostream& o, Rational r) {
		if(r.p%r.q == 0) o << r.p/r.q;
		else o << r.p << "/" << r.q;
		return o;
	}
};

Rational operator+(Rational x, Rational y) {
	ll t = abs(__gcd(x.q, y.q));
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