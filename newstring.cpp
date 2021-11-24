#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>

class String{

private:
int size;
char* ptr;
static const int LIM = 80;

public:
String() {size = 0; ptr = nullptr;}
String(const char*);
String(const String&); 
String(String&&);
String& operator=(String&&); 
~String();


int get_size(){ return size;}
String(unsigned int, char);
String Substr(int pos, int n);
void Push_back(char);
void Push_front(char);
friend bool operator==(const String &, const String &);
friend bool operator!=(const String &, const String &);
friend bool operator<(const String &, const String &);
friend bool operator>(const String &,const String &);
friend std::ostream& operator<<(std::ostream &,const String &);
friend std::istream& operator>>(std::istream &,  String &);
String& operator=(const String &);
char& operator[](int);
const char& operator[] (int) const;
const char& at(int) const;
String operator+(const String& rhs);
String operator+(char ch);
String& operator+=(const String& rhs);
void pop_back();
void pop_front();
String erase(int index, int count);
void erase(int);
bool empty() {return size == 0;}
void clear();
void insert (int index, String str);
void insert (int index, char ch);
void insert(const int index, int count, char ch);
int  find (const String&);
int  find (const char);
void replace(int, String);

void replace(int pos, char ch) {ptr[pos] = ch;}
static int stoi(String);

};
/////////////////////////

int String::find(const String& rhs) 
{ 

int count = 0;

int j = 0;
int i;
for( i = 0; i < this->size; ++i)
{
   if(ptr[i] == rhs.ptr[j++])
{
   ++count;
}
else if(count == rhs.size)
{
 break;
}

else if(ptr[i] != rhs[i] && count == rhs.size - 1)
{
	--i;
	j = 0;
	count = 0;
}

else
{
 j = 0;
count = 0;

}

}

if(count == rhs.size)
{

std::cout << "Find it";
return i - rhs.size;

}
else
{
std::cout << "couldn't find it";
return -1;

} 
}

/////////////////////

int String::stoi(String str)
{ 

	std::vector<int> vec;
	for(int i = 0; i < str.get_size(); ++i)
{ 

vec.push_back(str[i] - 48); 

}

int res = 0;

for(int i = vec.size() - 1; i >= 0; --i ) 
{ 

res += vec[i] * pow(10, vec.size() - i - 1);

} 

return res;

} 

//////////////
void String::replace(int index, String str)
{ 
 String tmp = this -> Substr(0, index);
 String tmp2 = this -> Substr(tmp.size + str.size, this->size);

 *this = tmp + str;
 *this += tmp2;  

} 


void String::Push_front(char ch)
{
      char* nptr = new char[size + 1];

      for(int i = 0; i < size; ++i)
      {
	      nptr[i + 1] = ptr[i];
      }

      nptr[0] = ch;
      delete [] ptr;
      ptr = nptr;
      ++size;
      ptr[size] = '\0';
}


void String::clear()
{
while(size --)
{
 this->pop_back();
}

}

int String::find(const char ch)
{

for(int i = 0; i < size; ++i)
if(ch == ptr[i]){
 return i;}

return -1;

}
void String::insert(int index, String str)
{
        String tmp = this->Substr(0, index);
        String tmp2 = this->Substr(index, size);
        
        *this = tmp + str;
        *this += tmp2;
        
        this->size += str.size;
}

String String::erase(int index, int count)
{

String res = *this;


while(count--)
{

res.erase(index);

}
return res;

}

String String::operator+(char ch)
{
String res;
res = *this;
res.Push_back(ch);
return res;
}


String& String::operator+= (const String& rhs)
{
	*this = *this + rhs;
	return *this;
}


String String::operator+(const String& rhs)
{

String res;

res.size = this->size + rhs.size;
res.ptr  = new char[res.size + 1];
res.ptr[res.size] = '\0';
std::strcpy(res.ptr, this->ptr);


for(int i = 0; i < rhs.size; ++i) 
{
res.ptr[this->size++] = rhs[i];
}

return res;

}


