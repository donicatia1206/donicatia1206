# Guia Teórico & Fórmulas — Calculadora de Balanço Calórico

Este documento detalha a fundamentação fisiológica, os parâmetros de entrada e o modelo matemático utilizados pelo script `calculadora_dia.py` no **Projeto 5º Elemento**.

---

## 1. Conceitos Fisiológicos Fundamentais

* **TMB (Taxa Metabólica Basal):** Representa a quantidade mínima de energia (em quilocalorias) necessária para o corpo manter suas funções vitais em repouso absoluto ao longo de 24 horas (respiração, batimentos cardíacos, atividade cerebral e regulação térmica).
* **MET (Equivalente Metabólico do Trabalho):** Unidade padronizada para quantificar a intensidade e o custo energético de atividades físicas. 
  * **1 MET** equivale ao consumo de oxigênio em repouso.
  * Atividades com **MET maiores** representam múltiplos do gasto em repouso proporcional ao peso corporal.
* **Déficit Calórico:** Situação metabólica na qual o gasto energético total do organismo supera o consumo calórico alimentício diário, promovendo a utilização de reservas lipídicas.

---

## 2. Tabela de Equivalência de Atividades (Valores de MET)

Abaixo estão os coeficientes cadastrados no sistema para cálculo do gasto calórico extra:

| Código | Modalidade / Atividade Física | Valor MET |
| :---: | :--- | :---: |
| **1** | Ciclismo Leve / Lazer (< 16 km/h) | 4.0 |
| **2** | Ciclismo Moderado (16 a 19 km/h) | 6.8 |
| **3** | Caminhada Leve / Moderada (4 km/h) | 3.0 |
| **4** | Musculação / Treino de Força | 5.0 |
| **5** | Natação Leve / Recreativa | 4.5 |
| **6** | Treino Funcional / CrossFit | 8.0 |
| **7** | Corrida em Areia Fofa | 11.5 |

---

## 3. Modelo Matemático e Fórmulas

### A. Gasto Físico Extra por Atividade (METs)

$$\text{Gasto Extra (kcal)} = \text{MET} \times \text{Peso Corporal (kg)} \times \left(\frac{\text{Tempo em Minutos}}{60}\right)$$

**Exemplo Prático (30 minutos de Ciclismo Leve a 131,95 kg):**

$$\text{Gasto Extra} = 4,0 \times 131,95 \times \left(\frac{30}{60}\right) = 4,0 \times 131,95 \times 0,5 = 263,9 \text{ kcal}$$

### B. Balanço Calórico Diário Consolidado

$$\text{Gasto Total do Dia} = \text{TMB Base} + (\text{Passos} \times 0.05) + \text{Gasto Extra (METs)}$$

$$\text{Balanço Calórico} = \text{Consumo Alimentar} - \text{Gasto Total do Dia}$$

* **Resultado Negativo (-):** Déficit Calórico obtido.
* **Resultado Positivo (+):** Superávit Calórico obtido.

---

## 4. Regras de Integridade e Trata de Dados

* **Prevenção de Dupla Contagem:** Atividades aeróbicas registradas por tempo evitam sobreposição com contagem de passos de caminhada.
* **Cálculo Fidedigno de Médias:** Dias não preenchidos na semana são ignorados no cálculo de média diária para não distorcer o relatório.
