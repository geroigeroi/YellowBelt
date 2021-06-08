bool isFemale(Person person) {
    if (person.gender == Gender::FEMALE) {
        return true;
    }
    return false;
}

bool isEmplyed(Person person) {
    if (person.is_employed) {
        return true;
    }
    return false;
}

void PrintStats(std::vector<Person> persons) {
    std::cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << std::endl;
    
    auto onlyFemale = std::partition(persons.begin(), persons.end(), isFemale);
    std::cout << "Median age for females = " << ComputeMedianAge(persons.begin(), onlyFemale) << std::endl;
    std::cout << "Median age for males = " << ComputeMedianAge(onlyFemale, persons.end()) << std::endl;
    
    auto onlyEmployedFemale = std::partition(persons.begin(), persons.end(), [](Person p){return isFemale(p) && isEmplyed(p);});
    std::cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), onlyEmployedFemale) << std::endl;
    
    auto onlyUnemployedFemale = std::partition(persons.begin(), persons.end(), [](Person p){return isFemale(p) && !isEmplyed(p);});
    std::cout << "Median age for unemployed females = " << ComputeMedianAge(persons.begin(), onlyUnemployedFemale) << std::endl;
    
    auto onlyEmployedMale = std::partition(persons.begin(), persons.end(), [](Person p){return !isFemale(p) && isEmplyed(p);});
    std::cout << "Median age for employed males = " << ComputeMedianAge(persons.begin(), onlyEmployedMale) << std::endl;
    
    auto onlyUnemployedMale = std::partition(persons.begin(), persons.end(), [](Person p){return !isFemale(p) && !isEmplyed(p);});
    std::cout << "Median age for unemployed males = " << ComputeMedianAge(persons.begin(), onlyUnemployedMale) << std::endl;
}