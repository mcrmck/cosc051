/** Copyright 2021 Will McCormack
 * Project 4
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
 * Description: Takes subject and side effect file, outputting statistical
 * analysis for possible factors for control and experimental groups.
 *
**/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

class Subject {
 public:
    // A constuctor that creates a subject given all the
    // information needed, which conists of the 14 vectors
    // from project 3, including the group. It initializes
    // the post factors to zero for the time being.
    Subject(unsigned int, unsigned int, unsigned int, unsigned int, int,
            double, double, double, unsigned int, double,
            double, double, double, char);

    // Causes the subject to print its contents neatly. Used for
    // debugging but still required. Items should print in the order
    // listed for private data members below
    void report();

    // Returns the subject ID of the subject
    unsigned int getSubjectId();

    // Returns the experimental group of the subject
    char getGroup();

    // Accessor and Observers for each of the side effect measures.
    void setHeadacheFactorPost(double);
    double getHeadacheFactorPost();
    void setStoolFactorPost(double);
    double getStoolFactorPost();
    void setCoughPost(unsigned int);
    unsigned int getCoughPost();

 private:
    unsigned int subject_id;
    unsigned int age;
    unsigned int age_factor;
    unsigned int progress;
    int progress_factor;
    double height;
    double weight;
    double bmi_factor;
    unsigned int egg_allergy_factor;
    double headache_factor;
    double stool_factor;
    double asthma_factor;
    double score;
    char group;  // eligibility
    double headache_factor_post;
    double stool_factor_post;
    unsigned int cough_post;
};  // end class definition

Subject::Subject(unsigned int id, unsigned int a, unsigned int af,
                unsigned int p, int pf, double h,
                double w, double bmi, unsigned int eaf, double hf,
                double sf, double asf, double s, char g) {
    subject_id = id;
    age = a;
    age_factor = af;
    progress = p;
    progress_factor = pf;
    height = h;
    weight = w;
    bmi_factor = bmi;
    egg_allergy_factor = eaf;
    headache_factor = hf;
    stool_factor = sf;
    asthma_factor = asf;
    score = s;
    group = g;
    headache_factor_post = 0;
    stool_factor_post = 0;
    cough_post = 0;
}

void Subject::report() {
    cout << "Subject id: " << subject_id << endl;
    cout << "Age: " << age << endl;
    cout << "Age factor: " << age_factor << endl;
    cout << "Progress: " << progress << endl;
    cout << "Progress factor: " << progress_factor << endl;
    cout << "Height: " << height << endl;
    cout << "Weight: " << weight << endl;
    cout << "BMI factor: " << bmi_factor << endl;
    cout << "Egg allergy factor: " << egg_allergy_factor << endl;
    cout << "Headache factor: " << headache_factor << endl;
    cout << "Stool factor: " << stool_factor << endl;
    cout << "Asthma factor: " << asthma_factor << endl;
    cout << "Score: " << score << endl;
    cout << "Group: " << group << endl;
    cout << "Headache factor post: " << headache_factor_post << endl;
    cout << "Stool factor post: " << stool_factor_post << endl;
    cout << "Cough post: " << cough_post << endl;
    cout << endl;
}

unsigned int Subject::getSubjectId() {
    return subject_id;
}

char Subject::getGroup() {
    return group;
}

void Subject::setHeadacheFactorPost(double hfp) {
    headache_factor_post = hfp;
}

double Subject::getHeadacheFactorPost() {
    return headache_factor_post;
}

void Subject::setStoolFactorPost(double sfp) {
    stool_factor_post = sfp;
}

double Subject::getStoolFactorPost() {
    return stool_factor_post;
}

void Subject::setCoughPost(unsigned int cp) {
    cough_post = cp;
}

unsigned int Subject::getCoughPost() {
    return cough_post;
}



class Trial {
 public:
    // Simple constructor
    Trial();

    // Loads a subject file into the vector of subjects
    // Returns a count of the number of subjects loaded
    int loadSubjects(string);