void String::Push_back(char ch)
{

char* nptr = new char[this -> size + 2];

for(int i = 0; i < this -> size; ++i){
 nptr[i] = this -> ptr[i];}
 
nptr[size] = ch;
delete [] ptr;
++size;
ptr = nptr;

}

String String::Substr(int pos, int n)
{
String res; 
res.size = n - pos;
res.ptr = new char[res.size + 2];

int j = 0;
for(int i = pos;  i <= n; ++i)
{
 res.ptr[j++] = this->ptr[i];
 
}
return res;
}

String& String::operator=(String&& rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	delete [] ptr;
	this->ptr = rhs.ptr;
	this->size = rhs.size;

	rhs.ptr = nullptr;
	rhs.size = 0;
       
        return *this;	
	
}	



String::String(String&& rhs)
{ 

this->size = rhs.size;
this->ptr = rhs.ptr;

rhs.size = 0;
rhs.ptr = nullptr;

}

String::String(unsigned int size, char ch)
{
ptr = new char[size + 1];

int i = 0;
while(size--)
{
ptr[i] = ch;
++i;
}

}


String::String(const char* chp)
{
size = std::strlen(chp);
ptr = new char[size + 1];
std::strcpy(ptr, chp);
}

String::String(const String& s1)
{
size = s1.size;
ptr = new char[size + 1];
ptr[size] = '\0';
std::strcpy(ptr, s1.ptr);

}

String::~String(){ delete [] ptr;}


bool operator>(const String & s1, const String& s2)
{
 return s1.size > s2.size ? true : false;

}

bool operator<(const String & s1, const String & s2)
{
return !(s1 > s2);

}

bool operator==(const String & s1, const String & s2)
{

int count = 0;
for(int i = 0; i < strlen(s1.ptr); ++i)
 {
if(s1[i] == s2[i])
{
++count;
}
 
 }
return count == s1.size;

}

bool operator != (const String & s1, const String & s2)
{
return !(s1 == s2);
}

std::ostream& operator<<(std::ostream & os, const String & s1){

os << s1.ptr;
return os;

}

String & String::operator=(const String & s1)
{
 if(this == &s1){
  return *this;}

delete [] ptr;
size = s1.size;
ptr = new char[size + 1];
std::strcpy(ptr, s1.ptr);
return *this;
}

char& String::operator[](int i) 
{
return ptr[i];
}

const char& String::operator[] (int i) const
{
 return ptr[i];
}

const char& String::at(int i) const
{
if(i < 0 || i > size)
{
 std::cout << "error";
 exit(7);
}
else
  return ptr[i];

}

std::istream& operator>>(std::istream & is,  String & s1)
{
char temp[String::LIM];
is.get(temp, String::LIM);

if(is)
{
 s1 = temp;
}

while(is && is.get() != '\n')
{
  continue;
}
return is;

}


void String::erase(int index)
{


if(index == size - 1)
{
pop_back();

}
else if(index == 0)
{
pop_front();
}
else
{

 char* nptr = new char[size - 1];
 
 for(int i = 0; i < index; ++i)
{ 
std::cout << ptr[i] << std::endl;
nptr[i] = ptr[i];
}
 for(int i = index + 1; i < size; ++i)
{
 std::cout << ptr[i] << std::endl;
 nptr[i - 1] = ptr[i];
}

--size;

delete [] ptr;

ptr = nptr;
ptr[size] = '\0';

}
}


void String::pop_back()
{ 
char* nptr = new char[size - 1];

for(int i = 0; i < size - 1; ++i)
{
nptr[i] = ptr[i];
}

delete [] ptr;
ptr = nptr;
--size;
nptr[size] = '\0';
} 

void String::pop_front()
{
char* nptr = new char[size - 1];

int j = 1;
for(int i = 0; i < size; ++i, ++j)
 nptr[i] = ptr[j];

delete [] ptr;
nptr[size] = '\0';
ptr = nptr;

--size;
} 

int main()
{
	String str("aram");
	std::cout << str.find("ra");
	
}
