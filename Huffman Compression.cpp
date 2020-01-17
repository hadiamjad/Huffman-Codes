#include<iostream>
#include <fstream>
#include<string>

using namespace std;


class dnode
{
	int ascii;
	int freq;
	dnode* next;
	dnode* prev;
public:
	dnode()
	{
		ascii = 0;
		freq = 0;
		next = prev = nullptr;
	}
	dnode(int d,int k, dnode* n = nullptr, dnode * p = nullptr)
	{
		ascii = d;
		freq = k;
		next = n;
		prev = p;
	}

	int return_ascii()
	{
		return ascii;
	}

	int return_freq()
	{
		return freq;
	}

	void insert(int d, int k, dnode*n = nullptr, dnode* p = nullptr)
	{
		ascii = d;
		freq = k;
		next = n;
		prev = p;
	}

	bool operator <(dnode d)
	{
		if (this->ascii < d.ascii)
			return true;
		return false;
	}

	friend class dlist;
	friend class hashtable;
	friend class minheap;
};

class snode
{
	int ascii_val;
	string code;
	snode* next;
	snode* prev;
public:
	snode()
	{
		ascii_val = 0;
		next = prev = nullptr;
	}
	snode(int d, string k, snode* n = nullptr, snode * p = nullptr)
	{
		ascii_val = d;
		code = k;
		next = n;
		prev = n;
	}

	int return_ascii()
	{
		return ascii_val;
	}

	string return_freq()
	{
		return code;
	}

	void insert(int d, string k, snode*n = nullptr, snode* p = nullptr)
	{
		ascii_val = d;
		code = k;
		next = n;
		prev = p;
	}

	bool operator <(snode d)
	{
		if (this->ascii_val < d.ascii_val)
			return true;
		return false;
	}

	friend class slist;
	friend class hashtable;
	friend class hashtable_code;
	friend class minheap;
};

class dlist
{
	dnode * head;
	
public:
	dlist()
	{
		head = nullptr;

	}
	void insertatstart(int d, int k) /// insert  data at head
	{
		if (head != nullptr) {
			if (head->next != NULL)
			{
				dnode* new1 = new dnode(d, k);
				new1->next = head->next;
				new1->prev = head;
				(head->next)->prev = new1;
				head->next = new1;
			}
			else
			{
				dnode* new1 = new dnode(d, k);
				new1->next = nullptr;
				head->next = new1;
				new1->prev = head;
			}
		}
		else
		{
			head = new dnode(d, k);
		}
	}

	bool search(int d) // searches the data in the list and return true if found otherwise false.
	{
		if (head != nullptr)
		{
			dnode * ptr = head;
			while (ptr != nullptr)
			{
				if (ptr->ascii == d)
					return true;
				ptr = ptr->next;
			}
		}
		return false;
	}

	void increment_frequency(int d) // this function increments the frequency if ascii is found.
	{
		if (head != nullptr)
		{
			dnode * ptr = head;
			while (ptr != nullptr)
			{
				if (ptr->ascii == d)
					ptr->freq = ptr->freq + 1;
				ptr = ptr->next;
			}
		}
	}

	int count_nodes() // counts number of nodes in that list.
	{
		int count = 0;
		dnode * ptr = head;
		if (head != nullptr)
		{
			while (ptr != nullptr)
			{
				count++;
				ptr = ptr->next;
			}
			return count;
		}
		else
			return 0;

	}

	friend class hashtable;

	~dlist()
	{
		if (head != nullptr)
			delete [] head;

	}
};

class slist
{
	snode * head_s;

public:
	slist()
	{
		head_s = nullptr;

	}
	void insertatstart(int d, string k) /// insert  data at head
	{
		if (head_s != nullptr) {
			if (head_s->next != NULL)
			{
				snode* new1 = new snode(d, k);
				new1->next = head_s->next;
				new1->prev = head_s;
				(head_s->next)->prev = new1;
				head_s->next = new1;
			}
			else
			{
				snode* new1 = new snode(d, k);
				new1->next = nullptr;
				head_s->next = new1;
				new1->prev = head_s;
			}
		}
		else
		{
			head_s = new snode(d, k);
		}
	}

	string search(int d) // searches the data in the list and return true if found otherwise false.
	{
		if (head_s != nullptr)
		{
			snode * ptr = head_s;
			while (ptr != nullptr)
			{
				if (ptr->ascii_val == d)
					return ptr->code ;
				ptr = ptr->next;
			}
		}
		return "-1";
	}

