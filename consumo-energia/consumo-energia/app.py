nome = input("Aparelho: ")
watts = float(input("Watts: "))
horas = float(input("Horas/dia: "))
consumo = (watts * horas * 30) / 1000
print(f"Consumo: {consumo:.2f} kWh/mes")
