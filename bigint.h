#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED //Prevent multiple compilations
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#define LIMIT 1000000000 // set x decimal number,which is easy to output
#define LIMIT_LENGTH 9

using namespace std;

class bint{
private:
    vector< int > number;
    bool sign;
public:
    bint();
    bint(string s);
//    bint(string s,bool sin);
    bint(int n);
    void setNumber(vector< int > n);
    void setNumber(string s);
    vector<int> getNumber();
    void setSign(bool sin);
    bool getSign();
    string toString();
    void moveLeft();
    bint sqrt();
//    void operator = (bint b);
    bool operator == (bint b);
    bool operator != (bint b);
    bool operator > (bint b);
    bool operator < (bint b);
    bool operator >= (bint b);
    bool operator <= (bint b);
    bint operator + (bint b);
    bint operator - (bint b);
    bint operator * (bint b);
    bint operator / (bint b);
    bint operator % (bint b);
    // quick access for int type
    void operator = (int b);
    bool operator == (int b);
    bool operator != (int b);
    bool operator > (int b);
    bool operator < (int b);
    bool operator >= (int b);
    bool operator <= (int b);
    bint operator + (int b);
    bint operator - (int b);
    bint operator * (int b);
    bint operator / (int b);
    bint operator % (int b);


    void show(){ //for debug
        for(int i = 0;i < number.size();i++){
            cout<<number[i]<<endl;
        }
        cout<<"sign:"<<sign<<endl;
    }
    void show_v(vector < int > n){ // for debug
        for(int i = 0;i < n.size();i++){
            cout<<"pos "<<i<<" : "<<n[i]<<endl;
        }
    }
    void show_n(){ // for debug
        cout<<"value "<<toString()<<endl;
    }

private:
    bool my_equal(bint b1,bint b2);
    bool my_less(bint b1,bint b2);
    bool my_greater(bint b1,bint b2);
    bool abs_equal(vector< int > n1,vector< int > n2);
    bool abs_less(vector< int > n1,vector< int > n2);
    bool abs_greater(vector< int > n1,vector< int > n2);
    vector< int > add(vector< int > n1,vector< int > n2);
    vector< int > add(vector< int > n1,int n2);
    vector< int > sub(vector< int > n1,vector< int > n2);
    vector< int > sub(vector< int > n1,int n2);
    vector< int > mul(vector< int > n1,vector< int > n2);
    vector< int > mul(vector< int > n1,int n2);
    pair< bint, bint> div(bint n1,bint n2);
    pair< bint, bint > findQuotient(bint n1,bint n2);
    vector< int > get_vector(long long n);
    vector< int > get_vector(string s);

};

#endif // BIGINT_H_INCLUDED

bint::bint(){
    number.push_back(0);
    sign = true;
}

bint::bint(string s){
    if(isdigit(s[0])){
//        cout<<3333333333<<endl;
        sign = true;
//        cout<<4444444444<<endl;
        number = get_vector(s);
    }
    else{
//        cout<<4444444444<<endl;
        sign = (s[0] == '+');
//        cout<<22222233333333<<endl;
        number = get_vector(s.substr(1));
    }
}

bint::bint(int n){
    if(n >= 0){
        sign = true;
        number = get_vector(n);
    }
    else{
        sign = false;
        number = get_vector(abs(n));
    }

}

void bint::setNumber(vector< int > n){
    number = n;
}

void bint::setNumber(string s){
    number = get_vector(s);
}

vector<int> bint::getNumber(){
    return number;
}

void bint::setSign(bool sin){
    sign = sin;
}

bool bint::getSign(){
    return sign;
}

void bint::moveLeft(){
    if((*this) != 0)
        number.insert(number.begin(),0);
}

string bint::toString(){
    string ans = "";
    stringstream ss;
    string tmp;
    int tmpl = 0;
    int l = number.size();
    for(int i = 0;i < l - 1;i++){
        ss.clear();
        ss << number[i];
        ss >> tmp;
        tmpl = tmp.size();
        tmp = string((LIMIT_LENGTH - tmpl),'0') + tmp;
        ans = tmp + ans;
    }
    ss.clear();
    ss << number[l - 1];
    ss >> tmp;
    if(!sign){
        return "-" + tmp + ans;
    }
    return tmp + ans;
}

bint bint::sqrt(){ //return the upper bound of the sqrt
    bint now = (*this);
    bint ans;
    if(now < 0){
        return ans;
    }
    else if(now > 4){
        bint b;
        bint e;
        e = now / 2;
        while(b <= e){
            bint mid = (b + e) / 2;
//            mid.show_n();
            bint product = mid * mid;
            if(product == now){
                return mid;
            }
            else if( product < now){
                b = mid + 1;
            }
            else{
                bint tmp = mid - 1;
                if( (tmp * tmp) < now ){
                    return mid;
                }
                else{
                    e = tmp;
                }
            }
        }
    }
    else{
        return 2;
    }
    return ans;
}

//===================================================================
bool bint::operator == (bint b){
    return my_equal((*this),b);
}

bool bint::operator == (int b){
    bint tmp(b);
    return (*this) == tmp;
}

