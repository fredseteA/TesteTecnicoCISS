# Teste Símios - CISS

Projeto desenvolvido para o Programa de Formação CISS. O objetivo é identificar se uma sequência de DNA pertence a um humano ou a um símio, com base na presença de sequências de 4 letras iguais consecutivas na matriz de DNA.

**Autor:** Frederico de Freitas Luna Filho

---

## Tecnologias utilizadas

- C++ (G++ 15.2.0)

---

## Níveis

- ✅ Nível 1 — Algoritmo `isSimian`
- 🔧 Nível 2 — API REST (em desenvolvimento)
- 🔧 Nível 3 — Banco de dados e estatísticas (em desenvolvimento)

---

## Nível 1 — Algoritmo

### Como funciona

A função `isSimian` recebe um array de strings representando uma matriz NxN de DNA. Ela varre a matriz nas 4 direções possíveis (horizontal, vertical, diagonal principal e diagonal secundária) procurando sequências de 4 letras iguais consecutivas. Se encontrar ao menos uma, retorna `true` (símio), caso contrário retorna `false` (humano).

### Pré-requisitos

- G++ instalado (versão 15.2.0 ou superior)

Para verificar se o G++ está instalado, rode no terminal:

```bash
g++ --version
```

### Como compilar

Navegue até a pasta `src` do projeto e rode:

```bash
g++ simian.cpp -o simian
```

### Como executar

```bash
./simian
```

### Exemplo de uso

Edite o arquivo `simian.cpp` e altere o array `dna` no `main` com a sequência que deseja testar:

```cpp
vector<string> dna = {"CTGAGA", "CTGAGC", "TATTGT", "AGAGGG", "CCCCTA", "TCACTG"};
```

**Saída esperada para símio:**
```
Simio
```

**Saída esperada para humano:**
```
Humano
```

### Exemplos de teste

| DNA | Resultado esperado |
|-----|--------------------|
| `{"CTGAGA", "CTGAGC", "TATTGT", "AGAGGG", "CCCCTA", "TCACTG"}` | Símio (horizontal) |
| `{"ATGCGA", "AGTCGC", "ATAGTT", "AGAAGG", "ATCCTA", "TCACTG"}` | Símio (vertical) |
| `{"ATGCGA", "CAGTGC", "TTATTT", "AGACGG", "GCGTCA", "TCACTG"}` | Humano |

---

## Estrutura do projeto

```
TesteTecnicoCISS/
├── src/
│   ├── simian.cpp      # Algoritmo principal (Nível 1)
│   ├── simian.h        # Header
│   ├── api.cpp         # API REST (Nível 2)
│   └── database.cpp    # Banco de dados (Nível 3)
├── CMakeLists.txt
└── README.md
```