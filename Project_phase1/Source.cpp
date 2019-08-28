#include <iostream>
#include <fstream>
using namespace std;

class ad{ //abstract class
protected:
	char companyName[50];
	float price; //price per month
	int width;
	int length;
public:
	float getPrice(){
		return this->price;
	}

	//pure virtual methods
	virtual void getShape() = 0;
	virtual float ppcValue() = 0; //pay per click
	
	//virtual methods
	virtual void getInfo(){
		cout << endl << "The ad from " << companyName << ", which pays us " << price
			<< "$/month, has a size of " << width << "pX" << length << "p.";
	}

	virtual int totalNoPixels(){
		return this->width * this->length;
	}
};

class banner :public ad{
protected:
	char position[20]; //top part, bottom, left, right side, center, etc.
public:
	banner(char* name, float price, int w, int l, char* position){
		strcpy(companyName, name);
		this->price = price;
		width = w;
		length = l;
		strcpy(this->position, position);
	}

	void getInfo(){
		cout << endl << "The banner from " << companyName << ", which pays us " << price
			<< "$/month, has a size of " << width << "pX" << length << "p, and is on the "
			<< position << " of the page.";
	}

	void getShape(){
		if (this->width == this->length)
			cout << "square";
		else if (this->width < this->length)
			cout << "horizontal rectangle";
		else cout << "vertical rectangle";
	}

	float ppcValue(){
		return this->price / 5000;
	}
};

class popUp :public banner{
protected:
	int time; //seconds
public:
	popUp(char* name, float price, int w, int l, char* position, int seconds) :banner(name, price, w, l, position){
		time = seconds;
	}

	void getInfo(){
		cout << endl << "The pop-up ad from " << companyName << ", which pays us " << price
			<< "$/month, has a size of " << width << "pX" << length << "p, is on the "
			<< position << " of the page, and it lasts " << time << "s.";
	}

	float ppcValue(){
		return this->price / 10000;
	}
};

class gif :public banner{
protected:
	int frames;
public:
	gif(char* name, float price, int w, int l, char* position, int frames) :banner(name, price, w, l, position){
		this->frames = frames;
	}

	void getInfo(){
		cout << endl << "The gif banner from " << companyName << ", which pays us " << price
			<< "$/month, has a size of " << width << "pX" << length << "p, is on the "
			<< position << " of the page, and it has " << frames << " frames.";
	}

	float ppcValue(){
		return this->price / 7000;
	}

	int totalNoPixels(){
		return this->width * this->length * this->frames;
	}
};

class mediaAd :public ad{ //abstract
protected:
	int duration; //in seconds
public:
	float ppcValue(){
		return this->price / 4000;
	}
};

class videoAd :public mediaAd{
protected:
	int fps;
public:
	videoAd(char* name, float price, int w, int l, int seconds, int frames){
		strcpy(companyName, name);
		this->price = price;
		width = w;
		length = l;
		duration = seconds;
		fps = frames;
	}

	void getInfo(){
		cout << endl << "The video ad from " << companyName << ", which pays us " << price <<
			"$/month, has a resolution of " << width << "pX" << length << "p at " << fps << 
			" fps, and it lasts " << duration << "s.";
	}

	void getShape(){
		cout << "4:3";
	}

	int totalNoPixels(){
		return this->width * this->length * this->duration * this->fps;
	}
};

class audioAd :public mediaAd{
protected:
	char gender; // M or F
public:
	audioAd(char* name, float price, int seconds, char sex){
		strcpy(companyName, name);
		this->price = price;
		width = 0;
		length = 0;
		duration = seconds;
		gender = sex;
	}

	void getInfo(){
		cout << endl << "The audio ad from " << companyName << ", which pays us " << price <<
			"$/month, has a duration of " << duration << "s, and is narrated by a " << gender << ".";
	}

	void getShape(){
		cout << "audio";
	}

	int totalNoPixels(){
		return 0;
	}
};

class User{
protected:
	const int id;
	char* name;
	char username[50];
	char password[50];
	char gender;
	int age;
	int xp;
	static int noUsers;

public:
	User(char* username, char* password) :id(User::noUsers){
		User::noUsers += 1;
		this->name = new char[strlen("Name") + 1];
		strcpy(this->name, "Name");
		strcpy(this->username, username);
		strcpy(this->password, password);
		this->gender = 'm';
		this->age = 0;
		this->xp = 0;
	}

	User(char* username, char* password, char gender) :id(User::noUsers){
		User::noUsers += 1;
		this->name = new char[strlen("Name") + 1];
		strcpy(this->name, "Name");
		strcpy(this->username, username);
		strcpy(this->password, password);
		this->gender = gender;
		this->age = 0;
		this->xp = 0;
	}

	//destructor
	~User(){
		delete[] this->name;
	}

	//copy constructor
	User(User& u) :id(noUsers++){
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
	}

	void display(){
		cout << endl << "User's name: " << this->name;
		cout << endl << "User's username: " << this->username;
		cout << endl << "User's password: " << this->password;
		cout << endl << "User's id: " << this->id;
		cout << endl << "User's gender: " << this->gender;
		cout << endl << "User's age: " << this->age;
		cout << endl << "User's Xpoints: " << this->xp;
		cout << endl;
	}

	//getters
	char* getName(){
		return this->name;
	}

	char* getUsername(){
		return this->username;
	}

	char* getPassword(){
		return this->password;
	}

	int getId(){
		return this->id;
	}

	char getGender(){
		return this->gender;
	}

	int getAge(){
		return this->age;
	}

	int getXp(){
		return this->xp;
	}

	//setters
	void setName(char* newName){
		delete[] this->name;
		this->name = new char[strlen(newName) + 1];
		strcpy(this->name, newName);
	}

