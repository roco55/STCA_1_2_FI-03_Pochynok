#include <iostream>
using namespace std;
#include <string>
#include <bits/stdc++.h>
#define SIZEBIT 15
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
static LongInt shiftingR(LongInt x){
    for(int i=SIZEBIT-1; i>1; i--){
        x.arr[i]=x.arr[i-1];
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
        a = shiftingR(a);
        b = shiftingR(b);
        d = shiftingL(d,1);
    }
    while(a.arr[SIZEBIT-1] == false){
        shiftingR(a);
    }
    while(SIZEBIT - b.shrink() > 0){
        while(b.arr[SIZEBIT-1] == false){
            b = shiftingR(b);
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



static LongInt modul( LongInt& x, const LongInt& m){
    LongInt d, mul,res;
    d = div(x,m);
    mul = d*m;
    res = x-mul;

    return res;
}

static LongInt pm (const LongInt& x,  const LongInt& y, const LongInt& m){
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

static LongInt root(  LongInt& x, LongInt& m){
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
        k = shiftingR(k);
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
        root = shiftingR(root);
    }

    return root;
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

    string num1, num2, num3;
    LongInt num11, num21, mod;
    num1 = "AAA";
    num2 = "A";
    num3 = "AA";
    num11.converting(hb(num1));
    num21.converting(hb(num2));
    mod.converting(hb(num3));
    cout<<"NUM1\n";
    num11.print();
    cout<<"\n";
    cout<<"NUM2\n";
    num21.print();
    cout<<"\n";
    cout<<"NUM3\n";
    mod.print();
    cout<<"\n";



    LongInt res_pl = num11 + num21;
    cout<<"PLUS\n";
    res_pl.print();
    cout<<"\n";

    LongInt res_mi = num11 - num21; 
    cout<<"MINUS\n";
    res_mi.print();
    cout<<"\n";

    LongInt res_mul = num11 * num21;
    cout<<"MUL\n";
    res_mul.print();
    cout<<"\n";

    LongInt res_pow = LongInt::power(num11,num21);
    cout<<"POW\n";
    res_pow.print();
    cout<<"\n";
    

    LongInt res_div = LongInt::div(num11,num21);
    cout<<"DIV\n";
    res_div.print();
    cout<<"\n";
    /*
    LongInt res_gcd = LongInt::gcd(num11,num21);
    cout<<"GCD is\n";
    res_gcd.print();
    cout<<"\n";

    LongInt res_lcm = LongInt::lcm(num11,num21);
    cout<<"LCM is\n";
    res_lcm.print();
    cout<<"\n";

    LongInt res_pm = LongInt::pm(num11,num21, mod);
    cout<<"addition by mod is\n";
    res_pm.print();
    cout<<"\n";

    LongInt res_mm = LongInt::mm(num11,num21, mod);
    cout<<"minus by mod is\n";
    res_mm.print();
    cout<<"\n";

    LongInt res_mulm = LongInt::mulm(num11,num21, mod);
    cout<<"multiplication by mod is\n";
    res_mulm.print();
    cout<<"\n";

    LongInt res_sqm = LongInt::sqm(num11, mod);
    cout<<"x^2 by mod is\n";
    res_sqm.print();
    cout<<"\n";

    LongInt res_powm = LongInt::powm(num11,num21, mod);
    cout<<"power by mod is\n";
    res_powm.print();
    cout<<"\n";
    */
    LongInt res_root = LongInt::root(num11,mod);
    cout<<"root of num11 is\n";
    res_root.print();
    cout<<"\n";


    
   
}

