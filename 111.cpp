#include <iostream>
using namespace std;
#include <string>
#include <bits/stdc++.h>
#define SIZEBIT 4096
class LongInt{
bool arr[SIZEBIT];

private:



public:

//constructor
LongInt() {
 for(int i=0; i<SIZEBIT; ++i)
    {
        arr[i] = false;
    }
}



//shifting all array to the left
static LongInt  shiftingL(LongInt x, int y){ 
    LongInt k;
    k.arr[SIZEBIT-1-y] = true;
    LongInt res =x*k;
    return res;
};


//shifting all array to the right
static LongInt shiftingR(LongInt x, int y){

    for(int i=0; i<SIZEBIT-y; ++i){
        x.arr[SIZEBIT-1-i]=x.arr[SIZEBIT-1-y-i];
    }
    return x;
};


//converting from string to LongInt
void converting(string x){
    int size = x.size();
    for(int i = 0; i<size; ++i)
    {
        if(x[size-i-1]=='1'){
            arr[SIZEBIT-1-i]=true;
        }
    }
};


//binary addition (bitbybit)
LongInt operator+ (const LongInt& x) const{
    LongInt res;
    bool temp;
    for(int i=0; i<SIZEBIT; ++i)
    {
        res.arr[SIZEBIT-1-i] = (this->arr[SIZEBIT-1-i] ^ x.arr[SIZEBIT-1-i]) ^ temp;
        temp = ((this->arr[SIZEBIT-1-i] & x.arr[SIZEBIT-1-i]) | (this->arr[SIZEBIT-1-i] & temp)) | (x.arr[SIZEBIT-1-i] & temp); 
    }
    return res;
}
// ((this->arr[SIZEBIT-1-i] & x.arr[SIZEBIT-1-i]) | (this->arr[SIZEBIT-1-i] & temp)) | (x.arr[SIZEBIT-1-i] & temp)
// (this->arr[SIZEBIT-1-i] | x.arr[SIZEBIT-1-i]) & !(this->arr[SIZEBIT-1-i] & x.arr[SIZEBIT-1-i])


//returning 1 if 1st number is bigger then 2nd
bool comparison(const LongInt& x) const{
    bool res;
    for(int i=0; i<SIZEBIT;++i)   
    {
        res = ((this->arr[i] ^ x.arr[i]));
        if(res==1)
        {
            if(x.arr[i]==true){ 
                return res=false;
            }
            else
            {
                return res=true;
            }
        }else{
            res = true;
        }
    }
    return res;
} 


//binary diversion bitbybit
LongInt operator- (const LongInt& x) const{
    LongInt res;
    bool temp = 0;
    bool xd = this->comparison(x);
     for(int i=0; i<SIZEBIT;++i)
    {
        if(xd){
            if(temp)
            {
                res.arr[SIZEBIT-1-i] = !(this->arr[SIZEBIT-1-i] ^ x.arr[SIZEBIT-1-i]);
                temp = !(this->arr[SIZEBIT-1-i]) | (this->arr[SIZEBIT-1-i] & x.arr[SIZEBIT-1-i]);
            }
            else
            {
                res.arr[SIZEBIT-1-i] = this->arr[SIZEBIT-1-i] ^ x.arr[SIZEBIT-1-i];
                temp = !(this->arr[SIZEBIT-1-i]) & x.arr[SIZEBIT-1-i];
            }
        }
        else
        {
           if(temp)
            {
                res.arr[SIZEBIT-1-i] = !(this->arr[SIZEBIT-1-i] ^ x.arr[SIZEBIT-1-i]);
                temp = !(x.arr[SIZEBIT-1-i]) | (x.arr[SIZEBIT-1-i] & this->arr[SIZEBIT-1-i]);
            }
            else
            {
                res.arr[SIZEBIT-1-i] = this->arr[SIZEBIT-1-i] ^ x.arr[SIZEBIT-1-i];
                temp = !(x.arr[SIZEBIT-1-i]) & x.arr[SIZEBIT-1-i];
            } 
        }
    }
    return res;
    
}


//binary multiplication (summ of multiplication)
LongInt operator* (const LongInt& x) const{
    LongInt resadd;
    int i = 0;
    
    for(i; i<SIZEBIT; ++i)
    {
        LongInt resmul;
        for(int j = 0; j<SIZEBIT-i; ++j)
        {
            resmul.arr[SIZEBIT-1-i-j] = this->arr[SIZEBIT-1-i] & x.arr[SIZEBIT-1-j];
        }
        resadd = resadd + resmul;
    }
    return resadd;
}


//function to ignore all zeroes at the beggining
int shrink()const{
    int i = 0;
    for(;arr[i] == false;)
    {
        ++i;
    }
    return i;
} 


//power function (num1^num2) Gorner scheme
static LongInt power (const LongInt& x, const LongInt& y){
    int temp2 = y.shrink();
    LongInt res;
    res.arr[SIZEBIT-1] = true;
    if(SIZEBIT - temp2-1 == 0)
    {
        return (res);  
    }
    else
    { 
        for(int i=0; i<SIZEBIT-temp2-1;++i)
        {
            if(y.arr[temp2+i])
            {
               res = res * x;
            }
            res = res * res;
        }
        if(y.arr[SIZEBIT-1])
        {
            res = res * x;
        }
    }
    return res;
}




static LongInt div (const LongInt& x, const LongInt& y){
    int k = (SIZEBIT - y.shrink());
    LongInt q;
    LongInt r = x;

    LongInt c;
    while(r.comparison(y) == true){
        LongInt a;
        int t = (SIZEBIT - r.shrink());
        c = shiftingL(y, t-k);
        if(r.comparison(c) == false)
        {
            bool m = r.comparison(c);
            t = t-1;
            c = shiftingL(y,t-k);
        }
        r = r - c;
        a.arr[SIZEBIT-1-t+k]=true;
        q=q+a;
        
    }

    return q;
}

static LongInt gcd ( const LongInt& x,  const LongInt& y){
    LongInt d;
    LongInt a,b;
    a=x;
    b=y;
    d.arr[SIZEBIT-1] = true;
    while((a.arr[SIZEBIT-1] == false) && (b.arr[SIZEBIT-1] == false)){
        a = shiftingR(a,1);
        b = shiftingR(b,1);
        d = shiftingL(d,1);
    }
    while(a.arr[SIZEBIT-1] == false){
        a = shiftingR(a,1);
    }
    while(SIZEBIT - b.shrink() > 0){
        while(b.arr[SIZEBIT-1] == false){
            b = shiftingR(b,1);
        }
        if(a.comparison(b)){
            LongInt c = a;
            a = b;
            b = c - b;
            LongInt d;
            c = d;
        }else{
            b = b - a;
        }
    }
    d=d*a;
    return d;
}

static LongInt lcm (const LongInt& x, const LongInt& y){
    LongInt res, gsd, mul ;
    mul= x*y;
    gsd = gcd(x,y);
    res = div(mul,gsd);
    return res;
}



static LongInt modul( LongInt& x, LongInt& m){
    LongInt d, mul,res;
    d = div(x,m);
    mul = d*m;
    res = x-mul;

    return res;
}

static LongInt pm (const LongInt& x,  const LongInt& y, LongInt& m){
    LongInt add, res;
    add = x+y;
    res = modul(add, m);

    return res;
}

static LongInt mm (LongInt& x, LongInt& y, LongInt& m){
    LongInt min;
    min = x-y;
    return modul(min,m);
}

static LongInt mulm (LongInt& x, LongInt& y, LongInt& m){
    LongInt mul;
    mul = x*y;
    return modul(mul,m);
}

static LongInt divm (LongInt x, LongInt y, LongInt m){
    LongInt res;
    res = div(x,y);
    return modul(res,m);
}

static LongInt sqm(LongInt& x, LongInt& m){
    LongInt res;
    LongInt two;
    two.arr[SIZEBIT-2]=1;
    res = x * two;
    return modul(res,m);
}

static  LongInt powm(LongInt& x, LongInt& y, LongInt& m){
    LongInt pow;
    pow = power(x,y);
 return modul(pow,m);
}

static LongInt root(LongInt& x, LongInt& m){
    LongInt a = modul(x,m);
    LongInt root;
    root.arr[SIZEBIT-1]= true;
    int i = x.shrink();
    i=(((SIZEBIT-i)+1)/2);
    LongInt f;
    LongInt k;

    for(int loop = 0; loop <i; loop ++){
        k=a;
        for(int j=0; j<i*2-2*(loop+1);j++){
        k = shiftingR(k,1);
        }
        for(int s=(SIZEBIT-3);s>0;s--){
            k.arr[s] = false;
        }
        for(int c=0;c<2;c++){
            f=shiftingL(f,2);
        }
        f=f+k;
        if(f.comparison(root) == true){
        f = f-root;
        root.arr[SIZEBIT-1] = false;
        root = shiftingL(root,1);
        root.arr[SIZEBIT-1]= true;
        root.arr[SIZEBIT-3]= true;
        }
        else {
        root.arr[SIZEBIT-1] = false;
        root = shiftingL(root,1);
        root.arr[SIZEBIT-1]= true;
        root.arr[SIZEBIT-3]= false;
        }
    }
    for(int o = 0; o<2; o++){
        root = shiftingR(root,1);
    }

    return root;
}


static LongInt Barett(LongInt x, const LongInt m){
    LongInt c;
    c.arr[SIZEBIT-1] = true;
    int n = (SIZEBIT - m.shrink());
    LongInt ksi;
    ksi = shiftingL(c,2*n);
    LongInt tro = m;
    ksi = div(ksi,tro);
    LongInt one = x;
    LongInt q;  
    LongInt r;
    q = shiftingR(one,n-1);
    q = q * ksi;
    q = shiftingR(one,n+1);
    r = one-(q*tro);
    while(tro.comparison(r) == false){
        r = r - tro;
    }
    return r;
}



static LongInt LMPBarret(LongInt& x, LongInt& y, LongInt& m){
    LongInt c;
    LongInt a;
    LongInt mod;
    mod = m;
    a = x;
    c.arr[SIZEBIT-1] = true;
    int n;
    n = SIZEBIT - mod.shrink();
    int s = SIZEBIT - y.shrink();
    for(int i = 0; i<s; ++i)
    {
        if(y.arr[SIZEBIT-1-i] == true){
            c = Barett((mulm(c,a,mod)), mod);
        }
        a = Barett((mulm(a,a,mod)), mod);
    } 
    
  
    return c;
}


bool modcomp(LongInt& x){
    bool res = true;
    for(int i = 0; i<SIZEBIT; i++){
        if(this->arr[i] == x.arr[i]){
            res = true;
        }else{
            res = false;
            break;
        }
    }
    return res;
}


static LongInt square_by_prime_modul(LongInt& x, LongInt& m){
    LongInt one,two,three,five,four,eight;
    one.arr[SIZEBIT-1] = 1;
    three.arr[SIZEBIT-1] = 1;
    three.arr[SIZEBIT-2] = 1;
    five.arr[SIZEBIT-1] = 1;
    five.arr[SIZEBIT-3] = 1;
    four.arr[SIZEBIT-3] = 1;
    eight.arr[SIZEBIT-4] = 1;
    two.arr[SIZEBIT-2]=1;
    LongInt k;
    LongInt res;
    LongInt res1;
    LongInt res2;

    

    if(modul(m,four).modcomp(three) == 1){
        LongInt b;
        b = power(x,shiftingR((m-one),1));
        if(modul(b,m).modcomp(one)==1){
            k = shiftingR(m-three, 2);
            res1 = power(x,k+one);
            res1 = modul(res1,m);
            res2 = m - res1;
            }


        if(power(x,shiftingR((m-one),1)).modcomp(one)==1){
            k = shiftingR(m-five, 3);
            LongInt 
            res = power(x,(two*k+one));
            res = modul(res,m);
            if(res.modcomp(one)== 1){
                res1 = power(x,k+one);
                res2 = m - res1;
            }else{
                res1 = power(x,k+one)*power(two,two*k+one);
                res2 = m - res1;
            }
        }else{
            cout<<"Solutions don`t exist"; 
        }
    // }else if(modul(m,eight).modcomp(one)==1){
    //     LomgInt a;
    //     a=one;
    //     while(power(a,shiftingR(m-one)).modcomp(one) != one){
    //         a = a + one;
    //     }
    }else{
        cout<<"modul is not prime";
    }
    
    return res1;
}









    
//OUTPUT
//OUTPUT
//OUTPUT



//print func
void print(){
    int i=0;
    for(;arr[i] == false;)
    {
        ++i;
    }
    i = SIZEBIT -i;
    i+=3;
    i= i/4;
    i= i*4;

    string res;
    res = "0000";
    for(int j =0 ; j<i;++j){
        
        if(this->arr[SIZEBIT-i+j]==1){
            res +='1';
        }else{
            res += '0';
        }
    }
    cout<<convertBinToHex(res);
}

void createMap(unordered_map<string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
}
 
// function to find hexadecimal
string convertBinToHex(string bin)
{
    int l = bin.size();
    int t = bin.find_first_of('.');
     
    int len_left = t != -1 ? t : l;
     
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
    if (t != -1)   
    {
        int len_right = l - len_left - 1;
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);
    int i = 0;
    string hex = "";
    while (1)
    {
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;
        if (bin.at(i) == '.')   
        {
            hex += '.';
            i++;
        }
    }
    return hex;   
}
};