	void setUsername(char* newUsername){
		if (strlen(newUsername) <= 50)
			strcpy(this->username, newUsername);
		else
			cout << endl << "Please enter an username of max 50 chars!";
	}

	void setPassword(char* newPassword){
		if (strlen(newPassword) <= 50)
			strcpy(this->password, newPassword);
		else
			cout << endl << "Please enter a password of max 50 chars!";
	}

	void setGender(char newGender){
		if (newGender == 'm' || newGender == 'M' || newGender == 'f' || newGender == 'F')
			this->gender = newGender;
		else
			cout << endl << "Please enter M or F!";
	}

	void setAge(int newAge){
		if (newAge >= 14 && newAge <= 100)
			this->age = newAge;
		else
			cout << endl << "Please enter an age between 14 and 100";
	}

	void addXp(int newXp){
		this->xp += newXp;
	}


	//operators
	void operator=(User& u){
		delete[] this->name;
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
	}

	User operator+(int exp){
		User result = *this;
		result.xp += exp;
		return result;
	}

	User operator+=(int exp){
		this->xp += exp;
		return *this;
	}

	User operator*(double exp){
		User result = *this;
		result.xp = (double)(result.xp * exp);
		return result;
	}

	User operator/(double exp){
		User result = *this;
		result.xp = (double)(result.xp / exp);
		return result;
	}

	friend istream& operator>>(istream& in, User& u);

};
int User::noUsers = 0;
istream& operator>>(istream& in, User& u){
	cout << endl << "User's name: ";
	delete[] u.name;
	char buff[1000];
	cin.ignore();
	gets(buff);
	u.name = new char[strlen(buff) + 1];
	strcpy(u.name, buff);
	cout << "User's username: ";
	char newUsername[500];
	in >> newUsername;
	if (strlen(newUsername) <= 50)
		strcpy(u.username, newUsername);
	cout << "User's password: ";
	char newPassword[500];
	in >> newPassword;
	if (strlen(newPassword) <= 50)
		strcpy(u.password, newPassword);
	cout << "User's gender: ";
	char newGender;
	in >> newGender;
	if (newGender == 'm' || newGender == 'M' || newGender == 'f' || newGender == 'F')
		u.gender = newGender;
	cout << "User's age: ";
	int newAge;
	in >> newAge;
	if (newAge >= 14 && newAge <= 100)
		u.age = newAge;
	return in;
}
ostream& operator<<(ostream& out, User& u){
	out << endl << "User's name: " << u.getName();
	out << endl << "User's username: " << u.getUsername();
	out << endl << "User's password: " << u.getPassword();
	out << endl << "User's id: " << u.getId();
	out << endl << "User's gender: " << u.getGender();
	out << endl << "User's age: " << u.getAge();
	out << endl << "User's Xpoints: " << u.getXp();
	out << endl;
	return out;
}

class moderatorUser :public User{
protected:
	int noISolved; //nr of issues solved
public:
	moderatorUser(char* username, char* password) :User(username, password){
		this->noISolved = 0;
	}

	moderatorUser(char* username, char* password, char gender) :User(username, password, gender){
		this->noISolved = 0;
	}

	moderatorUser(moderatorUser& u):User(u){
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
		this->noISolved = u.noISolved;
	}

	void display(){
		cout << endl << "User's name: " << this->name;
		cout << endl << "User's username: " << this->username;
		cout << endl << "User's password: " << this->password;
		cout << endl << "User's id: " << this->id;
		cout << endl << "User's gender: " << this->gender;
		cout << endl << "User's age: " << this->age;
		cout << endl << "User's Xpoints: " << this->xp;
		cout << endl << "Issues solved by user: " << this->noISolved;
		cout << endl;
	}

	void addXp(User& u, int newXp){
		u.addXp(newXp);
	}

	int getNoISolved(){
		return this->noISolved;
	}

	void operator=(moderatorUser& u){
		delete[] this->name;
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
		this->noISolved = u.noISolved;
	}

	moderatorUser operator*(double exp){
		moderatorUser result = *this;
		result.xp = (double)(result.xp * exp);
		return result;
	}

	moderatorUser operator/(double exp){
		moderatorUser result = *this;
		result.xp = (double)(result.xp / exp);
		return result;
	}

	friend istream& operator>>(istream& in, moderatorUser& u);

};
istream& operator>>(istream& in, moderatorUser& u){
	cout << endl << "User's name: ";
	delete[] u.name;
	char buff[1000];
	cin.ignore();
	gets(buff);
	u.name = new char[strlen(buff) + 1];
	strcpy(u.name, buff);
	cout << "User's username: ";
	char newUsername[500];
	in >> newUsername;
	if (strlen(newUsername) <= 50)
		strcpy(u.username, newUsername);
	cout << "User's password: ";
	char newPassword[500];
	in >> newPassword;
	if (strlen(newPassword) <= 50)
		strcpy(u.password, newPassword);
	cout << "User's gender: ";
	char newGender;
	in >> newGender;
	if (newGender == 'm' || newGender == 'M' || newGender == 'f' || newGender == 'F')
		u.gender = newGender;
	cout << "User's age: ";
	int newAge;
	in >> newAge;
	if (newAge >= 14 && newAge <= 100)
		u.age = newAge;
	return in;
}
ostream& operator<<(ostream& out, moderatorUser& u){
	out << endl << "User's name: " << u.getName();
	out << endl << "User's username: " << u.getUsername();
	out << endl << "User's password: " << u.getPassword();
	out << endl << "User's id: " << u.getId();
	out << endl << "User's gender: " << u.getGender();
	out << endl << "User's age: " << u.getAge();
	out << endl << "User's Xpoints: " << u.getXp();
	out << endl << "Issues solved by user: " << u.getNoISolved();
	out << endl;
	return out;
}

