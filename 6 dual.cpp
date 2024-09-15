// -fexec-charset=GBK, (捣)守狼女预猎(灵)(金)
#include <bits/stdc++.h>
using namespace std;
#define int long long
string cards[] = {"预", "女", "猎", "守", "复", "民", "民", "民", "民", "民", "狼", "潜"};
map<string, bool> type;
#define left(i) ((i) * 2 - 2)
#define right(i) ((i) * 2 - 1)
bool check() {
	for(int i = 1; i <= 6; i++) 
		if(cards[left(i)] == "预" && !type[cards[right(i)]]) return 0;
		else if(cards[right(i)] == "预" && !type[cards[left(i)]]) return 0;
	int cnt = 0;
	for(int i = 1; i <= 6; i++) if(cards[left(i)] == "民" && cards[right(i)] == "民") cnt++;
	return cnt;
}
char state[7][2]; int top[7];
void print() {
	for(int i = 1; i <= 6; i++) cout<<i<<": "<<cards[left(i)]<<state[i][0]<<" "<<cards[right(i)]<<state[i][1]<<endl;
}
string get(int i, int k = -1) {
	if(k >= 0) {
		if(top[i] <= k) {
			if(!k) return cards[left(i)];
			else if(k == 1) return cards[right(i)];
		} else return "空";
	}
	if(!top[i]) return cards[left(i)];
	else if(top[i] == 1) return cards[right(i)];
	else return "空";
}
void die(int i) {
	if(get(i) == "猎") {
		int k; cout<<"猎人 "<<i<<" 带 "; cin>>k;
		if(k) die(k);
	}
	state[i][top[i]++] = 'x';
}
signed main() {
    mt19937 rnd(time(0));
	for(int i = 0; i < 12; i++) 
		if(i < 10) type[cards[i]] = 1;
		else type[cards[i]] = 0;
	type["空"] = 1;
    do shuffle(cards,cards + 12, rnd);
	while(!check());
	while(1) {
		system("cls");
		cout<<"--- 发牌阶段 ---"<<endl; cout<<endl;
		for(int i = 1; i <= 6; i++) cout<<cards[left(i)]<<" "<<cards[right(i)]<<endl; cout<<endl;
		int k; cout<<"换 "; cin>>k;
		if(!k) break;
		else swap(cards[left(k)], cards[right(k)]);
	}
	for(int i = 1; i <= 6; i++) state[i][0] = state[i][1] = ' '; 
	for(int i = 1; i <= 6; i++) 
		if(cards[left(i)] == "复") cards[left(i)] = cards[right(i)];
		else if(cards[right(i)] == "复") cards[right(i)] = cards[left(i)];
	int used1 = 0, used2 = 0;
	for(int cnt = 1; ; cnt++) {
		system("cls");
		cout<<"--- 游戏阶段 ---"<<endl; cout<<endl;
		cout<<"Day "<<cnt<<endl; cout<<endl; 
		print(); cout<<endl;
		int save[7] = {0, 0, 0, 0, 0, 0, 0}, kill = 0, poison = 0;
		for(int i = 1; i <= 6; i++) if(get(i) == "守") {
			int k; cout<<"守卫 "<<i<<"("<<top[i] + 1<<")"<<" 守 "; cin>>k;
			save[k]++;
			break;
		}
		vector<pair<int, int>> wolf;
		for(int i = 1; i <= 6; i++) 
			if(!type[get(i)]) wolf.push_back({i, top[i] + 1});
			else if(get(i, 1) == "潜") wolf.push_back({i, 2});
		if(!wolf.empty()) {
			cout<<"狼人 "; for(auto [i, j] : wolf) cout<<i<<"("<<j<<")"<<" "; cout<<"刀 "; cin>>kill;
		}
		for(int i = 1; i <= 6; i++) if(get(i) == "女") {
			if(!used1) {
				int k; cout<<"女巫 "<<i<<"("<<top[i] + 1<<")"<<" 今晚 "<<kill<<" 死了，救 "; cin>>k;
				if(k) save[kill]++, used1 = 1;
			} 
			if(!used2) {
				cout<<"女巫 "<<i<<"("<<top[i] + 1<<")"<<" 毒 "; cin>>poison;
				if(poison) used2 = 1;
			}
			break;
		}
		for(int i = 1; i <= 6; i++) if(get(i) == "预") {
			int k; cout<<"预言 "<<i<<"("<<top[i] + 1<<")"<<" 查 "; cin>>k;
			cout<<"  "<<((type[get(k)] || (type[cards[left(k)]] && type[cards[right(k)]])) ? "好" : "坏")<<endl;
			break;
		}
		for(int i = 1; i <= 6; i++) if(get(i) == "猎") {
			cout<<"猎人 "<<i<<"("<<top[i] + 1<<")"<<" "<<(poison == i ? "不" : "")<<"可以发动技能"<<endl;
			break;
		}
		cout<<endl;
		vector<int> died;
		if(kill) {
			if(!save[kill]) cout<<kill<<"("<<top[kill] + 1<<") 被刀"<<endl, died.push_back(kill);
			else if(save[kill] == 2) cout<<kill<<"("<<top[kill] + 1<<") 奶穿"<<endl, died.push_back(kill);
		}
		if(poison && poison != kill) {
			if(!save[poison]) cout<<poison<<"("<<top[poison] + 1<<") 被毒"<<endl, died.push_back(poison);
			else if(save[poison] == 2) cout<<poison<<"("<<top[poison] + 1<<") 奶穿"<<endl, died.push_back(poison);
		}
		if(!died.empty()) {
			cout<<"今晚 "; for(int i : died) cout<<i<<"("<<top[i] + 1<<") "; cout<<"推牌"<<endl;
			for(int i : died) die(i);
		} else cout<<"今晚平安夜"<<endl;
		cout<<endl; print(); cout<<endl;
		vector<int> vote[7];
		for(int i = 1; i <= 6; i++) {
			int u, v; cin>>u>>v;
			vote[v].push_back(u);
		}
		int maxv = 0; vector<int> maxi;
		for(int i = 1; i <= 6; i++) if(!vote[i].empty()) {
			sort(vote[i].begin(), vote[i].end());
			for(int j : vote[i]) cout<<j<<" "; cout<<"-> "<<i<<endl;
			if(vote[i].size() > maxv) maxv = vote[i].size(), maxi = {i};
			else if(vote[i].size() == maxv) maxi.push_back(i);
		}
		if(!maxv || maxi.size() > 1) cout<<"今日平安日"<<endl;
		else cout<<"今日 "<<maxi[0]<<"("<<top[maxi[0]] + 1<<") 推牌"<<endl, die(maxi[0]);
		cout<<endl;
		system("pause");
	}
	return 0;
}