    // Loads a side effect file. Uses the subject ID to locate the
    // subject ID in the vector, and then sets the subject object to
    // also contain the correct side effect values
    // Returns a count of the number of subjects with side effects loaded
    int loadSideEffects(string);

    // prints out the subject vector by calling the report method
    // of each subject. Used for debugging but required.
    void report();

    // performs an analysis of the average and standard deviaton for
    // the control and experiment groups for each side effect
    // parameter order is: control average, control stddev,
    // experimental average, experimental stddev
    // Note: These methods do not do the output! They do the
    // computation which is returned
    void analyzeHeadache(double &, double &, double &, double &);
    void analyzeStool(double &, double &, double &, double &);
    void analyzeCough(double &, double &, double &, double &);

 private:
    // This private method computes the average for a particular
    // group (c or e, provided in the first parameter) for a
    // particular side effect (h, s, or c, given in the second parameter)
    double averageForGroup(char, char);

    // This private method computes the population standard deviation
    // for a particular group
    // (c or e, provided in the first parameter) for a
    // particular side effect
    // (h, s, or c, given in the second parameter)
    // the third parameter is the average for that group as
    // computed above.
    double stdevForGroup(char, char, double);

    // A private function used to return the location
    // in the vector of subjects of a subject with a
    // particular subject id used in the loadSideEffects
    // to locate where a particular subject is
    int findSubject(unsigned int);
    vector<Subject> subjects;
};  // end class definition

Trial::Trial() {}

int Trial::loadSubjects(string file_name) {
    // reject bad file name
    ifstream input_file(file_name);
     if (!input_file) {
         cout << "Bad file name." << endl;
        return -1;
    }
    // initialze variables to read in
    unsigned int subject_id, age, age_factor, progress, egg_allergy_factor;
    int progress_factor;
    double height, weight, bmi_factor, headache_factor, stool_factor,
            asthma_factor, score;
    char group;

    // push to appropriate vectors
    while (input_file >> subject_id >> age >> age_factor >> progress >>
            progress_factor >> height >> weight >> bmi_factor >>
            egg_allergy_factor >> headache_factor >> stool_factor >>
            asthma_factor >> score >> group) {
        Subject temp(subject_id, age, age_factor, progress, progress_factor,
                    height, weight, bmi_factor, egg_allergy_factor,
                    headache_factor, stool_factor, asthma_factor, score, group);

        subjects.push_back(temp);
    }
    return subjects.size();
}

int Trial::loadSideEffects(string file_name) {
    // handle bad file name
    ifstream input_file(file_name);
    if (!input_file) {
        cout << "Bad file name." << endl;
        return -1;
    }

    unsigned int subject_id, cough_post, num_loaded;
    double headache_factor_post, stool_factor_post;

    // read in to vectors
    while (input_file >> subject_id >> headache_factor_post >>
             stool_factor_post >> cough_post) {
        int subject_index = findSubject(subject_id);
        subjects[subject_index].setHeadacheFactorPost(headache_factor_post);
        subjects[subject_index].setStoolFactorPost(stool_factor_post);
        subjects[subject_index].setCoughPost(cough_post);
        num_loaded++;
    }
    return num_loaded;
}

int Trial::findSubject(unsigned int subject_id) {
    for (int i = 0; i < subjects.size(); i++) {
        // if found match, return index
        if (subjects[i].getSubjectId() == subject_id) {
            return i;
        }
    }
    // if not found, return -1
    return -1;
}

void Trial::report() {
    for (int i = 0; i < subjects.size(); i++) {
        subjects[i].report();
    }
}

void Trial::analyzeHeadache(double & control_average, double & control_stddev,
                            double & experimental_average,
                            double & experimental_stddev) {
    // calculate avg/stddev for control and experimental groups
    control_average = averageForGroup('c', 'h');
    control_stddev = stdevForGroup('c', 'h', control_average);
    experimental_average = averageForGroup('e', 'h');
    experimental_stddev = stdevForGroup('e', 'h', experimental_average);
}

