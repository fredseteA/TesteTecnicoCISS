#pragma once
#include <string>
#include <vector>

void dbInit();
void dbSaveDna(const std::vector<std::string>& dna, bool isSimian);

struct Stats {
    int countSimian;
    int countHuman;
    float ratio;
};

Stats dbGetStats();