class adminUser : public moderatorUser{
public:
	adminUser(char* username, char* password) :moderatorUser(username, password){

	}

	adminUser(char* username, char* password, char gender) :moderatorUser(username, password, gender){

	}

	adminUser(adminUser& u) :moderatorUser(u){
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
		this->noISolved = u.noISolved;
	}

	void operator=(adminUser& u){
		delete[] this->name;
		this->name = new char[strlen(u.name) + 1];
		strcpy(this->name, u.name);
		strcpy(this->username, u.username);
		strcpy(this->password, u.password);
		this->gender = u.gender;
		this->age = u.age;
		this->xp = u.xp;
		this->noISolved = u.noISolved;
	}

	adminUser operator*(double exp){
		adminUser result = *this;
		result.xp = (double)(result.xp * exp);
		return result;
	}

	adminUser operator/(double exp){
		adminUser result = *this;
		result.xp = (double)(result.xp / exp);
		return result;
	}

	friend istream& operator>>(istream& in, adminUser& u);

};
istream& operator>>(istream& in, adminUser& u){
	cout << endl << "User's name: ";
	delete[] u.name;
	char buff[1000];
	cin.ignore();
	gets(buff);
	u.name = new char[strlen(buff) + 1];
	strcpy(u.name, buff);
	cout << "User's username: ";
	char newUsername[500];
	in >> newUsername;
	if (strlen(newUsername) <= 50)
		strcpy(u.username, newUsername);
	cout << "User's password: ";
	char newPassword[500];
	in >> newPassword;
	if (strlen(newPassword) <= 50)
		strcpy(u.password, newPassword);
	cout << "User's gender: ";
	char newGender;
	in >> newGender;
	if (newGender == 'm' || newGender == 'M' || newGender == 'f' || newGender == 'F')
		u.gender = newGender;
	cout << "User's age: ";
	int newAge;
	in >> newAge;
	if (newAge >= 14 && newAge <= 100)
		u.age = newAge;
	return in;
}
ostream& operator<<(ostream& out, adminUser& u){
	out << endl << "User's name: " << u.getName();
	out << endl << "User's username: " << u.getUsername();
	out << endl << "User's password: " << u.getPassword();
	out << endl << "User's id: " << u.getId();
	out << endl << "User's gender: " << u.getGender();
	out << endl << "User's age: " << u.getAge();
	out << endl << "User's Xpoints: " << u.getXp();
	out << endl << "Issues solved by user: " << u.getNoISolved();
	out << endl;
	return out;
}

class Reply{
private:
	friend class Subject;
	friend class Domain;
	const int id;
	bool bestanswer;
	char username[50];
	char* body;
	int thumbsup;
	static int noReplies;

public:
	Reply() :id(Reply::noReplies){
		Reply::noReplies += 1;
		this->bestanswer = 0;
		strcpy(this->username, "default_username");
		this->body = new char[1];
		strcpy(this->body, "\0");
		this->thumbsup = 0;
	}

	Reply(bool bestanswer, char* username) :id(Reply::noReplies){
		Reply::noReplies += 1;
		this->bestanswer = bestanswer;
		strcpy(this->username, username);
		this->body = new char[strlen("Body") + 1];
		strcpy(this->body, "Body");
		this->thumbsup = 0;
	}

	Reply(bool bestanswer) :id(Reply::noReplies){
		Reply::noReplies += 1;
		this->bestanswer = bestanswer;
		strcpy(this->username, "Username");
		this->body = new char[strlen("Body") + 1];
		strcpy(this->body, "Body");
		this->thumbsup = 0;
	}

	//destructor
	~Reply(){
		delete[] this->body;
	}

	//copy constructor
	Reply(Reply& r) :id(noReplies++){
		this->bestanswer = r.bestanswer;
		strcpy(this->username, r.username);
		this->body = new char[strlen(r.body) + 1];
		strcpy(this->body, r.body);
		this->thumbsup = r.thumbsup;
	}

	void display(){
		cout << endl << "Reply ID: " << this->id;
		if (this->bestanswer)
			cout << endl << "Marked as the best answer!";
		cout << endl << "Wrote by: " << this->username;
		cout << endl << "Reply: " << this->body;
		cout << endl << "Nr of thumbsup: " << this->thumbsup;
		cout << endl;
	}

	//getters
	int getId(){
		return this->id;
	}

	bool getBestanswer(){
		return this->bestanswer;
	}

	char* getUsername(){
		return this->username;
	}

	char* getBody(){
		return this->body;
	}

	int getThumbsup(){
		return this->thumbsup;
	}

	//setters
	void setBestanswer(int newBestanswer){
		this->bestanswer = newBestanswer;
	}

	void setUsername(char* newUsername){
		if (strlen(newUsername) <= 50)
			strcpy(this->username, newUsername);
		else
			cout << endl << "The username's nr of chars exceeds 50! ";
	}

	void setBody(char* newBody){
		delete[] this->body;
		this->body = new char[strlen(newBody) + 1];
		strcpy(this->body, newBody);
	}

	void addThumbsup(){ //it will be accesible in the future only for moderators
		this->thumbsup++;
	}

	void operator=(Reply& r){
		this->bestanswer = r.bestanswer;
		strcpy(this->username, r.username);
		delete[] this->body;
		this->body = new char[strlen(r.body) + 1];
		strcpy(this->body, r.body);
		this->thumbsup = r.thumbsup;
	}

	bool operator==(Reply& r){
		if (this->bestanswer == r.bestanswer && strcmp(this->username, r.username) == 0
			&& strcmp(this->body, r.body) == 0 && this->thumbsup == r.thumbsup)
			return true;
		else
			return false;
	}

	bool operator!=(Reply& r){
		if (*this == r)
			return false;
		else
			return true;
	}

