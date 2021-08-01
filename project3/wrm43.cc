/** Copyright 2021 Will McCormack
 * Project 3
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
 * Description: Uses vectors to allow researchers to load multiple site files,
 * assign control/experimental groups, and view statistics by group.
 *
**/

#include <vector>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// initialize vectors
vector <unsigned int> subject_id_vec;
vector <unsigned int> age_vec;
vector <unsigned int> age_factor_vec;
vector <unsigned int> progress_vec;
vector <int> progress_factor_vec;
vector <double> height_vec;
vector <double> weight_vec;
vector <double> BMI_factor_vec;
vector <unsigned int> egg_allergy_factor_vec;
vector <double> headache_factor_vec;
vector <double> stool_factor_vec;
vector <double> asthma_factor_vec;
vector <double> score_vec;
vector <char> group_vec;


/**
* Prints the menu of choices. Accepts a single character from
* the keyboard and passes it back as a return code. Used to
* print the menu repeatedly, cleanly, and consistently.
* @returns The character entered by the user
*/
char get_menu() {
    cout << "Welcome to the RSV Cross-Cohort Analysis Interface" << endl;
    cout << "See below for a list of options" << endl;
    cout << "Load Subject File - L" << endl;
    cout << "List Subjects in Group - l" << endl;
    cout << "Set minimum eligibility score - e" << endl;
    cout << "Divide subjects evenly into control/experimental groups - d"
        << endl;
    cout << "Fix age errors - f" << endl;
    cout << "Compute average score for group - a" << endl;
    cout << "Compute standard deviation for group - s" << endl;
    cout << "Compute group score stastistics - S" << endl;
    cout << "Quit - q" << endl;
    char in;

    cin >> in;
    return in;
}

/**
 * Loads the filename included as a string and places all the values
 * read into the appropriate vectors.
 * @params The thirteen vectors that hold the subject information plus a
 * string containing the filename to be read
 * @returns the count of the number of lines read
 *
**/
int load_subject_file(vector<unsigned int> & subject_id_vec,
                    vector<unsigned int> & age_vec,
                    vector<unsigned int> & age_factor_vec,
                    vector<unsigned int> & progress_vec,
                    vector<int> & progress_factor_vec,
                    vector<double> & height_vec,
                    vector<double> & weight_vec,
                    vector<double> & BMI_factor_vec,
                    vector<unsigned int> & egg_allergy_factor_vec,
                    vector<double> & headache_factor_vec,
                    vector<double> & stool_factor_vec,
                    vector<double> & asthma_factor_vec,
                    vector<double> & score_vec,
                    vector<char> & group_vec, string fileName) {
    ifstream input_file(fileName);
    // checks bad input file
    if (!input_file) {
        return -1;
    }

    // initialize variables to push
    unsigned int subject_id, age, age_factor, progress, egg_allergy_factor;
    int progress_factor;
    double height, weight, BMI_factor, headache_factor,
            stool_factor, asthma_factor, score;
    char group;

    // loops through input file, pushing to appropriate vectors
    while (input_file >> subject_id >> age >> age_factor >> progress >>
            progress_factor >> height >> weight >> BMI_factor >>
            egg_allergy_factor >> headache_factor >> stool_factor >>
            asthma_factor >> score >> group) {
        subject_id_vec.push_back(subject_id);
        age_vec.push_back(age);
        age_factor_vec.push_back(age_factor);
        progress_vec.push_back(progress);
        progress_factor_vec.push_back(progress_factor);
        height_vec.push_back(height);
        weight_vec.push_back(weight);
        BMI_factor_vec.push_back(BMI_factor);
        egg_allergy_factor_vec.push_back(egg_allergy_factor);
        headache_factor_vec.push_back(headache_factor);
        stool_factor_vec.push_back(stool_factor);
        asthma_factor_vec.push_back(asthma_factor);
        score_vec.push_back(score);
        group_vec.push_back(group);
    }
    return subject_id_vec.size();
}

