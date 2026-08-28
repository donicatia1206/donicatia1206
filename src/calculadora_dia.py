# PROJETO 5º ELEMENTO - AGENDA DE REGISTRO SEMANAL
PESO_ATUAL = 131.95
TMB_BASE = 2216

METS = {
    "1": ("Bike Leve / Lazer", 4.0),
    "2": ("Bike Moderada", 6.8),
    "3": ("Caminhada Leve", 3.0),
    "4": ("Musculação", 5.0),
    "5": ("Natação Leve", 4.5),
    "6": ("Crossfit", 8.0),
    "7": ("Corrida na Areia", 11.5),
}

dias_semana = [
    "Segunda-feira",
    "Terça-feira",
    "Quarta-feira",
    "Quinta-feira",
    "Sexta-feira",
    "Sábado",
    "Domingo",
]
registro_semana = []

print("==================================================")
print("  PROJETO 5º ELEMENTO - REGISTRO DE ATIVIDADES    ")
print("==================================================")
print(f"Perfil: Donizete | TMB Base: {TMB_BASE} kcal/dia\n")

for dia in dias_semana:
    print(f"--- {dia.upper()} ---")
    data = input(f"Data ({dia}) [deixe em branco se não preenchido]: ")

    if data.strip():
        passos = int(
            input("Passos registrados pela palmilha: ") or 0
        )
        consumo = float(
            input("Calorias consumidas (kcal): ") or 0
        )

        # Adição de atividade física extra por MET
        print("\nExercício Extra:")
        print("0 - Nenhum")
        for chave, (nome, met) in METS.items():
            print(f"{chave} - {nome}")

        opcao = input("Escolha a opção (0 a 7): ").strip()
        gasto_extra = 0.0

        if opcao in METS:
            minutos = float(
                input(
                    f"Tempo em minutos para {METS[opcao][0]}: "
                )
                or 0
            )
            met_val = METS[opcao][1]
            gasto_extra = met_val * PESO_ATUAL * (minutos / 60)
            print(
                f"-> Gasto extra calculado: {gasto_extra:.1f} kcal"
            )

        # Estimativa de gasto pelos passos (ex: ~0.05 kcal por passo a 131kg)
        gasto_passos = passos * 0.05
        gasto_total_dia = TMB_BASE + gasto_passos + gasto_extra
        balanco = consumo - gasto_total_dia

        registro_semana.append(
            {
                "dia": dia,
                "data": data,
                "passos": passos,
                "consumo": consumo,
                "extra": gasto_extra,
                "balanco": balanco,
                "preenchido": True,
            }
        )
    else:
        registro_semana.append(
            {
                "dia": dia,
                "data": "-",
                "passos": 0,
                "consumo": 0,
                "extra": 0,
                "balanco": -TMB_BASE,
                "preenchido": False,
            }
        )
    print()

# Exibição do Relatório
print("==================================================")
print("        RELATÓRIO DE CONSOLIDAÇÃO SEMANAL         ")
print("==================================================")
print(
    f"{'Dia':<13} | {'Data':<10} | {'Passos':<6} | {'Consumo':<7} | {'Extra':<7} | {'Balanço'}"
)
print("-" * 65)

total_passos = 0
total_consumo = 0
dias_com_dados = 0

for item in registro_semana:
    if item["preenchido"]:
        dias_com_dados += 1
        total_passos += item["passos"]
        total_consumo += item["consumo"]
        sinal = "+" if item["balanco"] > 0 else ""
        balanco_str = f"{sinal}{item['balanco']:.0f} kcal"
    else:
        balanco_str = f"{-TMB_BASE} kcal"

    print(
        f"{item['dia']:<13} | {item['data']:<10} | {item['passos']:<6} | {item['consumo']:<7.0f} | {item['extra']:<7.0f} | {balanco_str}"
    )

print("-" * 65)
media_passos = (
    total_passos / dias_com_dados if dias_com_dados > 0 else 0
)
media_consumo = (
    total_consumo / dias_com_dados if dias_com_dados > 0 else 0
)

print(f"Total de Passos na Semana : {total_passos:,} passos")
print(f"Média de Passos/Dia       : {media_passos:.0f} passos/dia")
print(
    f"Média Consumo Calórico    : {media_consumo:.0f} kcal/dia"
)
print("==================================================")
