ll GCD, x, y;
void ext_gcd(ll a, ll b) {
    if (b == 0) {
        x = 1;
        y = 0;
        GCD = a;
        return;
    }
    ext_gcd(b, a % b);
    ll t1 = y;
    ll t2 = x - (a / b) * y;
    x = t1;
    y = t2;
}

ll mod_inv(ll a, ll M) {
    ext_gcd(a, M);
    if (GCD != 1) return -1;

    while(x<0){
        x += M;
    }
    x %= M;
    return x;
}