void Trial::analyzeStool(double & control_average, double & control_stddev,
                        double & experimental_average,
                        double & experimental_stddev) {
    // calculate avg/stddev for control and experimental groups
    control_average = averageForGroup('c', 's');
    control_stddev = stdevForGroup('c', 's', control_average);
    experimental_average = averageForGroup('e', 's');
    experimental_stddev = stdevForGroup('e', 's', experimental_average);
}

void Trial::analyzeCough(double & control_average, double & control_stddev,
                        double & experimental_average,
                        double & experimental_stddev) {
    // calculate avg/stddev for control and experimental groups
    control_average = averageForGroup('c', 'c');
    control_stddev = stdevForGroup('c', 'c', control_average);
    experimental_average = averageForGroup('e', 'c');
    experimental_stddev = stdevForGroup('e', 'c', experimental_average);
}


double Trial::averageForGroup(char group, char side_effect) {
    double side_effect_sum = 0;
    unsigned int group_size = 0;
    for (int i = 0; i < subjects.size(); i++) {
        // if matches group, add appropriate factor to sum
        if (subjects[i].getGroup() == group) {
            if (side_effect == 'h') {
                side_effect_sum += subjects[i].getHeadacheFactorPost();
            } else if (side_effect == 's') {
                side_effect_sum += subjects[i].getStoolFactorPost();
            } else {
                side_effect_sum += subjects[i].getCoughPost();
            }
            group_size++;
        }
    }
    return side_effect_sum / group_size;
}

double Trial::stdevForGroup(char group, char side_effect, double average) {
    double stdev = 0;
    unsigned int group_size = 0;
    for (int i = 0; i < subjects.size(); i++) {
        if (subjects[i].getGroup() == group) {
            // if matches group, add appropriate side effect to sum.
            if (side_effect == 'h') {
                stdev += pow(subjects[i].getHeadacheFactorPost() - average, 2);
            } else if (side_effect == 's') {
                stdev += pow(subjects[i].getStoolFactorPost() - average, 2);
            } else {
                stdev += pow(subjects[i].getCoughPost() - average, 2);
            }
            group_size++;
        }
    }
    return sqrt(stdev / group_size);
}







int main() {
    string subject_file_name;
    string side_effect_file_name;
    cout << "Welcome to the RSV Trial Side Effect Analysis Interface." << endl;
    cout << "Please enter subject file name." << endl;
    cin >> subject_file_name;
    cout << "Please enter side effect file name." << endl;
    cin >> side_effect_file_name;
    cout << endl;

    Trial trial;
    trial.loadSubjects(subject_file_name);
    trial.loadSideEffects(side_effect_file_name);

    double control_average, control_stddev, experimental_average,
            experimental_stddev;
    trial.analyzeHeadache(control_average, control_stddev, experimental_average,
                            experimental_stddev);

    cout << "HEADACHE ANALYSIS" << endl;
    cout << "control average: " << control_average << endl;
    cout << "control st. dev: " << control_stddev << endl;
    cout << "experimental average: " << experimental_average << endl;
    cout << "experimental st. dev: " << experimental_stddev << endl << endl;

    trial.analyzeStool(control_average, control_stddev, experimental_average,
                        experimental_stddev);

    cout << "STOOL ANALYSIS" << endl;
    cout << "control average: " << control_average << endl;
    cout << "control st. dev: " << control_stddev << endl;
    cout << "experimental average: " << experimental_average << endl;
    cout << "experimental st. dev: " << experimental_stddev << endl << endl;

    trial.analyzeCough(control_average, control_stddev, experimental_average,
                        experimental_stddev);

    cout << "COUGH ANALYSIS" << endl;
    cout << "control average: " << control_average << endl;
    cout << "control st. dev: " << control_stddev << endl;
    cout << "experimental average: " << experimental_average << endl;
    cout << "experimental st. dev: " << experimental_stddev << endl << endl;
}

