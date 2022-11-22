#include <iostream>
using namespace std;
#include <string>
#include <bits/stdc++.h>
#define SIZEBIT 2048
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
    num1 = "D4D2110984907B5625309D956521BAB4157B8B1ECE04043249A3D379AC112E5B9AF44E721E148D88A942744CF56A06B92D28A0DB950FE4CED2B41A0BD38BCE7D0BE1055CF5DE38F2A588C2C9A79A75011058C320A7B661C6CE1C36C7D870758307E5D2CF07D9B6E8D529779B6B2910DD17B6766A7EFEE215A98CAC300F2827DB";
    num2 = "3A7EF2554E8940FA9B93B2A5E822CC7BB262F4A14159E4318CAE3ABF5AEB1022EC6D01DEFAB48B528868679D649B445A753684C13F6C3ADBAB059D635A2882090FC166EA9F0AAACD16A062149E4A0952F7FAAB14A0E9D3CB0BE9200DBD3B0342496421826919148E617AF1DB66978B1FCD28F8408506B79979CCBCC7F7E5FDE7";
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
  
    /*
    LongInt res_pl = num11 + num21;
    cout<<"PLUS\n";
    res_pl.print();
    cout<<"\n";
    if(a == a1){
        cout<<"test passed\n";
    }
    LongInt res_mi = num11 - num21; 
    cout<<"MINUS\n";
    res_mi.print();
    cout<<"\n";
    if(b == b1){
        cout<<"test passed\n";
    }
    

    LongInt res_mul = num11 * num21;
    cout<<"MUL\n";
    res_mul.print();
    cout<<"\n";
    if(c == c1){
        cout<<"test passed\n";
    }
    cout<<"\n";

    LongInt res_pow = LongInt::power(num11,num21);
    cout<<"POW\n";
    res_pow.print();
    cout<<"\n";
    

    LongInt res_div = LongInt::div((num11*num21),num21);
    cout<<"DIV\n";
    res_div.print();
    cout<<"\n";
     if(d == d1){
        cout<<"test passed\n";
    }
    cout<<"\n";
  */
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
    
    LongInt res_root = LongInt::root(num11,mod);
    cout<<"root of num11 is\n";
    res_root.print();
    cout<<"\n";
  

    
   
}

