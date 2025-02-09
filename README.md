# README - Trabalho Prático 2 de Introdução à Inteligência Artificial

## 📌 Descrição do Projeto
Este projeto aborda um problema de otimização em grafos, onde o objetivo é encontrar um subconjunto de vértices com um custo total mínimo. Para isso, foram implementados diferentes algoritmos e heurísticas para resolver o problema, incluindo Hill Climbing e algoritmos evolutivos.

## 👥 Autores
- Lucas Erardo Alves da Graça Monteiro - 2022153271
- Timoffy Drohin - 2022161633

## 👨‍🏫 Professores
- Carlos Manuel Jorge da Silva Pereira
- Anabela Borges Simões

## 📂 Estrutura do Código
O projeto contém as seguintes funções principais:

### 1. Representação do Problema e Função de Avaliação
- A solução é representada como um vetor de inteiros, indicando quais vértices pertencem ao subconjunto ótimo.
- A função `calculaCustoTotal` calcula o custo total da solução, somando os custos das arestas conectadas aos vértices selecionados.
- A função `validateSolution` verifica se uma solução gerada atende aos critérios de validade.

### 2. Algoritmos e Heurísticas Utilizados
- **Hill Climbing**: Busca local que encontra a melhor solução vizinha em cada iteração. Implementações:
  - `Hill_Climbing`
  - `Hill_Climbing_2`
- **Recombinação (Crossover)**:
  - `algoritmoRecombinacao_Single_Point_Crossover`
  - `algoritmoRecombinacao_Double_Point_Crossover`
- **Mutação**:
  - `algoritmoMutacao_Troca`
  - `algoritmoMutacao_Insercao`
- **Abordagens Híbridas**:
  - `Hibrido`
  - `Hibrido_2`

### 3. Justificativa das Escolhas
- A diversidade de métodos foi utilizada para equilibrar exploração e explotação do espaço de soluções.
- Abordagens híbridas foram implementadas para aumentar a eficiência na busca pela melhor solução.

### 4. Resultados Obtidos
- Foram realizadas diversas execuções para avaliar a eficiência dos algoritmos.
- O estudo dos dados mostrou que, com mais iterações, as soluções se aproximam da ótima.
- Algoritmos com maior número de vizinhos tendem a explorar melhor o espaço de busca.

## 🚀 Como Executar o Projeto
1. Clone este repositório:
   ```bash
   git clone https://github.com/LucasMonteiro2004/Work2_IIA.git
   cd Work2_IIA
   ```
2. Compile o código:
   ```bash
   gcc -o programa main.c mat.c utils.c -Wall
   ```
3. Execute o programa:
   ```bash
   ./programa
   ```

## 📜 Licença

---
📌 **Observação:** Este README resume as informações do relatório do projeto. Para mais detalhes, consulte o documento original. 🚀