	friend class hashtable_code;

	~slist()
	{
		if (head_s != nullptr)
			delete[] head_s;
	}


};


int global_count=0; // global variable for the count of distinct elements.


class hashtable_code
{
	slist data[15];
public:
	hashtable_code()
	{}

	void search_insert_or_update(int i, string k) //searches that ascii if exist update frequency else inserts it. 
	{
		unsigned int j = i % 15; // hash function.

		data[j].insertatstart(i, k);
	}

	string search(int i)
	{
		string k;
		unsigned int j = i % 15;
		k=data[j].search(i);
		return k;
	}
	
	int code_search(string s)
	{
		int i = 0;
		while (i < 15)
		{
			if (data[i].head_s != nullptr)
			{
				snode *ptr = data[i].head_s;
				while (ptr != nullptr)
				{
					if (ptr->code == s)
						return ptr->ascii_val;
					ptr = ptr->next;
				}
			}
			i++;
		}
		return -1;
	}
};

class minheap
{
	dnode *h;
	int maxsize;
	int heapsize;
public:
	minheap() //default constructor initializes maxheapsize by global_count.
	{
		maxsize = global_count + 1;
		h = new dnode[maxsize];
		heapsize = 0;

	}

	void insert_val(int d, int k, dnode*n=nullptr, dnode* p=nullptr)
	{
		if (heapsize != maxsize)
		{
			heapsize++;
			h[heapsize].insert(d, k,n,p);
		}
		int i = heapsize;
		while (i > 1)
		{
			if (h[i] < h[i / 2])
			{
				swap(h[i], h[i / 2]);
				i = i / 2;
			}
			else
				break;
		}
	}
	void minheapify(int i) // reheaps after data is removed.
	{
		int left = 2 * i;
		int right = 2 * i + 1;
		int minimum = i;
		if (left <= heapsize && h[left] < h[i])
			minimum = left;
		if (right <= heapsize && h[right] < h[i])
			minimum = right;
		if (left <= heapsize && h[left] < h[i] && right <= heapsize && h[right] < h[i])
		{
			if (h[left] < h[right])
				minimum = left;
			else
				minimum = right;
		}
		if (i != minimum)
		{
			swap(h[i], h[minimum]);
			minheapify(minimum);
		}
	}
	void extractmin(int &a, int &f, dnode*&n,dnode*&p)// extracts minimum and send back.
	{
		a = h[1].ascii;
		f = h[1].freq;
		n = h[1].next;
		p = h[1].prev;
		h[1].ascii = h[heapsize].ascii;
		h[1].freq = h[heapsize].freq;
		h[1].next = h[heapsize].next;
		h[1].prev = h[heapsize].prev;
		heapsize--;
		minheapify(1);
	}

	void building_tree() // will reduce the heap to one node that contains the complete tree.//left=next;right=prev
	{
		if (heapsize > 1)
		{
			int a1 = 0, f1 = 0,a2=0,f2=0;
			dnode *n1; dnode *n2;
			dnode *p1; dnode *p2;
			while (heapsize > 1)
			{
				extractmin(a1, f1,n1,p1);
				extractmin(a2, f2,n2,p2);
				dnode *n = new dnode(a1, f1,n1,p1);
				dnode *p = new dnode(a2, f2,n2,p2);
				insert_val(a1 + a2,0,n,p);
			}
		}
	}

	void printheap()
	{
		for (int i = 1; i <= heapsize; i++)
		{
			cout << h[i].ascii<< " "<<h[i].freq<< endl;
		}
	}



	void building(dnode* ptr, string &k, hashtable_code &c)
	{
		if (ptr->next==nullptr && ptr->prev==nullptr)
		{
			c.search_insert_or_update(ptr->ascii, k);
		}
		else
		{
			k.push_back('0');
			building(ptr->next, k, c);
			k.pop_back();
			k.push_back('1');
			building(ptr->prev, k, c);
			k.pop_back();
		}
	}

	void build_code(hashtable_code &c) //wraper function for traversal
	{
		string k;
		dnode *ptr = h;
		ptr = &ptr[1];
		building(ptr, k, c);
	}

};

class hashtable
{
	dlist data[15];
public:
	hashtable()
	{
	}

	void search_insert_or_update(int i) //searches that ascii if exist update frequency else inserts it. 
	{
		int k = i % 15; // hash function.

		if (data[k].search(i))// element already exist then increment.
		{
			data[k].increment_frequency(i);
		}
		else //otherwise add at the start.
		{
			data[k].insertatstart(i, 1);
		}
	}