	friend istream& operator>>(istream& in, Reply& r);

};
int Reply::noReplies = 0;
istream& operator>>(istream& in, Reply& r){
	cout << endl << "Best answer? ";
	in >> r.bestanswer;
	cout << "Wrote by: ";
	char newUsername[500];
	in >> newUsername;
	if (strlen(newUsername) <= 50)
		strcpy(r.username, newUsername);
	cout << "Reply: ";
	delete[] r.body;
	char newReply[9999];
	cin.ignore();
	gets(newReply);
	r.body = new char[strlen(newReply) + 1];
	strcpy(r.body, newReply);
	return in;
}
ostream& operator<<(ostream& out, Reply& r){
	out << endl << "Reply ID: " << r.getId();
	if (r.getBestanswer())
		out << endl << "Marked as the best answer!";
	out << endl << "Wrote by: " << r.getUsername();
	out << endl << "Reply: " << r.getBody();
	out << endl << "Nr of thumbsup: " << r.getThumbsup();
	out << endl;
	return out;
}

class Subject{ //(ex: Why my code doesn't work? *code*)
private:
	friend class Domain;
	friend class Reply;
	const int id;
	char title[200];
	char username[50];
	char* question;
	int difficulty;
	Reply* replies;
	int noReplies;
	int status; //0 = unsolved, n = index + 1 of the correct answer
	static int noSubjects;

public:
	Subject(char* title = "", char* username = "") :id(Subject::noSubjects){
		Subject::noSubjects += 1;
		strcpy(this->title, title);
		strcpy(this->username, username);
		this->question = new char[strlen("Question") + 1];
		strcpy(this->question, "Question");
		this->difficulty = 0;
		this->replies = NULL;
		this->noReplies = 0;
		this->status = 0;
	}

	Subject(char* title, int difficulty) :id(Subject::noSubjects){
		Subject::noSubjects += 1;
		strcpy(this->title, title);
		strcpy(this->username, "Username");
		this->question = new char[strlen("Question") + 1];
		strcpy(this->question, "Question");
		this->difficulty = difficulty;
		this->noReplies = 0;
		this->replies = NULL;
		this->status = 0;
	}

	//destructor
	~Subject(){
		delete[] this->question;
		delete[] this->replies;
	}

	//copy constructor
	Subject(Subject& s) :id(noSubjects++){
		strcpy(this->title, s.title);
		strcpy(this->username, s.username);
		this->question = new char[strlen(s.question) + 1];
		strcpy(this->question, s.question);
		this->difficulty = s.difficulty;
		this->noReplies = s.noReplies;
		this->replies = new Reply[s.noReplies];
		for (int i = 0; i < s.noReplies; i++)
			this->replies[i] = s.replies[i];
		this->status = s.status;
	}

	void display(){
		cout << endl << "Subject: " << this->title;
		cout << endl << "ID: " << this->id;
		cout << endl << "Created by: " << this->username;
		cout << endl << "Question: " << this->question;
		cout << endl << "Difficulty: " << this->difficulty;
		cout << endl << "Nr of replies: " << this->noReplies;
		if (this->noReplies){
			cout << endl << "------------------------------";
			cout << endl << "Replies: ";
			for (int i = 0; i < this->noReplies; i++)
				cout << endl << this->replies[i];
			cout << endl << "------------------------------";
		}
		cout << endl << "Status: ";
		if (this->noReplies == 0)
			cout << "Unsolved...";
		else{
			int c = 0;
			for (int i = 0; i < this->noReplies; i++){
				if (this->replies[i].bestanswer){
					this->status = i + 1;
					cout << "The correct answer is reply nr. " << this->status << "!";
					c++;
				}
			}
			if (!c)
				cout << "Unsolved...";
		}
		cout << endl;
	}

	//getters
	char* getTitle(){
		return this->title;
	}

	int getId(){
		return this->id;
	}

	char* getUsername(){
		return this->username;
	}

	char* getQuestion(){
		return this->question;
	}

	int getDifficulty(){
		return this->difficulty;
	}

	int getNoReplies(){
		return this->noReplies;
	}

	Reply getReply(int index){
		if (index >= 0 && index < this->noReplies)
			return this->replies[index];
	}

	int getStatus(){
		return this->status;
	}

	//setters
	void setTitle(char* newTitle){
		if (strlen(newTitle) <= 200)
			strcpy(this->title, newTitle);
		else
			cout << endl << "Please enter a subject title that has less than 200 chars!";
	}

	void setUsername(char* newUsername){
		if (strlen(newUsername) <= 50)
			strcpy(this->username, newUsername);
		else
			cout << endl << "Please enter an username of max 50 chars!";
	}

	void setQuestion(char* newQuestion){
		delete[] this->question;
		this->question = new char[strlen(newQuestion) + 1];
		strcpy(this->question, newQuestion);
	}

	void setDifficulty(int newDifficulty){
		if (newDifficulty <= 10 && newDifficulty > 0)
			this->difficulty = newDifficulty;
		else
			cout << endl << "Please enter a difficulty between 1 and 10";
	}

	void setStatus(int newStatus){
		if (newStatus <= this->noReplies)
			this->status = newStatus;
	}

	void operator=(Subject& s){
		strcpy(this->title, s.title);
		strcpy(this->username, s.username);
		delete[] this->question;
		this->question = new char[strlen(s.question) + 1];
		strcpy(this->question, s.question);
		this->difficulty = s.difficulty;
		this->noReplies = s.noReplies;
		delete[] this->replies;
		this->replies = new Reply[s.noReplies];
		for (int i = 0; i < this->noReplies; i++)
			this->replies[i] = s.replies[i];
		this->status = s.status;
	}