bool bint::operator != (bint b){
    return !my_equal((*this),b);
}

bool bint::operator != (int b){
    bint tmp(b);
    return (*this) != tmp;
}

bool bint::operator > (bint b){
    return my_greater((*this),b);
}

bool bint::operator > (int b){
    bint tmp(b);
    return (*this) > tmp;
}

bool bint::operator < (bint b){
    return my_less((*this),b);
}

bool bint::operator < (int b){
    bint tmp(b);
    return (*this) < tmp;
}

bool bint::operator >= (bint b){
    return my_greater((*this),b) || my_equal((*this),b);
}

bool bint::operator >= (int b){
    bint tmp(b);
    return (*this) >= tmp;
}

bool bint::operator <= (bint b){
    return my_less((*this),b) || my_equal((*this),b);
}

bool bint::operator <= (int b){
    bint tmp(b);
    return (*this) <= tmp;
}

//====================================================================
bint bint::operator + (bint b){
    bint ans;
    vector<int> nb = b.getNumber();
    if(sign == b.sign){
        ans.setNumber( add(number,nb) );
        ans.setSign(sign);
    }
    else{

        if(abs_equal(number, nb)){
            return ans;//default is 0
        }
        else if(abs_less(number, nb)){
            ans.setNumber(sub(nb, number));
            ans.setSign(b.getSign());
        }
        else{
            ans.setNumber(sub(number, nb));
            ans.setSign(sign);
        }
    }
    return ans;
}

bint bint::operator + (int b){
    bint tmp(b);
    return (*this) + tmp;
}

bint bint::operator - (bint b){
    b.setSign( ! b.getSign() );
    return (*this) + b;
}

bint bint::operator - (int b){
    bint tmp(b);
    return (*this) - tmp;
}

bint bint::operator * (bint b){
    bint ans;
    ans.setSign( sign == b.getSign());
    ans.setNumber( mul(number,b.getNumber()));
    return ans;
}

bint bint::operator * (int b){
    bint tmp(b);
    return (*this) * tmp;
}

bint bint::operator / (bint b){
    pair<bint, bint> result;
    result = div((*this), b);
    bint ans;
    ans = result.first;
    ans.setSign((sign == b.getSign()));
    return ans;
}

bint bint::operator / (int b){
    bint tmp(b);
    return (*this) / tmp;
}

bint bint::operator % (bint b){
    pair<bint, bint> result;
    result = div((*this) , b);
    return result.second;
}

bint bint::operator % (int b){
    bint tmp(b);
    return (*this) % tmp;
}

void bint::operator = (int n){
    if(n >= 0){
        sign = true;
        number = get_vector(n);
    }
    else{
        sign = false;
        number = get_vector(abs(n));
    }
}

//================================================================


bool bint::my_equal(bint b1,bint b2){
    return (b1.getNumber() == b2.getNumber()) && (b1.getSign() == b2.getSign());
}

bool bint::my_less(bint b1,bint b2){
    bool s1 = b1.getSign();
    bool s2 = b2.getSign();
    vector< int > n1 = b1.getNumber();
    vector< int > n2 = b2.getNumber();
    if(!s1 && s2){ // - && +
        return true;
    }
    else if(s1 && !s2){ // + && -
        return false;
    }
    else if(s1 && s1){ // + && +
        return abs_less(n1,n2);
    }
    else{ // - && -
        return abs_greater(n1,n2);
    }
    return false;
}

bool bint::my_greater(bint n1,bint n2){
    return !my_equal(n1,n2) && ! my_less(n1,n2);
}

bool bint::abs_equal(vector< int > n1,vector< int > n2){
    return n1 == n2;
}

bool bint::abs_less(vector< int > n1,vector< int > n2){
    int l1 = n1.size();
    int l2 = n2.size();
    if(l1 < l2 ){
        return true;
    }
    else if(l1 > l2){
        return false;
    }
    else{
        for(int i = l1 - 1;i >= 0;i --){
            if(n1[i] > n2[i]){
                return false;
            }
            else if(n1[i] < n2[i]){
                return true;
            }
            else if((i == 0) && (n1[i] == n2[i])){// equal
                return false;
            }
        }
    }
    return false;
}

bool bint::abs_greater(vector< int > n1,vector< int > n2){
    return !abs_equal(n1,n2) && !abs_less(n1,n2);
}

vector<int> bint::add(vector< int > n1,vector< int > n2){
    int l1 = n1.size();
    int l2 = n2.size();
//    cout<<"start to add"<<endl;
    if(l1 < l2) // let l1 > l2
        return add(n2,n1);
    vector<int> ans = n1;
    long long tmp = 0;
    int carry = 0;
    n2.insert(n2.end(),l1-l2,0);
    for(int i = 0;i < l1;i ++){
        tmp = (long long)n1[i] + (long long)n2[i] + (long long)carry;
//        cout<<"tmp"<<tmp<<endl;
        if(tmp >= LIMIT){
            carry = 1;
            ans[i] = (int)(tmp - LIMIT);
        }
        else{
            carry = 0;
            ans[i] = (int)(tmp);
        }
//        show_v(ans);
    }
    if(carry == 1){
        ans.push_back(1);
    }
    return ans;
}