	void count_elements() // counts the number of distinct elements in each list.
	{
		for (int i = 0; i < 15; i++)
		{
			global_count += data[i].count_nodes();
		}
	}

	void add_items(minheap &h)
	{
		int d = 0, k = 0;
		for (int i = 0; i < 15; i++)
		{
			if (data[i].head != nullptr)
			{
				dnode* ptr = data[i].head;
				while (ptr != nullptr)
				{
					d = ptr->ascii;
					k = ptr->freq;
					h.insert_val(d, k);
					ptr = ptr->next;
				}
			}

		}
	}


};

void filing(hashtable &h) // filling process in which data is copies in hashtable h.
{
	ifstream fin ("data.txt");
	char ascii;
	while (!fin.eof())
	{
		if (!fin.eof())
		{
			fin.get(ascii);
		} //change.
		unsigned char i = ascii;
		h.search_insert_or_update(i);
	}
}

int stopend = 0;

void encoder(hashtable_code f)
{
	ifstream fin("data.txt");
	ofstream fout("output.txt",ios::binary);
	char ascii;
	string code;
	int code_size;
	int maxbits = 7;// maxbits that can be shifted.
	char variable = 0;// variable that we are going to compress.
	int i = 0;//variable for string traversal.
	char variable2 = 0;
	if (!fin.eof()) {
		fin.get(ascii);//change
		unsigned char j = ascii;
		code = f.search(j); // returns the code for that particulare ascii.
		code_size = code.length(); // returns the length of that code.
	}
	while (!fin.eof())
	{

		char c;// for bit by bit removal from code.
			while (maxbits > -1 && i < code_size)
			{
				c = code[i];
				//if (c == 48) // if zero.
				//{
				//	maxbits--;
				//}
				if (c == 49) // or else if one.
				{
					variable2++;
					variable2 = variable2 << maxbits;
					variable = variable | variable2;
					variable2 = 0;
				}
				i++;
				maxbits--;
			}


			if (maxbits == -1 && i < code_size)
			{
				fout.put (variable);
				maxbits = 7;
				variable = 0;
			}
			else if (i >= code_size && maxbits != -1)
			{
				if (!fin.eof())
				{
					fin.get(ascii);
				}//change
				unsigned char j = (unsigned char)ascii;
				code = f.search(j); // returns the code for that particulare ascii.
				code_size = code.length(); // returns the length of that code.
				i = 0;
			}
			else
			{
				fout.put (variable);
				maxbits = 7;
				variable = 0;
				if (!fin.eof())
				{
					fin.get(ascii);
				}//change
				unsigned char j = (unsigned char)ascii;
				code = f.search(j); // returns the code for that particulare ascii.
				code_size = code.length(); // returns the length of that code.
				i = 0;
			}
	}
	if (maxbits<7)
	{
	/*	variable = variable >> maxbits;*/
		fout.put(variable);
		stopend = 7-maxbits;
	}
}

void decoder(hashtable_code f)
{
	ifstream fin("output.txt",ios::binary);
	ofstream fout("decoder.txt");

	char input;// takes input.
	string in;// in will sent for the code and will be updated.
	int maxbits = 8;
	int variable=128;//for and purposes.
	int ascii; //if code found then its ascii comes in this.
	char endoffile;

	while (!fin.eof())
	{
		if (!fin.eof()) {
			fin.get(input);
		}
		fin.peek();
		if (fin.eof())
		{
			for (int k = 0; k < stopend; k++)
			{
				variable = variable & input;
				if (variable == 128)
					in.push_back('1');
				else
					in.push_back('0');
				ascii = f.code_search(in);
				if (ascii != -1)
				{
					fout << (char)ascii;
					in = "";
				}
				input = input << 1;
				variable = 128;
			}
		}
		else
		{
			for (int k = 0; k < 8; k++)
			{
				variable = variable & input;
				if (variable == 128)
					in.push_back('1');
				else
					in.push_back('0');
				ascii = f.code_search(in);
				if (ascii != -1)
				{
					fout << (char)ascii;
					in = "";
				}
				input = input << 1;
				variable = 128;
			}
		}
	}

}


int main()
{
	hashtable h;
	hashtable_code c;
	filing(h);
	h.count_elements();
	minheap k;
	h.add_items(k);
	k.printheap();
	k.building_tree();
	k.build_code(c);

	encoder(c);
	decoder(c);

	cout << "ending";

	system("pause");
}