/**
 * Neatly prints information for each subject that matches the
 * orrect group code. Defaults to printing all if the code is not
 * provided.
 * @params The thirteen vectors that hold the subject information plus a
 * group code to print
 * @returns none
**/
void list_subjects(vector<unsigned int> subject_id_vec,
                    vector<unsigned int> age_vec,
                    vector<unsigned int> age_factor_vec,
                    vector<unsigned int> progress_vec,
                    vector<int> progress_factor_vec, vector<double> height_vec,
                    vector<double> weight_vec,
                    vector<double> BMI_factor_vec,
                    vector<unsigned int> egg_allergy_factor_vec,
                    vector<double> headache_factor_vec,
                    vector<double> stool_factor_vec,
                    vector<double> asthma_factor_vec,
                    vector<double> score_vec, vector<char> group_vec,
                    char which_to_print = 'a') {
    for (int i = 0; i < subject_id_vec.size(); i++) {
        if (which_to_print == group_vec[i] || which_to_print == 'a') {
            cout << subject_id_vec[i];
            cout << " " << age_vec[i];
            cout << " " << age_factor_vec[i];
            cout << " " << progress_vec[i];
            cout << " " << progress_factor_vec[i];
            cout << " " << height_vec[i];
            cout << " " << weight_vec[i];
            cout << " " << BMI_factor_vec[i] << " "
                << egg_allergy_factor_vec[i] << " " << headache_factor_vec[i]
                << " " << stool_factor_vec[i] << " " << asthma_factor_vec[i]
                << " " << score_vec[i] << " " << group_vec[i] << endl;
        }
        }
    }

/**
 * Sets the minimum score needed to be excluded. Changes the group code
 * to i if subject is excluded or n if included. Can be used to reset group
 * codes.
 * @params the vector of scores, the vector of group codes, the minimum exclusion score
 * @returns none
**/
void set_minimum_score(vector<double> score_vec, vector<char>& group_vec,
                    double min_score) {
    for (int i = 0; i < score_vec.size(); i++) {
        if (score_vec[i] > min_score) {
            group_vec[i] = 'n';
        } else {
            group_vec[i] = 'i';
        }
    }
}

/**
 * Divides eligible subjects into control and experimental groups by changing
 * their group code.
 * @params the vector of group codes
 * @returns none
**/
void split_subjects_evenly(vector<char>& group_vec) {
    // alternates only elliglbes group starting with c
    char cur_group = 'c';
    for (int i = 0; i < group_vec.size(); i++) {
        if (group_vec[i] == 'n') {
            group_vec[i] = cur_group;
            if (cur_group == 'c') {
                cur_group = 'e';
            } else {
                cur_group = 'c';
            }
        }
    }
}

/**
 * Identifies any subjects with an age factor of 0, changes their score to zero,
 * and changes their group status to ineligible. Prints IDs of subjects who had errors.
 * @params id vector, age factor vector, score vector, group vector
 * @return none
**/
void fix_age_errors(vector<unsigned int> subject_id_vec,
                    vector<unsigned int> age_factor_vec,
                    vector<double>& score_vec, vector<char>& group_vec) {
    for (int i = 0; i < subject_id_vec.size(); i++) {
        if (age_factor_vec[i] == 0) {
            score_vec[i] = 0;
            group_vec[i] = 'i';
            cout << subject_id_vec[i] << endl;
        }
    }
}

/**
 * Computes the average score for a group given the group code
 * @params vector of scores, vector of groups, group code to compute average for
 * @returns the average for the given group
 **/
double average_score_for_group(vector<double> score_vec, vector<char> group_vec,
                                char which_group) {
    double score_sum;
    unsigned int group_size;

    for (int i = 0; i < score_vec.size(); i++) {
        if (group_vec[i] == which_group) {
            score_sum += score_vec[i];
            group_size++;
        }
    }
    return score_sum / group_size;
}

