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
    """Calcula a TMB exata do Donizete."""
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
        print("Sua gordura corporal está sendo queimada para suprir essa energia!")
    elif balanco > 0:
        print(f"⚠️ SUPERÁVIT CALÓRICO: +{balanco:.2f} kcal")
        print("Atenção: Ingestão acima do gasto diário.")
    else:
        print("⚖️ BALANÇO NEUTRO: 0 kcal")
        
    print("=" * 55)

# Exemplo de teste da função:
if __name__ == "__main__":
    # Simulação: consumindo 2000 kcal e dando 4000 passos com a palmilha
    diagnostico_dia(calorias_ingeridas=2000, passos_palmilha=4000)
