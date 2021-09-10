1. Extended Eucleadean Algorithm

ax + by = gcd(a,b), find gcd(a,b), x0, y0  

```
ll gcd, x, y;
void ext_gcd(ll a, ll b){
    if(b==0){x=1; y=0; gcd = a; return;}
    ext_gcd(b,a%b);
    ll t1 = y;
    ll t2 = x - (a/b)*y;
    x = t1; y = t2;
}

-------

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

pair<int,int> ext_gcd(int a,int b){
    if(b){
        auto tmp = ext_gcd(b, a%b);
        return {tmp.second, tmp.first - (a/b) * tmp.second};
    } else return {1, 0};
}

```

modular inverse with ext_gcd:  
--> find x such that ax == 1 (mod M)  
--> Diophantane equation: ax + My = 1  
--> modular inverse: mod_inv = ext_gcd(a,M)  
--> make it always positive: mod_inv = ((ext_gcd(a,M) + M) % M)  

```
ll mod_inv(ll a, ll M){
    return ((ext_gcd(a,M) + M) % M);
}

int mod_inv(int a, int M){
    return (ext_gcd(a, M).first + M) % M;
}
```

2. Fermat's little theorem  

P is a prime number, then for any integer a, a^P == a (mod P)  

if a is not divisble by P, then a^(P-1) == 1(modP)  

modular inverse with FLT:
ax == 1 (mod P)
--> x == a^(-1) (mod P)
--> a^(P-2) == a^(-1) (mod P)
--> mod_inv: a^(P-2)

