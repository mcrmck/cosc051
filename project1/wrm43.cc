/** Copyright 2021 Will McCormack
  * Project 1
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
  * Determines individual elligiblity
  * in a RSV study based off of questionaire answers.
 **/

#include <iostream>
#include <cmath>


int main() {
  // initialize variables
  unsigned int subject_id, age, age_factor, progress, egg_allergy_factor,
                headache_sev, stool_text, asthma_freq;
  int progress;
  double progress_factor, height, weight, BMI_factor, headache_freq,
         headache_factor, stool_freq, stool_factor, asthma_factor, score;
  bool asthma_presence;

  // initialize scalar constants
  const double age_scalar = 3.64, progress_scalar = 4.5,
              BMI_scalar = 2.0, headache_scalar = 20.0,
              stool_scalar = 1.2, asthma_scalar = 3.20;


  // get user input
  std::cout << "Input eight digit  id" << std::endl;
  std::cin >> subject_id;
  std::cout << "Input age (years)" << std::endl;
  std::cin >> age;

  // calculate age factor, including ineligible ages
  if (age < 18 || age > 45) {
    age_factor = 0;
  } else {
    age_factor = ((age - 10) / 5) * 13;
  }

  // get user pregnancy progress, and calculate corresponding factor
  std::cout << "If pregnant, input est. days since conception (otherwise 0)\n";
  std::cin >> progress;
  progress_factor = progress - 90;

  // get user height and weight, calculate BMI
  std::cout << "Input height, decimal value in meters\n";
  std::cin >> height;
  std::cout << "Input weight, decimal vlaue in kilograms\n";
  std::cin >>  weight;
  BMI_factor = (weight / (pow(height, 2)));
  // sets factor to 0 if out of range
  if (BMI_factor < 15 || BMI_factor > 40) {
    BMI_factor = 0;
  }

  // gets user egg allergy, in int form
  std::cout << "Do you have an egg allergy, (1 = yes/0 = no)\n";
  std::cin >>  egg_allergy_factor;

  // gets user headache freq/sev, calculates corresponding factor
  std::cout << "Input est. number of days with a headache per 30 day month\n";
  std::cin >> headache_freq;
  std::cout << "Input average integer headache severity "
            "using pain scale from 1-10\n";
  std::cin >> headache_sev;
  headache_factor = headache_freq * headache_sev;

  // gets user stool information and calculates factor
  std::cout << "Input estimated decimal average of bowel movements per day\n";
  std::cin >> stool_freq;
  std::cout << "Input stool texture, using Bristol Stool Scale\n";
  std::cin >> stool_text;
  stool_factor = abs(4 - stool_text) * abs(2 - stool_freq);

  // gets user asthma presence and if applicable med frequency
  std::cout << "Do you have asthma, (1 = yes/ 0 = no)\n";
  std::cin >> asthma_presence;
  if (asthma_presence) {
    std::cout << "If yes, what is the integer estimated number of times "
            "medicine is used to treat it (otherwise 0)\n";
    std::cin >> asthma_freq;
    asthma_factor = 2 + asthma_freq;
  } else {
    asthma_factor = 1;
  }

  // if user is inelligble, their elligibilty score is 0,
  // otherwise calculate accordingly
  if (egg_allergy_factor == 1 || progress_factor < 0 || progress_factor > 90
      || BMI_factor == 0 || stool_freq > 6) {
    score = 0;
  } else {
    score = (age_factor / age_scalar) + (progress_factor / progress_scalar)
                      + (BMI_factor / BMI_scalar) +
                      (headache_factor / headache_scalar) +
                      (stool_factor / stool_scalar) +
                      (asthma_scalar / asthma_scalar);
  }


  // output score and information in correct format
  std::cout << " " << subject_id << " " << age << " " << age_factor << " "
            << " " << progress << " " << progress_factor << " " << height
            << " " << weight << " " << BMI_factor << " " << egg_allergy_factor
            << " " << headache_factor << " " << stool_factor << " "
            << asthma_factor << " " << score << std::endl;
}