	Subject operator+(Reply& r){
		Subject result = *this;
		Reply* newReplies = new Reply[result.noReplies + 1];
		for (int i = 0; i < result.noReplies; i++)
			newReplies[i] = result.replies[i];
		newReplies[result.noReplies] = r;
		delete[] result.replies;
		result.replies = newReplies;
		result.noReplies += 1;
		return result;
	}

	Subject operator+=(Reply& r){
		Reply* newReplies = new Reply[this->noReplies + 1];
		for (int i = 0; i < this->noReplies; i++)
			newReplies[i] = this->replies[i];
		newReplies[this->noReplies] = r;
		delete[] this->replies;
		this->replies = newReplies;
		this->noReplies += 1;
		return *this;
	}

	Subject operator++(){
		Reply* newReplies = new Reply[this->noReplies + 1];
		for (int i = 0; i < this->noReplies; i++)
			newReplies[i] = this->replies[i];
		Reply r;
		newReplies[this->noReplies] = r;
		delete[] this->replies;
		this->replies = newReplies;
		this->noReplies += 1;
		return *this;
	}

	Subject operator-(Reply& r){
		Subject result = *this;
		Reply* newReplies = new Reply[result.noReplies - 1];
		for (int i = 0; i < result.noReplies; i++){
			if (result.replies[i] == r){
				int j;
				for (j = i; j < result.noReplies - 1; j++){
					newReplies[j] = result.replies[j + 1];
				}
				result.noReplies -= 1;
				i = result.noReplies;
			}
			else
				newReplies[i] = result.replies[i];
		}
		delete[] result.replies;
		result.replies = newReplies;
		return result;
	}

	Subject operator-=(Reply& r){
		Reply* newReplies = new Reply[this->noReplies - 1];
		for (int i = 0; i < this->noReplies; i++){
			if (this->replies[i] == r){
				int j;
				for (j = i; j < this->noReplies - 1; j++){
					newReplies[j] = this->replies[j + 1];
				}
				this->noReplies -= 1;
				i = this->noReplies;
			}
			else
				newReplies[i] = this->replies[i];
		}
		delete[] this->replies;
		this->replies = newReplies;
		return *this;
	}

	Subject operator--(){
		if (this->noReplies == 1){
			this->replies = NULL;
			this->noReplies -= 1;
			return *this;
		}
		else if (this->noReplies > 1){
			Reply* newReplies = new Reply[this->noReplies - 1];
			for (int i = 0; i < this->noReplies - 1; i++)
				newReplies[i] = this->replies[i];
			this->noReplies -= 1;
			delete[] this->replies;
			this->replies = newReplies;
			return *this;
		}
		else{
			cout << endl << "There are no replies!";
			return *this;
		}
	}

	Reply& operator[](int index){
		if (index > 0 && index <= this->noReplies)
			return this->replies[index - 1];
		else
			cout << endl << "A reply with the index " << index << " does not exist!";
	}

	Subject operator*=(Reply& r){
		//this->status = r.getId(); // I would have put the id but it's not stable
		for (int i = 0; i < this->noReplies; i++){
			if (this->replies[i] == r){
				this->status = i + 1;
				this->replies[i].bestanswer = true;
			}
		}
		return *this;
	}

	Subject operator!(){
		this->status = 0;
		for (int i = 0; i < this->noReplies; i++){
			if (this->replies[i].bestanswer){
				this->replies[i].bestanswer = false;
				break;
			}
		}
		return *this;
	}

	explicit operator int(){
		return this->status;
	}

	bool operator==(Subject& s){	
		int c = 0;
		if (this->noReplies == s.noReplies){
			for (int i = 0; i < this->noReplies; i++){
				if (this->replies[i] == s.replies[i])
					c++;
			}
		}
		if (strcmp(this->title, s.title) == 0 && strcmp(this->username, s.username) == 0
			&& strcmp(this->question, s.question) == 0 && this->difficulty == s.difficulty
			&& this->status == s.status && this->noReplies == s.noReplies 
			&& c == s.noReplies)
			return true;
		else
			return false;
	}

	bool operator!=(Subject& s){
		if (*this == s)
			return false;
		else
			return true;
	}

	void readRepliesFile(char* filename){
		ifstream inputFile;
		inputFile.open(filename, ios::in);
		if (inputFile.is_open()){
			inputFile >> this->noReplies;
			this->replies = new Reply[this->noReplies];
			//read the replies
			for (int i = 0; i < this->noReplies; i++){
				inputFile >> this->replies[i].bestanswer;
				inputFile.get();
				inputFile.getline((char*)this->replies[i].username, 50);
				char buffer[1000];
				inputFile.getline((char*)buffer, 1000);
				this->replies[i].setBody(buffer);
				inputFile >> this->replies[i].thumbsup;
			}
			inputFile.close();
		}
	}

	friend istream& operator>>(istream& in, Subject& s);

};
int Subject::noSubjects = 0;
istream& operator>>(istream& in, Subject& s){
	cout << endl << "Subject: ";
	char newTitle[500];
	gets(newTitle);
	if (strlen(newTitle) <= 200)
		strcpy(s.title, newTitle);
	cout << "Created by: ";
	char newUsername[500];
	in >> newUsername;
	if (strlen(newUsername) <= 50)
		strcpy(s.username, newUsername);
	cout << "Question: ";
	delete[] s.question;
	char buffer[9999];
	cin.ignore();
	gets(buffer);
	s.question = new char[strlen(buffer) + 1];
	strcpy(s.question, buffer);
	cout << "Difficulty: ";
	in >> s.difficulty;
	s.noReplies = 0;
	s.replies = NULL;
	s.status = 0;
	return in;
}
ostream& operator<<(ostream& out, Subject& s){
	out << endl << "Subject: " << s.getTitle();
	out << endl << "ID: " << s.getId();
	out << endl << "Created by: " << s.getUsername();
	out << endl << "Question: " << s.getQuestion();
	out << endl << "Difficulty: " << s.getDifficulty();
	out << endl << "Nr of replies: " << s.getNoReplies();
	if (s.getNoReplies()){
		out << endl << "------------------------------";
		out << endl << "Replies: ";
		for (int i = 0; i < s.getNoReplies(); i++)
			out << endl << s.getReply(i);
		out << endl << "------------------------------";
	}
	out << endl << "Status: ";
	if (s.getNoReplies() == 0)
		out << "Unsolved...";
	else{
		int c = 0;
		for (int i = 0; i < s.getNoReplies(); i++){
			if (s.getReply(i).getBestanswer()){
				s.setStatus(i + 1);
				out << "The correct answer is reply nr. " << s.getStatus() << "!";
				c++;
			}
		}
		if (!c)
			out << "Unsolved...";
	}
	out << endl;
	return out;
}