const char* hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
};


std::string hb(const std::string& hex)
{
    // TODO use a loop from <algorithm> or smth
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
       bin += hex_char_to_bin(hex[i]);
    return bin;
}


int main(){

    string num1, num2, num3,num4;
    LongInt num11, num21, mod, pow2;
    num1 = "2";   
    num2 = "13";
    num3 = "17";
    num4 = "2";
    pow2.converting(hb(num4));
    num11.converting(hb(num1));
    num21.converting(hb(num2));
    mod.converting(hb(num3));
    cout<<"A\n";
    num11.print();
    cout<<"\n\n";
    cout<<"B\n";
    num21.print();
    cout<<"\n\n";
    cout<<"MODUL\n";
    mod.print();
    cout<<"\n\n";
    string a,b,c,d,e;
    string a1,b1,c1,d1,e1;
    a="010F51035ED319BC50C0C4503B4D44872FC7DE7FC00F5DE863D6520E3906FC3E7E8761505118C918DB31AADBEA5A054B13A25F259CD47C1FAA7DB9B76F2DB450861BA26C4794E8E3BFBC2924DE45E47E5408536E3548A03591DA0556D595AB78C55149F45170F2CB7736A46976D1C09BFCE4DF6EAB040599AF235968F8070E25C2";
    a1="010F51035ED319BC50C0C4503B4D44872FC7DE7FC00F5DE863D6520E3906FC3E7E8761505118C918DB31AADBEA5A054B13A25F259CD47C1FAA7DB9B76F2DB450861BA26C4794E8E3BFBC2924DE45E47E5408536E3548A03591DA0556D595AB78C55149F45170F2CB7736A46976D1C09BFCE4DF6EAB040599AF235968F8070E25C2";
    b ="09A531EB436073A5B899CEAEF7CFEEE386318967D8CAA2000BCF598BA51261E38AE874C932360023620DA0CAF90CEC25EB7F21C1A55A3A9F327AE7CA879634C73FC1F9E7256D38E258EE860B509506BAE185E180C06CC8DFBC23316BA1B357240BE81B14C9EC0A25A73AE85C0049185BD4A8D7E29F9F82A7C2FBFEF68174229F4";
    b1 ="09A531EB436073A5B899CEAEF7CFEEE386318967D8CAA2000BCF598BA51261E38AE874C932360023620DA0CAF90CEC25EB7F21C1A55A3A9F327AE7CA879634C73FC1F9E7256D38E258EE860B509506BAE185E180C06CC8DFBC23316BA1B357240BE81B14C9EC0A25A73AE85C0049185BD4A8D7E29F9F82A7C2FBFEF68174229F4";
    c="030A120B609DCBE28B09CA92E12DD29D77AE6400DC22B026AFB5FB945AAF62B57F4E48BD299261F02BBB35DD2495B5CD2713BF0E30192DAE1B334659160C8552423F0AD7FB82870920DF4E9B57980EAD2ADA9F3EF4B5D0718AB7F1053700395278998CB9AD48498D65150E3E837B0BB169D432B441424557061F838A17C65F90A31105F599BF69B87485BF9C70F51D37A417E476E372558C26782AC8C8F35C3D1227E851D8A72CD708700FD90C5E17F22C4EA15730345E56BD76F04B54580813CBE306B4404C6F34BCD9840D2911E6B3CF6DE3EE428C274EDF0A97335D8256DA26FCD67BA5450593A15F6B527ECE76FBBE20F7A882347614AF4B7FAF55086659D";
    c1="030A120B609DCBE28B09CA92E12DD29D77AE6400DC22B026AFB5FB945AAF62B57F4E48BD299261F02BBB35DD2495B5CD2713BF0E30192DAE1B334659160C8552423F0AD7FB82870920DF4E9B57980EAD2ADA9F3EF4B5D0718AB7F1053700395278998CB9AD48498D65150E3E837B0BB169D432B441424557061F838A17C65F90A31105F599BF69B87485BF9C70F51D37A417E476E372558C26782AC8C8F35C3D1227E851D8A72CD708700FD90C5E17F22C4EA15730345E56BD76F04B54580813CBE306B4404C6F34BCD9840D2911E6B3CF6DE3EE428C274EDF0A97335D8256DA26FCD67BA5450593A15F6B527ECE76FBBE20F7A882347614AF4B7FAF55086659D";
    d="0D4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB";
    d1 = "0D4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB";
  

    
    // cout<<"GCD\n";
    // LongInt::gcd(num11,num21).print();
    // cout<<"\n";
    // cout<<"01\n\n";

    // cout<<"LCM\n";
    // LongInt::lcm(num11,num21).print();
    // cout<<"\n";
    // cout<<"085d620e895108fb2221135d9f2b0\n\n";

    // cout<<"( A + B ) mod C\n";
    // LongInt::pm(num11,num21,mod).print();
    // cout<<"\n";
    // cout<<"01312ba7fbc371fc5ded6f\n\n";

    // cout<<"( A - B ) mod C\n";
    // LongInt::mm(num11,num21,mod).print();
    // cout<<"\n";
    // cout<<"01312ba7fbc371fc5c64cf\n\n";

    // cout<<"( A * B ) mod C\n";
    // LongInt::mulm(num11,num21,mod).print();
    // cout<<"\n";
    // cout<<"061fc395422ce07fa17380\n\n";

    // cout<<"( A ^ 2 ) mod C\n";
    // LongInt::powm(num11,pow2,mod).print();
    // cout<<"\n";
    // cout<<"0aa34eed1be227854c8301\n\n";

    // cout<<"A mod C\n";
    // LongInt::modul(num11,mod).print();
    // cout<<"\n";

    // cout<<"A mod C (Barret)\n";
    // LongInt::Barett(num11,mod).print();
    // cout<<"\n\n";

    
    // cout<<"( A ^ B ) mod C (Barret)\n";
    // LongInt::LMPBarret(num11,num21,mod).print();
    // cout<<"\n";
    // cout<<"0adf0df3c6131109e338f1\n\n";

    cout<<"root x mod C \n";
    LongInt::square_by_prime_modul(num11,mod).print();
    cout<<"\n";

    

}
