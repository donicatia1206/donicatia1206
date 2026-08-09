



# ⚡ PROJETO 5 ELEMENTO / GEMINIDONI
> **Módulo de Computação Metabólica & Biomecânica Aplicada**

---

## 🎯 Sobre o Projeto
O **Projeto 5 Elemento** é uma solução que integra engenharia biomecânica e acompanhamento nutricional para apoiar a redução de peso e a saúde articular.

- 🦶 **Palmilha Inteligente:** Amortecimento magnético ativo (ESP32-C3 + FSR-402 + MOSFET) para alívio imediato do estresse mecânico no calcanhar (esporão / fascite plantar).
- 🧮 **Motor Metabólico:** Algoritmo em Python para monitoramento diário do déficit calórico e integração da telemetria de passos.

---

## 📊 Perfil Biométrico & Parâmetros Base (Donizete)

| Parâmetro | Valor Configurado |
| :--- | :--- |
| **Peso Atual** | 131,95 kg |
| **Altura** | 1,85 m (185 cm) |
| **Idade** | 53 anos |
| **Sexo** | Masculino (M) |
| **Taxa Metabólica Basal (TMB)** | **~2.215,75 kcal/dia** |
| **Gasto Diário Estimado (Rotina)** | **~2.658,90 kcal/dia** |
| **Meta de Redução** | -37,0 kg |

---

## 🐍 Código do Motor Metabólico (`calculadora_deficit.py`)

```python
"""
PROJETO 5 ELEMENTO / GEMINIDONI
Módulo Metabólico Personalizado - Donizete
"""

# ==================================================
# PERFIL BIOMÉTRICO FIXO - DONIZETE
# ==================================================
PESO_ATUAL_KG = 131.95
ALTURA_CM = 185.0
IDADE_ANOS = 53
SEXO = 'M'
META_PERDA_KG = 37.0
# ==================================================

def calcular_tmb_donizete():
    """Calcula a TMB exata do Donizete (Mifflin-St Jeor)."""
    return (10 * PESO_ATUAL_KG) + (6.25 * ALTURA_CM) - (5 * IDADE_ANOS) + 5

def estimar_gasto_passos(passos):
    """Calcula o gasto dos passos considerando o peso atual de 131.95 kg."""
    fator_peso = PESO_ATUAL_KG / 70.0
    return passos * 0.04 * fator_peso

def diagnostico_dia(calorias_ingeridas, passos_palmilha=0):
    tmb = calcular_tmb_donizete()
    gasto_rotina = tmb * 1.2  # Gasto diário básico sem exercícios
    gasto_passos = estimar_gasto_passos(passos_palmilha)
    gasto_total = gasto_rotina + gasto_passos
    
    balanco = calorias_ingeridas - gasto_total
    
    print("=" * 55)
    print("      PROJETO 5 ELEMENTO - RELATÓRIO DO DONIZETE")
    print("=" * 55)
    print(f"📊 Peso Atual: {PESO_ATUAL_KG} kg | Altura: 1.85m | Idade: 53 anos")
    print(f"🔥 Sua TMB (Metabolismo Basal): {tmb:.2f} kcal")
    print(f"🚶 Gasto Extra Palmilha ({passos_palmilha} passos): {gasto_passos:.2f} kcal")
    print(f"⚡ GASTO ENERGÉTICO TOTAL HOJE: {gasto_total:.2f} kcal")
    print(f"🍽️ Calorias Ingeridas: {calorias_ingeridas:.2f} kcal")
    print("-" * 55)
    
    if balanco < 0:
        deficit = abs(balanco)
        print(f"✅ DÉFICIT ATINGIDO: -{deficit:.2f} kcal")
        print("Sua gordura corporal está sendo queimada como energia!")
    elif balanco > 0:
        print(f"⚠️ SUPERÁVIT CALÓRICO: +{balanco:.2f} kcal")
        print("Atenção: Ingestão acima do gasto diário.")
    else:
        print("⚖️ BALANÇO NEUTRO: 0 kcal")
        
    print("=" * 55)

if __name__ == "__main__":
    # Exemplo de teste: 2000 kcal ingeridas e 4000 passos na palmilha
    diagnostico_dia(calorias_ingeridas=2000, passos_palmilha=4000)

