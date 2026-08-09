# ♒ Projeto GeminiDoni: Sistema de Monitoramento Hídrico

### 🏛️ Sobre o Projeto
Este repositório integra o **Acervo GeminiDoni**. [span_4](start_span)O software foi desenvolvido para o primeiro módulo de Desenvolvimento de Sistemas (DSI), utilizando a tecnologia (o **Quinto Elemento**) para equilibrar o elemento fundamental **Água**[span_4](end_span).

### 🚀 Filosofia de Desenvolvimento
[span_5](start_span)Seguindo o **Legacy Mode**, este código é um guia autônomo focado em performance física e mental[span_5](end_span). Aplicamos os conceitos de:
* **[span_6](start_span)Abacaxi x Batata:** Código denso e eficiente para garantir "saciedade lógica"[span_6](end_span).
* **[span_7](start_span)Terra x Mar:** Uma estrutura de dados organizada que reflete a origem da informação[span_7](end_span).

### 🛠️ Funcionalidades
* Monitorização de 5 níveis de criticidade de reservatórios.
* Interface visual via terminal utilizando **Sequências de Escape ANSI** para máxima acessibilidade mobile.
* [span_8](start_span)Sistema digital, ético e funcional[span_8](end_span).

### 🔑 Estética Visual (Elementos)
* 🔴 **Nível 1:** Crítico
* 🟡 **Nível 2:** Baixo
* 🟢 **Nível 3:** Médio
* 🔵 **Nível 5:** Alerta


## 🧮 Calculadora de Déficit Calórico (Módulo Python)

```python
"""
PROJETO 5 ELEMENTO / GEMINIDONI
Módulo de Computação Metabólica e Cálculo de Déficit Calórico
"""

def calcular_tmb(peso_kg, altura_cm, idade_anos, sexo):
    if sexo.lower() in ['m', 'masculino']:
        return (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade_anos) + 5
    elif sexo.lower() in ['f', 'feminino']:
        return (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade_anos) - 161
    raise ValueError("Sexo deve ser 'M' ou 'F'.")

def estimar_gasto_passos(passos, peso_kg):
    return passos * 0.04 * (peso_kg / 70.0)

def main():
    print("=" * 50)
    print("   PROJETO 5 ELEMENTO - CALCULADORA DE DÉFICIT")
    print("=" * 50)
    
    peso = float(input("Peso (kg): "))
    altura = float(input("Altura (cm): "))
    idade = int(input("Idade (anos): "))
    sexo = input("Sexo (M/F): ").strip()
    
    tmb = calcular_tmb(peso, altura, idade, sexo)
    gasto_total = tmb * 1.2
    
    usar_passos = input("Incluir passos da palmilha? (S/N): ").strip().lower()
    if usar_passos == 's':
        passos = int(input("Total de passos hoje: "))
        gasto_total += estimar_gasto_passos(passos, peso)
        
    calorias_ingestao = float(input("Calorias consumidas hoje (kcal): "))
    balanco = calorias_ingestao - gasto_total
    
    print("\n" + "=" * 50)
    if balanco < 0:
        print(f"✅ DÉFICIT CALÓRICO: -{abs(balanco):.2f} kcal")
    else:
        print(f"⚠️ SUPERÁVIT CALÓRICO: +{balanco:.2f} kcal")
    print("=" * 50)

if __name__ == "__main__":
    main()
