/** Copyright 2021 Will McCormack
 * Project 2
 * Name Will McCormack
 * Netid: wrm43
 * COSC 051
 * Section: N/A
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance
 * on this project with the exceptions of the lecture notes and those
 * items noted below.
 * Any help items (you may omit mentions of the TAs, the professors,
 * the recommended text, or prior years posted solutions):
 * Description:
 * Analyzes subject data and eligibility based on user input file and cutoff score.
 * Determines average metrics of group.
 *
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    string file_name;

    // intialize variables
    unsigned int subject_id, age, age_factor, progress, egg_allergy_factor,
                asthma_factor, num_subjects, num_qualified;
    int progress_factor;
    double height, weight, BMI_factor, headache_factor, stool_factor, score,
            cutoff_score, min_score, max_score;

    // intialize sum variables to be used when calculating averages.
    double age_sum, age_factor_sum, progress_sum, progress_factor_sum,
            headache_factor_sum, asthma_factor_sum, BMI_sum, BMI_factor_sum,
            stool_factor_sum, score_sum;


    // get user infile name
    cout << "Please enter subject file name for loading:" << endl;
    cin >> file_name;

    // get cutoff score
    cout << "Please enter the maximum subject score:" << endl;
    cin >> cutoff_score;

    min_score = cutoff_score;
    max_score = 0;

    // create infile stream with user input file name
    ifstream input_file(file_name);

    // loop through file name reading a line's woth of variables at a time
    while (input_file >> subject_id >> age >> age_factor >> progress >>
            progress_factor >> height >> weight >> BMI_factor
            >> egg_allergy_factor >> headache_factor >> stool_factor
            >> asthma_factor >> score) {
                num_subjects++;
                if (score > 0 && score < cutoff_score) {
                    num_qualified++;  // only increment if qualified

                    // increment sums
                    age_sum += age;
                    age_factor_sum += age_factor;
                    progress_sum += progress;
                    progress_factor_sum += progress_factor;
                    BMI_sum += (weight / (pow(height, 2)));
                    BMI_factor_sum += BMI_factor;
                    headache_factor_sum += headache_factor;
                    stool_factor_sum += stool_factor;
                    asthma_factor_sum += asthma_factor;
                    score_sum += score;

                    // if needed, set min/max score
                    if (score < min_score) {
                        min_score = score;
                    }
                    if (score > max_score) {
                        max_score = score;
                    }
                }
    }

    // output averages and total subjects
    cout << fixed << setprecision(2) <<  "Total Subjects in file "
        << file_name << ": " << num_subjects << endl;
    cout << "Number of subjects excluded based on score: "
        << (num_subjects - num_qualified) << endl;
    cout << "Number of subjects qualified based on score: "
        << num_qualified << endl;
    cout << "Average Age: "  << (age_sum / num_qualified) << endl;
    cout << "Average Age Factor: " << (age_factor_sum / num_qualified) << endl;
    cout << "Average Pregnancy Progress: "
        << (progress_sum / num_qualified) << endl;
    cout << "Average Pregnancy Progress Factor: "
        << (progress_factor_sum / num_qualified) << endl;
    cout << "Average BMI: "  <<  (BMI_sum / num_qualified) << endl;
    cout << "Average BMI Factor: " << (BMI_factor_sum / num_qualified) << endl;
    cout << "Average Headache Factor: "
        << (headache_factor_sum / num_qualified) << endl;
    cout << "Average Stool Factor: " << (stool_factor_sum / num_qualified)
        << endl;
    cout << "Average Asthma Factor: "
        << (asthma_factor_sum / num_qualified) << endl;
    cout << "Average Eligibility Score: " << (score_sum / num_qualified)
         << endl;
    cout << "Minimum Eligibility Score: " << min_score << endl;
    cout << "Maximum Eligibility Score: " << max_score << endl;
}
