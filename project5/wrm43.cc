/** Copyright 2021 Will McCormack
 * Project 5
 * Name: Will McCormack
 * Netid: wrm43
 * COSC 051
 * Section: N/A
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance
 * on this project with the exceptions of the lecture notes and those
 * items noted below.
 *
 * Any help items (you may omit mentions of the TAs, the professors,
 * the recommended text, or prior years posted solutions):
 * Description: Takes subject and baby data, then analyzes baby symptoms
 * for control and experimental group to measure efficacy.
 *
**/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Baby {
  friend istream& operator >>(istream &in, Baby &b);
  friend ostream& operator<<(ostream &out, Baby b);

 public:
  // Default constructor that sets private data members to 0
  Baby();

  double get_cough();
  void set_cough(double);
  int get_wheezing();
  void set_wheezing(int);
  int get_pneumonia();
  void set_pneumonia(int);

  // uses cout to print the private data members
  // separated by a space for debugging. Can use
  // the overloaded << operator
  void report();

  unsigned int get_mom_id();
  void set_mom_id(unsigned int);

 private:
  unsigned int mom_id;  // must match one of the Subjects
  double cough;
  int wheezing;
  int pneumonia;
};  // end class definition

istream& operator >>(istream& in, Baby &b) {
  // reads in input to private members
  in >> b.mom_id;
  in >> b.cough;
  in >> b.wheezing;
  in >> b.pneumonia;
  return in;
}

ostream& operator<<(ostream& out, Baby b) {
  // outputs all members
  out << endl << "Mom id: " << b.get_mom_id() << endl;
  out << "Cough: " << b.get_cough() << endl;
  out << "Wheezing: " << b.get_wheezing() << endl;
  out << "Pnemounia: " << b.get_pneumonia() << endl;
  return out;
}

Baby::Baby() {
  mom_id = 0;
  cough = 0;
  wheezing = 0;
  pneumonia = 0;
}

double Baby::get_cough() {
  return cough;
}

void Baby::set_cough(double c) {
  cough = c;
}

int Baby::get_wheezing() {
  return wheezing;
}

void Baby::set_wheezing(int w) {
  wheezing = w;
}

int Baby::get_pneumonia() {
  return pneumonia;
}

void Baby::set_pneumonia(int p) {
  pneumonia = p;
}

void Baby::report() {
  // outputs this Baby
  cout << *this << endl;
}

unsigned int Baby::get_mom_id() {
  return mom_id;
}

void Baby::set_mom_id(unsigned m) {
  mom_id = m;
}

class Subject {
  friend istream& operator>>(istream &in, Subject &ps);
  friend ostream& operator<<(ostream & out, Subject s);

 public:
  Subject();
  void set_subject_id(unsigned int);
  void set_group(char);
  void set_next(Subject *);
  unsigned int get_subject_id();
  Subject *get_next();
  void set_baby(Baby);
  Baby get_baby();

  // uses cout to print the private data members
  // separated by a space for debugging. Can use
  // the overloaded << operator
  void report();

  char get_group();

 private:
  unsigned int subject_id;  // mom's id c
  char group;  // e or c

  Subject *next;  // points to next Subject in Trial
  Baby baby;
};  // end class definition

istream& operator>>(istream &in, Subject &ps) {
  // reads into appropriate private members
  in >> ps.subject_id;
  in >> ps.group;
  return in;
}

ostream& operator<<(ostream & out, Subject s) {
  // outputs mother and associated baby information
  out << "Subject id: " << s.subject_id << endl;
  out << "Subject group " << s.group << endl;
  out << "Subject baby: " << s.baby << endl;
  return out;
}

Subject::Subject() {
  // by default, next is NULL
  next = NULL;
}

void Subject::set_subject_id(unsigned int id) {
  subject_id = id;
}

void Subject::set_group(char g) {
  group = g;
}

void Subject::set_next(Subject * n) {
  next = n;
}

unsigned int Subject::get_subject_id() {
  return subject_id;
}

Subject * Subject::get_next() {
  return next;
}

void Subject::set_baby(Baby b) {
  baby = b;
}

Baby Subject::get_baby() {
  return baby;
}

void Subject::report() {
  // outputs this Subject
  cout << *this << endl;
}

char Subject::get_group() {
  return group;
}

class Trial {
 public:
  Trial();
  // read subject file with given name
  int load_subject_file(string);

  // read baby file with given name
  int load_baby_file(string);

  // calls report on each Subject in the list
  void print_list();

  // Shows the average and standard deviation for each of the
  // control and experimental groups for each of the babies symptoms
  // (calls display_factor three times)
  void display_statistics();