/**
 * Computes the standard deviation of the score for a group given the group code
 * @params vector of scores, vector of groups, group code to compute st dev for
 * @returns the standard deviation for the given group
**/
double std_dev_score_for_group(vector<double> score_vec, vector<char> group_vec,
                                char which_group) {
    double score_sum, st_dev;
    double mean;
    int group_size = 0;

    // computes mean to be used in std. dev calc
    for (int i = 0; i < score_vec.size(); i++) {
        if (group_vec[i] == which_group) {
            score_sum += score_vec[i];
            group_size++;
        }
    }
    mean = score_sum / group_size;

    // calculates std. dev sum
    for (int i = 0; i < score_vec.size(); i++) {
        st_dev += pow(score_vec[i] - mean, 2);
    }

    return sqrt(st_dev / group_size);
}

/**
 * Computes the average and standard deviation for a particular group
 * @params the vector of scores, the vector of group codes, the character code
 * of the group to compute, the average and the std deviation which are
 * both returned by reference
 * @return average and std dev by reference
**/
void compute_group_score_statistics(vector<double> score_vec,
                                    vector<char> group_vec, char which_group,
                                    double & group_average,
                                    double & group_std_dev) {
    group_average = average_score_for_group(score_vec, group_vec, which_group);
    group_std_dev = std_dev_score_for_group(score_vec, group_vec, which_group);
}

int main() {
    char in, which_group;
    // if user enters q, program quits.
    while (in != 'q') {
        in = get_menu();
        // appropriate cases to handle user input
        switch (in) {
            case 'L': {
                cout << "Enter filename to load:" << endl;
                string input_file = "";
                cin >> input_file;
                load_subject_file(subject_id_vec, age_vec, age_factor_vec,
                                progress_vec, progress_factor_vec,
                                height_vec, weight_vec, BMI_factor_vec,
                                egg_allergy_factor_vec, headache_factor_vec,
                                stool_factor_vec, asthma_factor_vec, score_vec,
                                group_vec, input_file);
                break;
            }
            case 'l': {
                cout << "Which group to list?" << endl;
                cin >> which_group;
                list_subjects(subject_id_vec, age_vec, age_factor_vec,
                            progress_vec, progress_factor_vec, height_vec,
                            weight_vec, BMI_factor_vec, egg_allergy_factor_vec,
                            headache_factor_vec, stool_factor_vec,
                            asthma_factor_vec, score_vec, group_vec,
                            which_group);
                break;
            }
            case 'e': {
                cout << "What is the minimum eligibility score?" << endl;
                double min_score;
                cin >> min_score;
                set_minimum_score(score_vec, group_vec, min_score);
                break;
            }
            case 'd': {
                cout << "Dividing subjects evenly." << endl;
                split_subjects_evenly(group_vec);
                break;
            }
            case 'f': {
                cout << "Fixing age errors." << endl;
                fix_age_errors(subject_id_vec, age_factor_vec,
                                score_vec, group_vec);
                break;
            }
            case 'a': {
                cout << "Which group to compute average score?" << endl;
                cin >> which_group;
                cout << "Average score for group " << which_group << " : "
                    << average_score_for_group(score_vec,
                                                group_vec, which_group) << endl;
                break;
            }
            case 's': {
                cout << "Which group to compute standard deviation?" << endl;
                cin >> which_group;
                cout << "Standard deviation for group " << which_group
                        << " : " << std_dev_score_for_group(score_vec,
                                    group_vec, which_group) << endl;
                break;
            }
            case 'S': {
                cout << "Which group to compute statistics?" << endl;
                cin >> which_group;
                double group_average, group_st_dev;
                compute_group_score_statistics(score_vec, group_vec,
                                                which_group, group_average,
                                                group_st_dev);
                cout << "Statistics for group " << which_group << ":" << endl;
                cout << "Average: " << group_average << endl;
                cout << "Standard deviation: " << group_st_dev << endl;
                break;
            }
            // if user quits, return 0
            case 'q': {
                return 0;
            }
        }
    }
}
