nome = input("Aparelho: ")
watts = float(input("Potência (W): "))
horas = float(input("Horas de uso diário: "))

# Calcula o consumo mensal em kWh
consumo = (watts * horas * 30) / 1000

# Calcula o custo estimado (R$ 0,75 por kWh)
custo = consumo * 0.75

print("-" * 30)
print(f"Aparelho: {nome}")
print(f"Consumo Mensal: {consumo:.2f} kWh")
print(f"Custo Mensal Estimado: R$ {custo:.2f}")
print("-" * 30)