 private:
  // add Subject to the 'list'
  void add_subject(Subject *);
  // Find the mom on the list to add the baby data
  Subject * find_subject_by_id(unsigned int);
  // Computes the average for a particular group and symptom
  // args: group (e or c), symptom code (c, w, or p)
  double average(char, char);
  // Computes the standard deviation for a particular group and symptom
  // args: group (e or c), symptom code (c, w, or p)
  double deviation(char, char, double);

  // Prints the statistical data for a single symptom
  void display_factor(char);

  Subject *head_subject;  // points to start of linked list of Subjects
};  // end class definition

Trial::Trial() {
  // when constructed, head is NULL
  head_subject = NULL;
}

int Trial::load_subject_file(string file_name) {
  ifstream input_file(file_name);

  // handles bad file name
  if (!input_file) {
    cout << "Bad file name." << endl;
    return -1;
  }
  unsigned int size;

  Subject * s = new Subject();

  // loops through input file, adding subjects and incrementing size
  while (input_file >> *s) {
    add_subject(new Subject(*s));
    size++;
  }
  return size;
}

void Trial::add_subject(Subject * s) {
  // if empty list, set head
  if (head_subject == NULL) {
    head_subject = s;
  } else {
    // list is not empty, use temp ptr to traverse
    Subject * temp = head_subject;
    while (temp->get_next() != NULL) {
      temp = temp->get_next();
    }
    temp->set_next(s);
  }
}

int Trial::load_baby_file(string file_name) {
  ifstream input_file(file_name);
  // handle bad file name
  if (!input_file) {
    cout << "Bad file name." << endl;
    return -1;
  }

  unsigned int size;
  Baby * b = new Baby();

  while (input_file >> *b) {
    // finds mother and sets their baby
    Subject * s = find_subject_by_id(b->get_mom_id());
    s->set_baby(*b);
    size++;
  }
  return size;
}

Subject * Trial::find_subject_by_id(unsigned int to_find) {
  // set up temp pointer at head
  Subject * temp = head_subject;
  while (temp) {
    // if found, return temp
    if (temp->get_subject_id() == to_find) {
      return temp;
    }
    temp = temp->get_next();
  }
  // if not found, return NULL
  return NULL;
}

void Trial::print_list() {
  Subject *temp = head_subject;
  while (temp) {
    // take advantage of overloaded << operator
    cout << *temp << endl;
    temp = temp->get_next();
  }
}

void Trial::display_statistics() {
  // displays for three factors
  display_factor('c');
  display_factor('w');
  display_factor('p');
}

void Trial::display_factor(char symptom) {
  // calculate stats
  double control_average = average('c', symptom);
  double control_deviation = deviation('c', symptom, control_average);
  double experimental_average = average('e', symptom);
  double experimental_deviation = deviation('e', symptom, experimental_average);

  if (symptom == 'c') {
    cout << "Displaying statistical data for coughing: " << endl;
  } else if (symptom == 'w') {
    cout << "Displaying statistical data for wheezing: " << endl;
  } else if (symptom == 'p') {
    cout << "Displaying statistical data for pneumonia: " << endl;
  } else {
    cout << "Symptom code not recognized (available: c/w/p)." << endl;
    return;
  }
  cout << "Control average: " << control_average <<  endl;
  cout << "Control std. deviation: " << control_deviation << endl;
  cout << "Experimental average: " << experimental_average << endl;
  cout << "Experimental std. deviation: " << experimental_deviation
      << endl << endl;
}

double Trial::average(char group, char symptom) {
  unsigned int group_size;
  double symptom_sum;

  // start at head
  Subject *temp = head_subject;

  while (temp) {
    // if in correct group, add correct symptom to sum
    if (temp->get_group() == group) {
      if (symptom == 'c') {
        symptom_sum += temp->get_baby().get_cough();
      } else if (symptom == 'w') {
        symptom_sum += temp->get_baby().get_wheezing();
      } else {
        symptom_sum += temp->get_baby().get_pneumonia();
      }
      group_size++;  // increment group sum
    }
    temp = temp->get_next();
  }
  return symptom_sum / group_size;
}

double Trial::deviation(char group, char symptom, double average) {
  double deviation;
  unsigned int group_size;

  // start temp pointer at head
  Subject * temp = head_subject;

  while (temp) {
    // if in correct group, add correct symptom to sum
    if (temp->get_group() == group) {
      if (symptom == 'c') {
        deviation += pow(temp->get_baby().get_cough() - average, 2);
      } else if (symptom == 'w') {
        deviation += pow(temp->get_baby().get_wheezing() - average, 2);
      } else {
        deviation += pow(temp->get_baby().get_pneumonia() - average, 2);
      }
      group_size++;  // increment group size
    }
    temp = temp->get_next();
  }
  return sqrt(deviation / group_size);
}

int main() {
  Trial trial;
  trial.load_subject_file("data.txt");
  trial.load_baby_file("baby.txt");
  trial.display_statistics();
}
