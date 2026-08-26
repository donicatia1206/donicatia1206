# RELATÓRIO DE VALIDAÇÃO E SIMULAÇÃO VIRTUAL
**Projeto:** Palmilha Inteligente com Amortecimento Magnético Ativo  
**Instituição:** Etec Ary do Camargo Pedroso | **Curso:** Técnico em Eletroeletrônica  
**Integrantes:** Donizete, Arão, Áureo, Bruno, Guilherme  
**Link da Simulação:** [Wokwi Project 473442608376337409](https://wokwi.com/projects/473442608376337409)  

---

### 1. Resumo da Validação
O circuito e o firmware do MVP foram testados e aprovados no ambiente Wokwi. A simulação atestou a leitura analógica do sensor de pressão e a resposta proporcional do atuador PWM acionando a malha de amortecimento magnético.

---

### 2. Mapeamento de Pinos e Telemetria

* **ESP32-C3 (`GPIO 1`):** Entrada analógica do sensor de pressão (FSR-402 / Potenciômetro).
* **ESP32-C3 (`GPIO 2`):** Saída PWM (0 a 255) para controle de potência do MOSFET/Eletroímã.
* **Frequência de Amostragem:** 10 Hz (delay de 100 ms).

| Estado | Leitura ADC (`GPIO 1`) | Sinal PWM (`GPIO 2`) | Status Registrado |
| :--- | :--- | :--- | :--- |
| **Repouso** | $0$ a $150$ | $0$ | REPOUSO |
| **Carga Média** | $2334$ | $141$ | ATUANDO (Repulsa Magnética) |
| **Carga Máxima** | $4095$ | $255$ | ATUANDO (Repulsa Magnética) |

---

### 3. Conclusão Técnica
O algoritmo tratou com precisão o *noise floor* (ruído de leitura abaixo de 150 ADC) e realizou a conversão linear perfeita via `map()` e `constrain()`, liberando energia ao atuador proporcionalmente ao impacto sofrido pelo calcanhar.