ofstream& operator<<(ofstream& fout, Domain& d);
class Domain{ //(ex: C++, Java, etc)
private:
	const int id;
	char name[30];
	Subject* questions;
	int noQuestions;
	static int noDomains;

public:
	Domain(char* name = "Default") :id(Domain::noDomains){
		Domain::noDomains += 1;
		strcpy(this->name, name);
		this->questions = NULL;
		this->noQuestions = 0;
	}

	~Domain(){
		delete[] this->questions;
	}

	Domain(Domain& d):id(noDomains++){
		strcpy(this->name, d.name);
		this->questions = new Subject[d.noQuestions];
		for (int i = 0; i < d.noQuestions; i++)
			this->questions[i] = d.questions[i];
		this->noQuestions = d.noQuestions;
	}

	//display
	void display(){
		cout << endl << "Domain: " << this->name;
		cout << endl << "No questions: " << this->noQuestions;
		if (this->noQuestions){
			for (int i = 0; i < this->noQuestions; i++){
				cout << endl << endl << "Question "<< i + 1 << ": " << this->questions[i];
			}
		}
	}

	//getters
	char* getName(){
		return this->name;
	}

	int getNoQuestions(){
		return this->noQuestions;
	}

	Subject getQuestions(int index){
		if (index >= 0 && index < this->noQuestions)
			return this->questions[index];
	}

	//setters
	void setName(char* name){
		if (strlen(name) <= 30)
			strcpy(this->name, name);
	}

	//operators
	void operator=(Domain& d){
		strcpy(this->name, d.name);
		delete[] this->questions;
		this->questions = new Subject[d.noQuestions];
		for (int i = 0; i < d.noQuestions; i++)
			this->questions[i] = d.questions[i];
		this->noQuestions = d.noQuestions;
	}

	Domain operator+(Subject& q){
		Domain result = *this;
		Subject* newQuestions = new Subject[result.noQuestions + 1];
		for (int i = 0; i < result.noQuestions; i++)
			newQuestions[i] = result.questions[i];
		newQuestions[result.noQuestions] = q;
		delete[] result.questions;
		result.questions = newQuestions;
		result.noQuestions += 1;
		return result;
	}

	Domain operator+=(Subject& q){
		Subject* newQuestions = new Subject[this->noQuestions + 1];
		for (int i = 0; i < this->noQuestions; i++)
			newQuestions[i] = this->questions[i];
		newQuestions[this->noQuestions] = q;
		delete[] this->questions;
		this->questions = newQuestions;
		this->noQuestions += 1;
		return *this;
	}

	Domain operator-(Subject& q){
		Domain result = *this;
		Subject* newQuestions = new Subject[result.noQuestions - 1];
		for (int i = 0; i < result.noQuestions; i++){
			if (result.questions[i] == q){
				int j;
				for (j = i; j < result.noQuestions - 1; j++){
					newQuestions[j] = result.questions[j + 1];
				}
				result.noQuestions -= 1;
				i = result.noQuestions;
			}
			else
				newQuestions[i] = result.questions[i];
		}
		delete[] result.questions;
		result.questions = newQuestions;
		return result;
	}

	Domain operator-=(Subject& q){
		Subject* newQuestions = new Subject[this->noQuestions - 1];
		for (int i = 0; i < this->noQuestions; i++){
			if (this->questions[i] == q){
				int j;
				for (j = i; j < this->noQuestions - 1; j++){
					newQuestions[j] = this->questions[j + 1];
				}
				this->noQuestions -= 1;
				i = this->noQuestions;
			}
			else
				newQuestions[i] = this->questions[i];
		}
		delete[] this->questions;
		this->questions = newQuestions;
		return *this;
	}

	void readSubjectsFile(char* filename){
		ifstream inputFile;
		inputFile.open(filename, ios::in);
		if (inputFile.is_open()){
			inputFile >> this->noQuestions;
			this->questions = new Subject[this->noQuestions];
			//read the questions
			for (int i = 0; i < this->noQuestions; i++){
				inputFile.get();
				inputFile.getline((char*)this->questions[i].title, 200);
				inputFile.getline((char*)this->questions[i].username, 50);
				char buffer[1000];
				inputFile.getline((char*)buffer, 1000);
				this->questions[i].setQuestion(buffer);
				this->questions[i].noReplies = 0;
				this->questions[i].replies = NULL;
				inputFile >> this->questions[i].difficulty;
			}
			inputFile.close();
		}
	}

	void addRepliesFile(char* filename, int index){
		this->questions[index - 1].readRepliesFile(filename);
	}

	void raportTxt(char* filename){
		ofstream raport;
		raport.open("raport.txt", ios::out);
		if (raport.is_open()){
			raport << *this;
			cout << endl << "Raport issued to " << filename;
			raport.close();
		}
	}