vector<int> bint::add(vector< int > n1,int n2){
    return add(n1,get_vector(n2));
}

vector< int > bint::sub(vector< int > n1,vector< int > n2){ //s.t. n1 >= n2 when function used
    int l1 = n1.size();
    int l2 = n2.size();
    if(l1 < l2) // let l1 > l2
        return add(n2,n1);
    vector<int> ans = n1;
    long long tmp = 0;
    n2.insert(n2.end(),l1-l2,0);
    for(int i = 0;i < l1;i ++){
        if(n1[i] < n2[i]){
            n1[i + 1] -= 1;
            tmp = LIMIT + (long long)n1[i];
            ans[i] = (int)(tmp - n2[i]);
        }
        else{
            ans[i] = n1[i] - n2[i];
        }
    }
    while(ans.back() == 0 && ans.size() > 1){ // remove the useless zero
        ans.pop_back();
    }
    return ans;
}

vector< int > bint::sub(vector< int > n1,int n2){
    return sub(n1,get_vector(n2));
}

vector<int> bint::mul(vector< int > n1,vector< int > n2){
    int l1 = n1.size();
    int l2 = n2.size();
    if(l1 < l2) // let l1 > l2
        return mul(n2,n1);
    vector<int> ans;
    ans.push_back(0);
    long long carry = 0;
    for(int i = 0; i < l2 ; i++){
        long long current = n2[i];
        vector<int> mid_ans = n1;
        carry = 0;
        for(int j = 0;j < l1;j ++){
            long long tmp = (long long)n1[j] * current + carry;
            if(tmp >= LIMIT){
                carry = tmp / LIMIT;
                mid_ans[j] = tmp % LIMIT;
            }
            else{
                carry = 0;
                mid_ans[j] = (int)tmp;
            }
        }
        if(carry > 0){
            mid_ans.push_back(carry);
        }
        mid_ans.insert(mid_ans.begin(),i,0);
        ans = add(ans,mid_ans);
    }
    while(ans.back() == 0 && ans.size() > 1){ // remove the useless zero
        ans.pop_back();
    }
    return ans;
}

vector<int> bint::mul(vector< int > n1,int n2){
    return mul(n1,get_vector(n2));
}

// I don't use vector here because processing is complex for div
pair< bint, bint> bint::div(bint n1,bint n2){
    bint ans;
    bint reminder; // default 0
    vector< int > n1_v = n1.getNumber();
    int l1 = n1_v.size();
    pair< bint, bint> result_pair;

    n1.setSign(true);// only consider the abs value here
    n2.setSign(true);

    if(n1 < n2){
        reminder = n1;
        return make_pair(ans,reminder);
    }

    for(int i = l1 - 1;i >= 0;i --){
        reminder.moveLeft();
        reminder = reminder + n1_v[i];
//        cout<<"tmp  ";
//        reminder.show_n();
        result_pair = findQuotient(reminder, n2);
        reminder = result_pair.second;
        ans.moveLeft();
        ans = ans + result_pair.first;
//        cout<<"ans  ";
//        ans.show_n();
//        cout<<"r  ";
//        reminder.show_n();
    }
    //remove 0?
    return make_pair(ans,reminder);
}

pair< bint, bint > bint::findQuotient(bint n1,bint n2){
    bint ans;
    bint reminder; // default 0
    long long b = 0; //begin
    long long e = LIMIT - 1; // end
    int quot;
    if(n1 < n2){
        reminder = n1;
        return make_pair(ans,reminder);
    }
    while(b <= e){
        quot = (b + e)/2;
//        cout<<"Quot : ====="<<quot<<" "<<b<<" "<<e<<endl;
        bint tmp = n2 * quot;
//        tmp.show();
//        cout<<"===bool : "<<tmp < <<endl;
        if(tmp == n1){
            ans = quot;
            return make_pair(ans,reminder);
        }
        else if(tmp > n1 ){
            e = quot - 1;
        }
        else{
            if(n2 + tmp > n1){ // n2 * (quot + 1)
                ans = quot;
                reminder = n1 - tmp;
                return make_pair(ans,reminder);
            }
            else{
                b = quot + 1;
            }
        }
    }
    return make_pair(ans,reminder);
}

vector< int > bint::get_vector(long long n){
    vector< int > ans;
    if(n >= LIMIT){
        ans.push_back(n % LIMIT);
        ans.push_back(n / LIMIT);
    }
    else{
        ans.push_back(n);
    }
    return ans;
}

vector< int > bint::get_vector(string s){
    int ls = s.size();
    vector< int > tmp;
    tmp.push_back(0);
    for(int i = 0;i < ls;i ++){
        tmp = add(tmp,s[i] - '0');
//        cout<<"now : "<<s.substr(0, i + 1)<<" ================="<<endl;
//        show_v(tmp);
        if(i != ls - 1) // don't do this for the last loop
            tmp = mul(tmp,10);
//        cout<<"=====after : "<<s.substr(0, i + 1)<<endl;
//        show_v(tmp);
    }
    return tmp;
}
