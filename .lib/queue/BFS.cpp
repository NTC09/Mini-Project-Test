#include <iostream>

using namespace std;

//Defines
int itemPoint[7] = {5,10,30,20,1000,0,1};
int nextStep[4][2] = { {-1,2},{-1,-2},{-2,1},{-2,-1} };

struct Item
{
	int list[7];
	Item(){
		for (int i=0;i<7;i++){
			list[i] = 0;
		}
	}
	void print(){
		for(int i=0;i<7;i++){
			cout<<list[i]<<" ";
		}
		cout<<endl;
	}
};

struct Pos
{
	int x;
	int y;
	void print(){
		cout<<this->x<< " " << this->y << endl;
	}
	void put(int x, int y){
		this->x = x;
		this->y = y;
	}
	bool check(int col){
		return !(this->y < 0 || this->y >=col || this->x < 0);
	}
};

Pos add(Pos A,int a[2]){
	Pos X;
	X.x = A.x + a[0];
	X.y = A.y + a[1];
	return X;
}
struct Mat
{
	int a[20][20];
	Mat(){
		for(int i=0;i<20;i++){
			for(int j=0;j<20;j++){
				a[i][j] = 0;
			}
		}
	}
	void put(int a[20][20],int row, int col){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				this->a[i][j] = a[i][j];
			}
		}
	}
	void print(int row, int col){
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				cout<<this->a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

class Queue{
private:
	int front;
	int rear;
	Pos pos[21];
	Item item[21];
public:
	//function
	int Front() {return this->front;}
	int Rear() {return this->rear;}
	Queue(){
		this->front = 1;
		this->rear = 1;
	}
	Pos dequePos(){
		return this->pos[this->front];
	}
	Item dequeItem(){
		return this->item[this->front];
	}
	void deque(){
		this->front++;
	}
	void enque(Pos A,Item x){
		this->pos[this->rear] = A;
		this->item[this->rear] = x;
		this->rear++;
	}
	void addPos(int x, int y){
		this->pos[this->rear].x = x;
		this->pos[this->rear].y = y;
	}
	bool isEmpty(){
		return (this->front > this->rear);
	}
	int point(){
		int point = 0;
		for (int i=0;i<7;i++)
			point += this->item[this->front].list[i] * itemPoint[i];
		return point;
	}
	void addItem(int i){
		this->item[this->front].list[i]++;
	}
	void decItem(int i){
		this->item[this->front].list[i]--;
	}
	bool aegis(){
		return (this->item[this->front].list[5] > 0);
	}
};

int go(int map[20][20], int n, int m, int y){
	Queue A;
	Pos current, next;
	Item curItem;
	current.put(n-1,y);
	int maxPoint = -1;
	A.enque(current,curItem);
	//A.pos[A.front].print();
	//A.item[A.front].print();
	//BFS
	while(!A.isEmpty()){
		current = A.dequePos();
		if(!current.check(m)){
			A.deque();
			
			continue;
		}
		cout << "\tPosit "<< A.Front() << "," << A.Rear()<< ": ";
		current.print();		
		int colectItem = map[current.x][current.y] ;
		A.addItem(colectItem);
		//curItem = A.dequeItem();
		
		cout<<"Item: "<<colectItem<<endl;	
		cout<<"Point: " <<A.point()<<endl;	
		if(colectItem == 6){ //Teleport portal
			if(maxPoint < A.point())
				maxPoint = A.point();
			cout<<"Point up!\n";
			A.deque();
			continue;
		}
		if(colectItem == 4){ // Mask of Madness
			if (A.aegis()){ //Have Roshan's Aegis
				A.decItem(5);
			}
			else{
				A.deque();
				continue;
			}
		}

		curItem = A.dequeItem();
		curItem.print();
		for(int i=0;i<4;i++){
			next = add(current,nextStep[i]);
			//next.print();
			if(next.check(m)){
				A.enque(next,curItem);
				cout<<"Next: "; next.print();
			}
		}
		A.deque();
	}
	cout<<A.Front()<<endl;
	cout<<A.Rear()<<endl;
	return maxPoint;
}

int main(){
	int T,tc;
	int n,m,y;
	int map[20][20] = {};
	freopen("input.txt","r",stdin);
	cin>>T;
	for(tc=1;tc<=T;++tc){
		cin>>n>>m>>y;
		//memset(map,0,n*m*sizeof (int));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>map[i][j];
			}
		}
		/*for(int i=0;i<4;i++){
			for(int j=0;j<2;j++){
				cout<<nextStep[i][j];
			}
			cout<<endl;
		}*/
		cout<<"Point: "<<go(map,n,m,y-1)<<endl;
	}
	return 0;
}