	void binOut(char* filename){
		ofstream savefile;
		savefile.open(filename, ios::out | ios::binary | ios::trunc);
		if (savefile.is_open()){
			//name
			int nameSize = strlen(this->name) + 1;
			savefile.write((char*)&nameSize, sizeof(int));
			savefile.write(this->name, nameSize*sizeof(char));
			//nr of questions
			savefile.write((char*)&this->noQuestions, sizeof(int));
			//questions
			for (int i = 0; i < this->noQuestions; i++){
				//title
				nameSize = strlen(this->questions[i].title) + 1;
				savefile.write((char*)&nameSize, sizeof(int));
				savefile.write(this->questions[i].title, nameSize*sizeof(char));
				//username
				nameSize = strlen(this->questions[i].username) + 1;
				savefile.write((char*)&nameSize, sizeof(int));
				savefile.write(this->questions[i].username, nameSize*sizeof(char));
				//question
				nameSize = strlen(this->questions[i].question) + 1;
				savefile.write((char*)&nameSize, sizeof(int));
				savefile.write(this->questions[i].question, nameSize*sizeof(char));
				//difficulty
				savefile.write((char*)&this->questions[i].difficulty, sizeof(int));
				//nr of replies
				savefile.write((char*)&this->questions[i].noReplies, sizeof(int));
				//replies
				if (this->questions[i].noReplies){
					for (int j = 0; j < this->questions[i].noReplies; j++){
						//best answer
						savefile.write((char*)&this->questions[i].replies[j].bestanswer, sizeof(int));
						//username
						nameSize = strlen(this->questions[i].replies[j].username) + 1;
						savefile.write((char*)&nameSize, sizeof(int));
						savefile.write(this->questions[i].replies[j].username, nameSize*sizeof(char));
						//body
						nameSize = strlen(this->questions[i].replies[j].body) + 1;
						savefile.write((char*)&nameSize, sizeof(int));
						savefile.write(this->questions[i].replies[j].body, nameSize*sizeof(char));
						//thumbs up
						savefile.write((char*)&this->questions[i].replies[j].thumbsup, sizeof(int));
					}
				}
				//status
				savefile.write((char*)&this->questions[i].status, sizeof(int));
			}
			cout << endl << "File saved to " << filename;
			savefile.close();
		}
	}

	void binIn(char* filename){
		ifstream inputFile;
		inputFile.open(filename, ios::in | ios::binary);
		if (inputFile.is_open()){
			int temp;
			//read name
			inputFile.read((char*)&temp, sizeof(int));
			inputFile.read(this->name, temp);
			//read no questions
			inputFile.read((char*)&this->noQuestions, sizeof(int));
			//read questions
			if (this->noQuestions){
				delete[] this->questions;
				this->questions = new Subject[this->noQuestions];
				for (int i = 0; i < this->noQuestions; i++){
					//read title
					inputFile.read((char*)&temp, sizeof(int));
					inputFile.read(this->questions[i].title, temp);
					//read username
					inputFile.read((char*)&temp, sizeof(int));
					inputFile.read(this->questions[i].username, temp);
					//read question
					inputFile.read((char*)&temp, sizeof(int));
					delete[] this->questions[i].question;
					this->questions[i].question = new char[temp];
					inputFile.read(this->questions[i].question, temp);
					//read difficulty
					inputFile.read((char*)&this->questions[i].difficulty, sizeof(int));
					//read nr of replies
					inputFile.read((char*)&this->questions[i].noReplies, sizeof(int));
					//read replies
					if (this->questions[i].noReplies){
						delete[] this->questions[i].replies;
						this->questions[i].replies = new Reply[this->questions[i].noReplies];
						for (int j = 0; j < this->questions[i].noReplies; j++){
							//read best answer
							inputFile.read((char*)&this->questions[i].replies[j].bestanswer, sizeof(int));
							//read username
							inputFile.read((char*)&temp, sizeof(int));
							inputFile.read(this->questions[i].replies[j].username, temp);
							//read body
							inputFile.read((char*)&temp, sizeof(int));
							delete[] this->questions[i].replies[j].body;
							this->questions[i].replies[j].body = new char[temp];
							inputFile.read(this->questions[i].replies[j].body, temp);
							//read thumbs up
							inputFile.read((char*)&this->questions[i].replies[j].thumbsup, sizeof(int));
						}
					}
					//read status
					inputFile.read((char*)&this->questions[i].status, sizeof(int));
				}
			}
			cout << endl << "Savefile loaded from " << filename;
			inputFile.close();
		}
	}

	Domain operator()(char* a, char* b, char* c, int d){
		Domain newDomain(a);
		newDomain.readSubjectsFile(b);
		newDomain.addRepliesFile(c, d);
		*this = newDomain;
		return *this;
	}

	friend istream& operator>>(istream& in, Domain& d);

};
int Domain::noDomains = 0;
ostream& operator<<(ostream& out, Domain& d){
	out << endl << "Domain: " << d.getName();
	out << endl << "No questions: " << d.getNoQuestions();
	if (d.getNoQuestions()){
		for (int i = 0; i < d.getNoQuestions(); i++){
			out << endl << endl << "Question " << i + 1 << ": " << d.getQuestions(i);
		}
	}
	return out;
}
istream& operator>>(istream& in, Domain& d){
	cout << endl << "Domain: ";
	in >> d.name;
	cout << "No questions: ";
	in >> d.noQuestions;
	if (d.noQuestions){
		for (int i = 0; i < d.noQuestions; i++){
			cout << "Question " << i << ": ";
			in >> d.questions[i];
		}
	}
	else{
		d.questions = NULL;
	}
	return in;
}
ofstream& operator<<(ofstream& fout, Domain& d){
	fout << endl << "Domain: " << d.getName();
	fout << endl << "No questions: " << d.getNoQuestions();
	if (d.getNoQuestions()){
		for (int i = 0; i < d.getNoQuestions(); i++){
			fout << endl << endl << "Question " << i + 1 << ": " << d.getQuestions(i);
		}
	}
	return fout;
}

