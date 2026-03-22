#include "simian.h"
#include <vector>
#include <string>

bool isSimian(const std::vector<std::string>& dna) {
    const int n = static_cast<int>(dna.size());
    if (n == 0) return false;
    const int m = static_cast<int>(dna[0].size());

    const int direcoes[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int d = 0; d < 4; d++) {
                const int di = direcoes[d][0];
                const int dj = direcoes[d][1];
                int iguais = 0;

                for (int passo = 0; passo < 4; passo++) {
                    const int novaLinha  = i + di * passo;
                    const int novaColuna = j + dj * passo;

                    if (novaLinha < 0 || novaLinha >= n ||
                        novaColuna < 0 || novaColuna >= m) {
                        break;
                    }

                    if (dna[novaLinha][novaColuna] == dna[i][j]) {
                        iguais++;
                    } else {
                        break;
                    }
                }

                if (iguais == 4) return true;
            }
        }
    }

    return false;
}