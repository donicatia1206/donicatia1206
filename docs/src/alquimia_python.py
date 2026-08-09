class AlquimiaAlimentar:
    @staticmethod
    def indice_saciedade(p: float, f: float, v: float) -> float:
        # Cálculo de estimativa baseado em Proteínas (p), Fibras (f) e Volume (v)
        score = (p * 1.5) + (f * 2.0) + (v * 0.05)
        return min(score, 100.0)

class PerfilUsuario:
    @staticmethod
    def calcular_gasto_passos(passos: int) -> float:
        # Média de 0.04 kcal gastas por passo
        return passos * 0.04

def menu_alquimia():
    perfil = PerfilUsuario()
    
    print("-" * 40)
    print("1. Estimativa de Saciedade (HAKs de Alquimia)")
    print("2. Simulação de Déficit com Passos")
    print("-" * 40)

    opcao = input("Escolha uma opção (1 ou 2): ")

    if opcao == "1":
        try:
            p = float(input("Proteínas (g): "))
            f = float(input("Fibras (g): "))
            v = float(input("Volume total (ml/g): "))
            score = AlquimiaAlimentar.indice_saciedade(p, f, v)
            print(f"\n✨ Índice de Saciedade Calculado: {score:.1f} / 100")
        except ValueError:
            print("\n❌ Por favor, insira valores numéricos válidos.")

    elif opcao == "2":
        try:
            passos = int(input("Passos registrados na palmilha: "))
            gasto_passos = perfil.calcular_gasto_passos(passos)
            print(f"\n🔥 Gasto estimado pelos passos: {gasto_passos:.2f} kcal")
        except ValueError:
            print("\n❌ Por favor, insira um número inteiro para os passos.")

    else:
        print("Opção inválida.")

if __name__ == "__main__":
    menu_alquimia()
