# ============================================================
# PROJETO 5º ELEMENTO — DIAGNÓSTICO E AGENDA SEMANAL
# ============================================================

def calcular_tmb_mifflin(peso_kg, altura_cm, idade, sexo='M'):
    """Calcula a Taxa Metabólica Basal pela Fórmula Mifflin-St Jeor"""
    if sexo.upper() == 'M':
        return (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade) + 5
    else:
        return (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade) - 161

def menu_agenda_semanal():
    # Parâmetros Biométricos Fixos (Donizete)
    PESO = 131.95
    ALTURA = 185
    IDADE = 53
    
    tmb = calcular_tmb_mifflin(PESO, ALTURA, IDADE, 'M')
    
    # Estrutura da Agenda Semanal
    dias_semana = [
        "Segunda-feira",
        "Terça-feira",
        "Quarta-feira",
        "Quinta-feira",
        "Sexta-feira",
        "Sábado",
        "Domingo"
    ]
    
    registros = []
    
    print("=" * 60)
    print("   PROJETO 5º ELEMENTO - AGENDA DE REGISTRO SEMANAL")
    print("=" * 60)
    print(f"Perfil: Donizete | TMB Base: {tmb:.0f} kcal/dia\n")
    
    total_passos = 0
    total_calorias_consumidas = 0
    
    for dia in dias_semana:
        print(f"\n--- {dia.upper()} ---")
        data = input(f"Data ({dia}): ")
        
        try:
            passos = int(input("Passos registrados pela palmilha: ") or 0)
            calorias = float(input("Calorias consumidas (kcal): ") or 0)
        except ValueError:
            print("Entrada inválida! Registrando 0 para este dia.")
            passos, calorias = 0, 0.0

        # Estimativa simples de gasto por passos (aprox. 0.04 kcal por passo)
        gasto_passos = passos * 0.04
        gasto_total_dia = tmb + gasto_passos
        balanco_dia = calorias - gasto_total_dia
        
        # Meta de água recomendada: 35ml por kg + 500ml a cada 5000 passos
        agua_recomendada_litros = ((PESO * 35) + (passos / 5000 * 500)) / 1000
        
        registros.append({
            "dia": dia,
            "data": data,
            "passos": passos,
            "calorias": calorias,
            "gasto": gasto_total_dia,
            "balanco": balanco_dia,
            "agua": agua_recomendada_litros
        })
        
        total_passos += passos
        total_calorias_consumidas += calorias

    # RESUMO DA SEMANA
    print("\n" + "=" * 60)
    print("           RELATÓRIO DE CONSOLIDAÇÃO SEMANAL")
    print("=" * 60)
    print(f"{'Dia':<15} | {'Data':<10} | {'Passos':<8} | {'Consumo':<8} | {'Balanço'}")
    print("-" * 60)
    
    for r in registros:
        val_balanco = r['balanco']
        status_balanco = f"{val_balanco:+.0f} kcal"
        print(f"{r['dia']:<15} | {r['data']:<10} | {r['passos']:<8} | {r['calorias']:<8.0f} | {status_balanco}")
        
    print("-" * 60)
    print(f"Total de Passos na Semana : {total_passos:,} passos")
    print(f"Média de Passos/Dia       : {total_passos // 7:,} passos/dia")
    print(f"Média Consumo Calórico    : {total_calorias_consumidas / 7:.0f} kcal/dia")
    print("=" * 60)

if __name__ == "__main__":
    menu_agenda_semanal()
