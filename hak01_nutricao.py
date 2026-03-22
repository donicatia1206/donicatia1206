print("--- PROTOCOLO D5: HAK 01 - SINTETIZAR NUTRIÇÃO ---")

alimento = input("O que você vai comer agora? ")
calorias = float(input(f"Quantas calorias tem 100g de {alimento}? (Aprox.): "))
quantidade = float(input("Quantas gramas você vai comer? "))

total_calorias = (calorias * quantidade) / 100

print("-" * 40)
print(f"RESUMO DA REFEIÇÃO:")
print(f"Alimento: {alimento}")
print(f"Total de Energia: {total_calorias:.2f} kcal")

if total_calorias > 500:
    print("Dica: Refeição pesada! Atenção ao índice glicêmico.")
else:
    print("Dica: Dentro do limite de performance. Bom apetite!")
print("-" * 40)
