"""
PROJETO 5 ELEMENTO / GEMINIDONI
Módulo de Computação Metabólica e Cálculo de Déficit Calórico

Desenvolvido por: Donizete (Idealizador) & Gemini
Versão: 1.0 (MVP)
"""

def calcular_tmb(peso_kg, altura_cm, idade_anos, sexo):
    """
    Calcula a Taxa Metabólica Basal (TMB) utilizando a fórmula de Mifflin-St Jeor.
    """
    if sexo.lower() in ['m', 'masculino']:
        tmb = (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade_anos) + 5
    elif sexo.lower() in ['f', 'feminino']:
        tmb = (10 * peso_kg) + (6.25 * altura_cm) - (5 * idade_anos) - 161
    else:
        raise ValueError("Sexo deve ser 'M' para Masculino ou 'F' para Feminino.")
    return tmb


def calcular_gasto_total(tmb, fator_atividade):
    """
    Calcula o Gasto Energético Total Diário (GETD) multiplicando a TMB pelo fator de atividade.
    Fatores padrão:
    1.2   - Sedentário (pouco ou nenhum exercício)
    1.375 - Levemente ativo (exercício leve 1 a 3 dias/semana)
    1.55  - Moderadamente ativo (exercício moderado 3 a 5 dias/semana)
    1.725 - Muito ativo (exercício pesado 6 a 7 dias/semana)
    """
    return tmb * fator_atividade


def estimar_gasto_passos_palmilha(passos, peso_kg):
    """
    Estimativa simplificada de gasto calórico baseado no trabalho mecânico das pisadas
    (Telemetria futura do ESP32/FSR-402).
    Aprox: 0.04 kcal por passo para um peso médio, ajustado proporcionalmente ao peso.
    """
    fator_peso = peso_kg / 70.0  # Referência base de 70 kg
    calorias_passos = passos * 0.04 * fator_peso
    return calorias_passos


def processar_deficit(gasto_total, calorias_ingestao):
    """
    Calcula o déficit ou superávit calórico diário.
    """
    balanco = calorias_ingestao - gasto_total
    return balanco


def main():
    print("=" * 55)
    print("      PROJETO 5 ELEMENTO - MOTOR METABÓLICO v1.0")
    print("=" * 55)

    # Input de Dados Perfil
    try:
        peso = float(input("Digite seu peso atual (kg): "))
        altura = float(input("Digite sua altura (cm): "))
        idade = int(input("Digite sua idade (anos): "))
        sexo = input("Digite seu sexo (M/F): ").strip()

        # Cálculo da TMB
        tmb = calcular_tmb(peso, altura, idade, sexo)
        print(f"\n[+] Taxa Metabólica Basal (TMB): {tmb:.2f} kcal/dia")

        # Nível de Atividade Geral
        print("\nEscolha o nível de atividade diária:")
        print("1 - Sedentário (pouco ou nenhum exercício)")
        print("2 - Levemente ativo (caminhadas leves / rotina diária)")
        print("3 - Moderadamente ativo (exercício 3-5x/semana)")
        opcao_atv = input("Opção (1-3): ").strip()

        fatores = {"1": 1.2, "2": 1.375, "3": 1.55}
        fator = fatores.get(opcao_atv, 1.2)

        gasto_basal_atividade = calcular_tmb(peso, altura, idade, sexo) * fator

        # Telemetria da Palmilha (Simulação ou Inserção Manual)
        usar_palmilha = input("\nDeseja incluir telemetria de passos da palmilha? (S/N): ").strip().lower()
        gasto_extra_passos = 0.0

        if usar_palmilha == 's':
            passos = int(input("Informe o total de passos registrados hoje: "))
            gasto_extra_passos = estimar_gasto_passos_palmilha(passos, peso)
            print(f"[+] Gasto estimado pelos passos (Palmilha): {gasto_extra_passos:.2f} kcal")

        gasto_total = gasto_basal_atividade + gasto_extra_passos
        print(f"\n[=] GASTO ENERGÉTICO TOTAL ESTIMADO: {gasto_total:.2f} kcal/dia")

        # Ingestão Alimentar
        calorias_consumidas = float(input("\nDigite o total de calorias consumidas hoje (kcal): "))

        # Resultado do Déficit
        balanco = processar_deficit(gasto_total, calorias_consumidas)

        print("\n" + "=" * 55)
        print("                  DIAGNÓSTICO DIÁRIO")
        print("=" * 55)

        if balanco < 0:
            deficit = abs(balanco)
            print(f"✅ DÉFICIT CALÓRICO ATINGIDO: -{deficit:.2f} kcal")
            print("Excelente! Seu corpo usou reservas de gordura como fonte de energia.")
        elif balanco > 0:
            print(f"⚠️ SUPERÁVIT CALÓRICO: +{balanco:.2f} kcal")
            print("Atenção: Você consumiu mais energia do que gastou hoje.")
        else:
            print("⚖️ BALANÇO NEUTRO: 0 kcal de diferença")
            print("Seu peso se manterá estável com essa faixa de ingestão.")

        print("=" * 55)

    except ValueError as e:
        print(f"\n❌ Erro na entrada de dados: {e}. Certifique-se de digitar números válidos.")


if __name__ == "__main__":
    main()
