#include<string>

class BigInteger{
private:
	std::string value;
	bool negative;
	inline void checkLegal(std::string x){
		int i=0;
		if(x[0]=='-')i=1;
		for(;i<x.length();i++){
			if(x[i]<'0' || x[i]>'9')exit(1);
		}
	}
	friend BigInteger division(BigInteger a,BigInteger b,BigInteger &quotient){
		bool ne=a.negative ^ b.negative;
		if(b==2){
			BigInteger ans=a;
			if(ans[ans.length()-1]&1){
				quotient=1;
				ans.value[ans.length()-1]--;
			}
			for(int i=ans.length()-1;i>=0;i--){
				int temp=ans[i]*5;
				ans.value[i]=temp/10+'0';
				ans.value[i+1]+=temp%10;
			}
			ans.negative=ne;
			ans.value.erase(0,ans.value.find_first_not_of("0"));
			if(ans.value==""){
				ans.value="0";
				ans.negative=0;
			}
			return ans;
		}
		else{
			BigInteger x=abs(a);
			BigInteger y=abs(b);
			BigInteger l = 0;
        	BigInteger r = x;
			BigInteger mid;
        	while(l<r){
            	mid=(l+r+1)/2;
            	if(y*mid<x)l=mid;
				else if(y*mid==x){
					r=mid;
					break;
				}
				else r=mid-1;
        	}
			r.negative=ne;
			if(r.value=="0"){
				r.negative=0;
			}
			quotient=a-r*b;
        	return r;
		}
	}
public:
	BigInteger(int a=0){
		negative=a<0;
		*this=std::to_string(a);
	}
	BigInteger(std::string a){
		checkLegal(a);
		negative=false;
		if(a[0]=='-'){
			negative=true;
			value=a.substr(1,a.length()-1);
		}
		else value=a;
	}
	explicit operator bool(){return !*this;}
	int length()const{return value.length();}
	friend std::ostream & operator<<(std::ostream &out,const BigInteger &a){
		std::string c=(a.negative)?"-":"";
		out<<c<<a.value;
		return out;
	}
	friend std::istream & operator>>(std::istream &in,BigInteger &a){
		std::string temp;
		in>>temp;
		a=temp;
		return in;
	}
	int operator[](int index){return value[index]-'0';}
	friend BigInteger abs(BigInteger a){return a.negative?-a:a;}
	bool operator!(){return *this==0;}
	bool operator<(BigInteger o)const{
		if(this->negative && o.negative)return abs(*this) > abs(o);
		else if(this->negative || o.negative)return this->negative;
		if(value.length()!=o.length()){
			return value.length()<o.length();
		}
		for(int i=0;i<value.length();i++){
			if(value[i]!=o[i]+'0'){
				return value[i]<o[i]+'0';
			}
		}
		return false;
	}
	bool operator==(BigInteger o)const{
		if(negative != o.negative || length() != o.length())return false;
		for(int i=0;i<length();i++){
			if(value[i] != o.value[i])return false;
		}
		return true;
	}
	bool operator>(BigInteger o)const{return *this<o;}
	bool operator<=(BigInteger o)const{return !(*this<o);}
	bool operator>=(BigInteger o)const{return !(*this>o);}
	bool operator!=(BigInteger o)const{return !(*this==o);}
	BigInteger operator-(){
		BigInteger ans=*this;
		ans.negative=!ans.negative;
		return ans;
	}
	BigInteger operator++(){(*this)+=1;return *this;}
   	BigInteger operator++(int){*this+=1;return *this-1;}
   	BigInteger operator--(){*this-=1;return *this;}
   	BigInteger operator--(int){*this-=1;return *this+1;}
	friend BigInteger operator+(BigInteger a,BigInteger b){
		if(a.negative && b.negative)return -(abs(a)+abs(b));
		else if(a.negative)return b-abs(a);
		else if(b.negative)return a-abs(b);
		else if(a<b)return b+a;
		std::string ans=a.value;
		for(int i=1;i<=b.length();i++){
			ans[ans.length()-i]+=b[b.length()-i];
		}
		for(int i=ans.length()-1;i>=0;i--){
			if(ans[i]>'9'){
				ans[i]-=10;
				if(i!=0)ans[i-1]++;
				else ans="1"+ans;
			}
		}
		return ans;
	}
	friend BigInteger operator-(BigInteger a,BigInteger b){
		if(a.negative && b.negative)return a+abs(b);
		else if(a.negative)return -(abs(a)+abs(b));
		else if(b.negative)return a+abs(b);
		else if(a<b)return -(b-a);
		std::string ans=a.value;
		for(int i=1;i<=b.length();i++){
			ans[ans.length()-i]-=b[b.length()-i];
		}
		for(int i=ans.length()-1;i>=0;i--){
			if(ans[i]<'0'){
				ans[i]+=10;
				ans[i-1]--;
			}
		}
		ans.erase(0,ans.find_first_not_of("0"));
		if(ans=="")ans="0";
		return ans;
	}
	friend BigInteger operator*(BigInteger a,BigInteger b){
		bool ne=a.negative ^ b.negative;
		BigInteger ans;
		for(int i=0;i<a.length();i++){
			for(int j=0;j<b.length();j++){
				std::string temp=std::to_string((a[i])*(b[j]));
				for(int k=0;k<a.length()+b.length()-i-j-2;k++){
					temp+='0';
				}
				ans=ans+temp;
			}
		}
		ans.negative=ne;
		ans.value.erase(0,ans.value.find_first_not_of("0"));
		if(ans.value==""){
			ans.value="0";
			ans.negative=0;
		}
		return ans;
	}
	friend BigInteger operator/(BigInteger a,BigInteger b){
		BigInteger quotient;
		return division(a,b,quotient);
	}
	friend BigInteger operator%(BigInteger a,BigInteger b){
		BigInteger ans;
		division(a,b,ans);
		return ans;
	}
	friend BigInteger operator<<(BigInteger a,BigInteger b){
		while(b--)a*=2;
		return a;
	}
	friend BigInteger operator>>(BigInteger a,BigInteger b){
		while(b--)a/=2;
		return a;
	}
	friend void operator+=(BigInteger &a,BigInteger b){a=a+b;}
	friend void operator-=(BigInteger &a,BigInteger b){a=a-b;}
	friend void operator*=(BigInteger &a,BigInteger b){a=a*b;}
	friend void operator/=(BigInteger &a,BigInteger b){a=a/b;}
	friend void operator%=(BigInteger &a,BigInteger b){a=a%b;}
	friend void operator<<=(BigInteger &a,BigInteger b){a=a<<b;}
	friend void operator>>=(BigInteger &a,BigInteger b){a=a>>b;}
};
