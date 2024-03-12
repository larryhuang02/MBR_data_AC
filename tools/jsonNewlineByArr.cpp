// arg0 json_file
// arg0 json_file only indent on in-arr levels


#include <cstdio>
#include <vector>
#include <set>
// #include <unordered_set>
#include <iostream>
#include <fstream>

using namespace std;

inline unsigned isNewlineParts(const int c){
	const unsigned tbl[256]={
		0,0,0,0,0,0,0,0,
		0,0,1,0,0,1,
	};
	return tbl[c&0xFF];
}

#define PrecondType set<unsigned>

vector<char> newlined(const char *s,const size_t sz,const PrecondType &exactInarr){
	vector<char> rtv;
	int c;
	int diffstat[3][256]={0};
	int formatChars[256]={0};
	int stat=0;
	diffstat[0]['"']=1;
	diffstat[1]['"']=-1;
	diffstat[1]['\\']=1;
	for(unsigned x=0;x!=256;++x) diffstat[2][x]=-1;
	// 0: not in str ; 1: in str ; 2: in str && backslash
	formatChars['\t']=1;
	formatChars['\n']=1;
	formatChars['\r']=1;
	formatChars[' ']=1;
	
	unsigned lv_obj=0,lv_arr=0;
	auto is_precondPass=[](unsigned lv_arr,const PrecondType &exactInarr)->bool{
		return !exactInarr.size() || exactInarr.find(lv_arr)!=exactInarr.end();
	};
	auto push_newline=[](vector<char> &buf)->void{
		buf.push_back('\r');
		buf.push_back('\n');
	};
#define uu pair<unsigned,unsigned>
	vector<uu > lv;
	for(size_t x=0;x!=sz;++x){
		c=s[x]&0xFF;
		rtv.push_back(s[x]);
		stat+=diffstat[stat][c];
		if(!stat){
			switch(c){
			default: break;
			case '\t':
			case '\n':
			case '\r':
			case ' ':{
				// formatChars
				rtv.pop_back();
			}break;
			case ',':{
				if(lv.size() && lv.back()==uu(lv_arr,lv_obj) && is_precondPass(lv_arr,exactInarr)){
					push_newline(rtv);
					for(unsigned _=lv_arr;_--;) rtv.push_back('\t');
				}
			}break;
			case '[':{
				++lv_arr;
				lv.push_back(uu(lv_arr,lv_obj));
				if(s[x+1]!=']' && is_precondPass(lv_arr,exactInarr)){
					push_newline(rtv);
					for(unsigned _=lv_arr;_--;) rtv.push_back('\t');
				}
			}break;
			case ']':{
				if(!lv.size()) return {};
				if(rtv.size()>=1 && is_precondPass(lv_arr,exactInarr)){
					rtv.pop_back(); // ']'
					while(rtv.size() && formatChars[rtv.back()&0xFF]) rtv.pop_back();
					push_newline(rtv);
					for(unsigned _=lv_arr;--_;) rtv.push_back('\t');
					rtv.push_back(']');
				}
				lv.pop_back();
				--lv_arr;
			}break;
			case '{':{
				++lv_obj;
			}break;
			case '}':{
				--lv_obj;
			}break;
			}
		}
	}
#undef uu
	return rtv;
}

int main(const int argc,const char *argv[]){
	ifstream iii;
	if(argc>1) iii.open(argv[1],ios::binary);
	if(!iii) return 0;
	iii.seekg(0,iii.end);
	size_t len=iii.tellg();
	iii.seekg(0,iii.beg);
	vector<char> buf(len+1);
	iii.read(&buf[0],len);
	iii.close();
	buf[len]=0;
	PrecondType precond;
	{
		unsigned tmp;
		for(int x=2;x!=argc;++x) if(sscanf(argv[x],"%d",&tmp)==1) precond.insert(tmp);
	}
	auto res=newlined(&buf[0],len,precond);
	// for(auto &c:res) cout<<c; cout<<endl;
	ofstream ooo(argv[1],ios::binary);
	ooo.write(&res[0],res.size());
	return 0;
}