void main(){
	User r1("ordinary", "basicaf");
	r1.setName("Regular");
	r1.setAge(31);
	cout << endl << "regular1: " << r1;
	/*User r2 = r1;
	r2.setName("John Doe");
	r2.setPassword("datjohntho");
	r2.setUsername("johnny");
	cout << endl << "regular2: " << r2;
	cout << endl << "Modify r1: ";
	cin >> r1;
	cout << endl << "The new r1: " << r1 << endl;*/

	moderatorUser m1("studase", "stud");
	m1.setName("Student of ASE");
	m1.setAge(18);
	m1.addXp(r1, 11);
	cout << endl << endl << "moderator1: " << m1;
	/*moderatorUser m2 = m1;
	m2.setName("Dean of ASE");
	m2.setUsername("dean");
	m2.setPassword("learn");
	m2.setAge(44);
	cout << endl << "moderator2: " << m2;
	moderatorUser m3("moderator", "sofm");
	cout << endl << "Ender moderator3's data: ";
	cin >> m3;
	cout << endl << "moderator3: " << m3;*/

	adminUser a1("ionpop", "ippsc");
	cout << a1;
	a1.setName("Ion Popescu"); //setters
	a1.setAge(20);
	a1.addXp(m1, 12);
	a1.setPassword("code4life");
	cout << endl << "admin1: ";
	a1.display(); //display is tested
	adminUser a2 = a1; //copy constructor and = overload
	a2.setUsername("ioanappsc");
	a2.setGender('f');
	a1.addXp(a2, 23);
	/*cout << endl << "a2, the copy of a1 feminin: " << a2; // << and getters are tested
	adminUser a3("admin", "pass");
	cout << endl << "Enter admin3 data: ";
	cin >> a3; // >> tested
	cout << endl << "admin3: " << a3;*/

	cout << endl << "*********"; // overloading of * and /
	r1 = r1 * 2; //reward by multipling the experience points
	m1 = m1 * 3;
	a2 = a2 / 2; //punsihment for bad behaviour by dividing the nr of xp
	cout << endl << "Results after xp rewards or punishments:";
	cout << endl << "user: " << r1;
	cout << endl << "moderator: " << m1;
	cout << endl << "admin2: " << a2;
	cout << "*********";
	cout << endl;
	
	Subject s1("I have a problem with += operator", "The Professor");
	s1.setQuestion("The += operator doesnt increment like it should. Here is the code: 'i +=;'");
	s1.setDifficulty(4);
	/*cout << endl << "subject1: " << s1;
	Subject s2 = s1; //tests the copy constructor 
	//cout << s2;
	cout << endl << "Enter a new subject: ";
	cin >> s2;
	cout << endl << "Here is the subject that you entered earlier: " << s2;
	cout << endl;*/

	Reply rp1(0, "johnny");
	rp1.setBody("IDK how to help you, bro... :(  It's way more difficult than 4!");
	Reply rp2(0, "johnny");
	rp2.setUsername("dean");
	rp2.setBody("You have to put an int after +=. Like so: i += 1;  or  j -= 2;");
	rp2.setBestanswer(1);
	rp2.addThumbsup();
	rp2.addThumbsup();

	s1 = s1 + rp1; //adds a reply to a subject
	s1 += rp2; //adds a reply to a subject
	s1++; //adds a new default reply (empty)
	//s1.setStatus(2);
	s1 *= rp2; //sets reply2 as the correct answer 

	cout << endl << "subject1: " << s1;
	s1--; //removes the last reply
	cout << endl << "*********************************";
	cout << endl << "The first reply of subject1 is:";
	cout << endl << s1[1]; //returns the reply with the index 1
	int cr = (int)s1; //returns the correct reply of s1 or 0 if it doesn't exist
	cout << endl << "The correct answer of the 1st subject is the reply nr. " << cr;
	cout << endl;

	//s1 = s1 - rp1; //removes a certain reply
	s1 -= rp1; //removes a certain reply
	//!s1; //clears the status of the subject (it makes it unsolved) and unmarks the reply
	cout << endl << "The first reply was removed!";
	cout << endl << endl << "subject1: " << s1;
	cout << endl;


	Domain d("C++");
	/*
	d1.readSubjectsFile("questions.txt"); 
	d1.addRepliesFile("replies.txt", 1); 
	// in the 3rd phase i will modify the method so that the index of the question will be automated
	*/
	Domain d1 = d("C++", "questions.txt", "replies.txt", 1); //equivalent to the set above //(function) overloading

	d.binOut("savefile.bin");
	/*to check binIn, run once to create savefile.bin, then comment the line from above
	(so the input files will be irrelevant), uncomment the set from below and run*/
	//d.binIn("savefile.bin");
	//cout << d;

	d.raportTxt("raport.txt");
	
	cout << "\n\n\n\t\t---ADVERTISING---";

	ad* *ads = new ad*[5];

	ads[0] = new banner("Intel", 120, 200, 800, "top part");
	ads[1] = new popUp("Kingston", 160, 750, 750, "center", 10);
	ads[2] = new gif("AMD", 100, 400, 200, "right side", 3);
	ads[3] = new videoAd("Apple", 250, 1920, 1080, 23, 30);
	ads[4] = new audioAd("Samsung", 200, 32, 'F');
	
	float adMoney = 0;
	for (int i = 0; i < 5; i++){
		cout << endl;
		ads[i]->getInfo();
		adMoney += ads[i]->getPrice();
	}
	cout << "\n\nMoney earned (per month) from advertising: " << adMoney << "$.\n\n";

	//A part of the requirements for the third phase were implemented since the second phase.
	//I have also made some corrections where needed.
}