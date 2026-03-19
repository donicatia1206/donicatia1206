# CALCULADORA 5º ELEMENTO - DONIZETE
# Peso: 137kg | Altura: 1,87m

kcal_churrasco = 1420
peso = 137

# A conta que o computador faz para você:
def calcular_recuperacao():
    print(f"--- RELATÓRIO DE IMPACTO ---")
    print(f"Consumo: {kcal_churrasco} calorias")
    
    # Natacao gasta aprox. 7 METs por hora
    tempo_natacao = kcal_churrasco / (7.0 * peso)
    
    print(f"PARA ZERAR O CHURRASCO:")
    print(f"Tempo de Natação: {tempo_natacao:.1f} horas")
    print("----------------------------")
    print("DICA: Use Abacaxi (Bromelina) para digerir a carne!")

calcular_recuperacao()
