#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isSimian(vector<string>dna) {   
    int direcoes[4][2] = {
        {0, 1},   
        {1, 0},   
        {1, 1},   
        {1, -1}   
    };

    for (int i = 0; i < dna.size(); i++) {
        for (int j = 0; j < dna[i].size(); j++) {

            for (int d = 0; d < 4; d++) {   
                int di = direcoes[d][0];
                int dj = direcoes[d][1];
                int iguais = 0;

                for (int passo = 0; passo < 4; passo++) {
                    int novaLinha = i + di * passo;
                    int novaColuna = j + dj * passo;
                    if (novaLinha < 0 || novaLinha >= dna.size() ||
                        novaColuna < 0 || novaColuna >= dna[0].size()) {
                        break;
                    }
                    if (dna[novaLinha][novaColuna] == dna[i][j]) {
                        iguais++;
                    } else {
                        break;
                    }
                }
                if (iguais == 4) {
                    return true;
                }
            }

        }
    }
    
    return false;
}

int main() {
    // 1. SÍMIO - sequência horizontal (CCCC na linha 4)
    vector<string> dna1= {"CTGAGA", "CTGAGC", "TATTGT", "AGAGGG", "CCCCTA", "TCACTG"};

    // 2. HUMANO - sem nenhuma sequência de 4 iguais
    vector<string> dna2 = {"ATGCGA", "CAGTGC", "TTATTT", "AGACGG", "GCGTCA", "TCACTG"};

    // 3. SÍMIO - sequência vertical (AAAA na coluna 0)
    vector<string> dna3 = {"ATGCGA", "AGTCGC", "ATAGTT", "AGAAGG", "ATCCTA", "TCACTG"};

    // 4. SÍMIO - sequência diagonal principal (GGGG)
    vector<string> dna4 = {"GTGCGA", "CGGTGC", "TTGATT", "AGAGGG", "CCCCTA", "TCACTG"};

    // 5. HUMANO - quase uma sequência mas falta 1, deu simio
    vector<string> dna5 = {"ATGCGA", "CAGTGC", "TTATGT", "AGAAGG", "CCCATA", "TCACTG"};

    // 6. SÍMIO - sequência diagonal secundária (TTTT)
    vector<string> dna6 = {"ATGCGT", "CAGTCT", "TTATGT", "AGTAGG", "TCCCTA", "TCACTG"};

    // 7. HUMANO - matriz menor 4x4 sem sequência, deu simio
    vector<string> dna7 = {"ATGC", "CAGT", "TTAT", "AGAA"};

    // 8. SÍMIO - matriz menor 4x4 com sequência horizontal
    vector<string> dna8 = {"AAAA", "CAGT", "TTAT", "AGAA"};

    // 9. SIMIO - sequência vertical na última coluna (GGGG)
    vector<string> dna = {"ATGCGG", "CAGTGG", "TTATGG", "AGAAGG", "CCCCTA", "TCACTG"};

    // 10. HUMANO - todas as letras diferentes sem repetição
    vector<string> dna10 = {"ATGCGA", "TCGATC", "GATCGA", "CGATCG", "ATCGAT", "TCGATC"};
    
    if (isSimian(dna)) {
        cout << "Simio" << endl;
    } else {
        cout << "Humano" << endl;
    }
    
    return 0;
}

/*
       j=0  j=1  j=2  j=3  j=4  j=5
i=0  [  C    T    G    A    G    A  ]
i=1  [  C    T    G    A    G    C  ]
i=2  [  T    A    T    T    G    T  ]
i=3  [  A    G    A    G    G    G  ]
i=4  [  C    C    C    C    T    A  ]
i=5  [  T    C    A    C    T    G  ]

*/