//Programmed by Timur Kukharskiy 2013
//P.S. It still possible to optimize this code... :)

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
struct group{
	string el;
	int count;
	group(){
		count=0;
		el="0000";
	}
};
void tribit(map<string,string> &mymap,string &s,vector<group> &groups,bool stage,bool &changed){
	string out="";
	for(int i=s.size()-1,cur_gr=0,back_gr=0,cur_el=3,dist=0;i>=0;i--,cur_el--){
		if((cur_el==2)||(cur_el==-1))cur_gr++;
		if(cur_el==-1)cur_el=3;
		if((cur_el==3)&&(cur_gr>(back_gr+dist))){
			back_gr=back_gr+dist+1;
			dist+=2;
		}
		if(cur_gr>(back_gr+dist))cur_gr=back_gr;
		if (stage==true){
			groups[cur_gr].el[cur_el]=s[i];
			groups[cur_gr].count++;
			if(groups[cur_gr].count==4){
				if((changed==false)&&(groups[cur_gr].el!=mymap[groups[cur_gr].el]))changed=true;
				groups[cur_gr].el=mymap[groups[cur_gr].el];
			}
		}else {
			out=out+groups[cur_gr].el[cur_el];
			groups[cur_gr].count=0;
		}
	}
	if(stage==false){
		reverse(out.begin(),out.end());
		s=out;
	}
}
int main(int argc, char *argv[]){
	string s=argv[1];
	map<string,string> mymap;
	vector<group> groups;
	bool check=false;
	for(int i=0;i<12;i++){
		int l=pow(4.0,i);
		if(s.size()==l){
			check=true;
			break;
		}
	}
	if(check==false){
		cout<<"Wrong Parameter! Must be pow 4 ^X"<<endl;
		return 0;
	}
	groups.resize(s.size()/4);
	
	mymap.insert(pair<string,string>("0000","0000"));
	mymap.insert(pair<string,string>("0001","1000"));
	mymap.insert(pair<string,string>("0010","0001"));
	mymap.insert(pair<string,string>("0011","0010"));
	mymap.insert(pair<string,string>("0100","0000"));
	mymap.insert(pair<string,string>("0101","0010"));
	mymap.insert(pair<string,string>("0110","1011"));
	mymap.insert(pair<string,string>("0111","1011"));
	mymap.insert(pair<string,string>("1000","0100"));
	mymap.insert(pair<string,string>("1001","0101"));
	mymap.insert(pair<string,string>("1010","0111"));
	mymap.insert(pair<string,string>("1011","1111"));
	mymap.insert(pair<string,string>("1100","1101"));
	mymap.insert(pair<string,string>("1101","1110"));
	mymap.insert(pair<string,string>("1110","0111"));
	mymap.insert(pair<string,string>("1111","1111"));
	cout<<argv[1]<<endl;
	while(s.size()!=1){
		bool changed=true;
		while(changed){
			changed=false;
			tribit(mymap,s,groups,true,changed);
			tribit(mymap,s,groups,false,changed);
			if(changed==true)cout<<s<<endl;
		}
		int size=s.size()/4;
		s="";
		for(int i=size-1;i>=0;i--){
			s=s+groups[i].el[0];
		}
		cout<<s<<endl;
	}
	return 0;
}