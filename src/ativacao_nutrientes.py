# ==============================================================================
# PROJETO 5o ELEMENTO / GEMINI-DONI - MODULO DE INTELIGENCIA NUTRICIONAL
# ==============================================================================
# Usuario: Donizete dos Santos
# Perfil: 53 anos | Altura: 1,85m | Peso Atual: 131,95 kg
# Objetivo: Perda de peso sustentavel, maxima biodisponibilidade e densidade nutricional
#
# CONCEITOS FUNDAMENTAIS DE DESIGN NUTRICIONAL:
# ------------------------------------------------------------------------------
# 1. Ativacao de Nutrientes (Biodisponibilidade)
#    O modo de preparo e as combinacoes dos alimentos alteram diretamente o quanto
#    o corpo consegue absorver dos nutrientes:
#    - Combinacao estrategica: Parear vegetal escuro com fonte de vitamina C (como
#      limao na couve) multiplica a absorcao de ferro nao-heme.
#    - Tecnica de coccao: Legumes como couve-flor, brocolis e alho-poro aproveitam
#      melhor suas propriedades bioativas quando cozidos no vapor leve ou rapidamente
#      salteados, evitando a perda de vitaminas hidrossoluceis na agua do cozimento.
#    - Gorduras boas: Vitaminas lipossoluceis (A, D, E, K) precisam de uma fonte
#      leve de gordura (como um fio de azeite de oliva) para serem devidamente
#      absorvidas.
#
# 2. Saciedade Sem Excesso
#    Focar em densidade nutricional e volume alimentar em vez de calorias vazias:
#    - Fibras e volume: Vegetais ricos em fibras estruturais e agua preenchem o
#      volume gastrico e desaceleram o esvaziamento do estomago.
#    - Controle glicemico: A mastigacao prolongada e o aporte de fibras reduzem
#      picos de insulina, mantendo a saciedade estavel por mais tempo sem necessitar
#      de porcoes hipercaloricas.
#
# 3. Sabor Sem Excesso
#    Extrair o sabor natural dos alimentos sem recorrer a excesso de sal, oleos
#    refinados ou temperos ultraprocessados:
#    - Uso de aromaticos: Alho-poro, alho, cebola, ervas frescas e especiarias
#      (curcuma, pimenta-do-reino) conferem um perfil de sabor rico e complexo
#      sem adicionar calorias ou sodio excessivo.
#    - Tecnicas de tostagem: Dourar levemente os vegetais na frigideira, air fryer,
#      forno eletrico ou grelha da churrasqueira ativa a Reacao de Maillard,
#      que realca o adocicado e o sabor natural do alimento.
# ==============================================================================

import json

# ------------------------------------------------------------------------------
# ETAPA 1: Dicionario de Regras de Ativacao de Nutrientes
# ------------------------------------------------------------------------------
regras_ativacao = {
    "ferro_nao_heme": {
        "nutriente": "Ferro Vegetal (Nao-Heme)",
        "alimentos_fonte": ["couve", "espinafre", "feijao", "lentilha"],
        "ativador": "Vitamina C",
        "exemplos_ativador": ["suco de limao", "laranja", "pimentao cru"],
        "mecanismo": "Reduz o ferro ferrico (Fe3+) a ferro ferroso (Fe2+), multiplicando a absorcao intestinal."
    },
    "vitaminas_lipossoluveis": {
        "nutriente": "Vitaminas A, D, E e K / Licopeno / Betacaroteno",
        "alimentos_fonte": ["cenoura", "abobora", "tomate", "vegetais verde-escuros"],
        "ativador": "Gordura Boa / Lipidios Leves",
        "exemplos_ativador": ["fio de azeite de oliva extravirgem", "sementes de abobora", "gergelim"],
        "mecanismo": "Forma micelas lipidicas que viabilizam a solubilizacao e transporte dos micronutrientes."
    },
    "compostos_sulfurados": {
        "nutriente": "Alicina e Isoflavanoides Bioativos",
        "alimentos_fonte": ["alho", "cebola", "alho-poro"],
        "ativador": "Tempo de Descanso Pos-Corte (Reacao Enzimatica)",
        "exemplos_ativador": ["Aguardar 10 minutos apos picar/amassar antes de aquecer"],
        "mecanismo": "Permite que a enzima aliinase converta aliina em alicina ativa, altamente protetora."
    },
    "curcumina_sinergica": {
        "nutriente": "Curcumina (Anti-inflamatorio Natural)",
        "alimentos_fonte": ["curcuma (acafrao-da-terra)"],
        "ativador": "Piperina",
        "exemplos_ativador": ["pimenta-do-reino moida na hora"],
        "mecanismo": "Inibe a glucuronidacao hepatica e intestinal, aumentando a biodisponibilidade em ate 2000%."
    }
}

# ------------------------------------------------------------------------------
# ETAPA 2: Mapeamento de Recomendacao de Preparo e Coccao
# ------------------------------------------------------------------------------
def recomendar_preparo(ingrediente):
    """
    Retorna a tecnica de preparo ideal para o ingrediente informado,
    focando na preservacao de micronutrientes e no controle calorico.
    """
    ingrediente_norm = ingrediente.lower().strip()
    
    tecnicas = {
        "vapor_ou_salteado": {
            "itens": ["couve-flor", "brocolis", "alho-poro", "espinafre", "couve"],
            "metodo": "Vapor leve (2 a 4 min) ou salteado rapido em fogo alto",
            "vantagem": "Preserva vitaminas hidrossoluceis (Complexo B e Vit C) e evita perda de glucosinolatos na agua."
        },
        "assado_ou_grelhado": {
            "itens": ["abobora", "cenoura", "berinjela", "abobrinha", "pimentao"],
            "metodo": "Air fryer, forno eletrico ou grelha da churrasqueira (calor seco sem oleo em excesso)",
            "vantagem": "Ativa a Reacao de Maillard, caramelizando acucares naturais do vegetal e concentrando sabor."
        },
        "remolho_e_pressao": {
            "itens": ["feijao", "feijoada", "lentilha", "grao-de-bico"],
            "metodo": "Remolho previo de 12h a 24h (descarte da agua) + cozimento em panela de pressao",
            "vantagem": "Elimina fitatos e oligossacarideos (antinutrientes) facilitando a digestao e absorcao de minerais."
        },
        "refogado_aromatico": {
            "itens": ["alho", "cebola"],
            "metodo": "Dourado leve em fogo medio com gotas de azeite ou agua",
            "vantagem": "Libera oleos essenciais aromaticos sem oxidar a materia organica."
        }
    }
    
    for chave, dados in tecnicas.items():
        if any(item in ingrediente_norm for item in dados["itens"]):
            return {
                "ingrediente": ingrediente,
                "metodo_recomendado": dados["metodo"],
                "beneficio_tecnico": dados["vantagem"]
            }
            
    return {
        "ingrediente": ingrediente,
        "metodo_recomendado": "Grelhado leve ou cozido a baixa temperatura",
        "beneficio_tecnico": "Manutencao da integridade estrutural do alimento."
    }

# ------------------------------------------------------------------------------
# ETAPA 3: Mapeamento de Aromas e Sabor (Sabor Sem Excesso)
# ------------------------------------------------------------------------------
potencializadores_sabor = {
    "bases_aromaticas": [
        "alho-poro picado", "cebola roxa", "alho amassado",
        "cheiro-verde fresco", "alecrim", "salvia"
    ],
    "especiarias_termogenicas": [
        {"nome": "Curcuma + Pimenta-do-reino", "funcao": "Sinergia anti-inflamatoria e cor dourada viva"},
        {"nome": "Paprica Defumada", "funcao": "Fornece nota de defumado sem necessidade de carnes gordurosas"},
        {"nome": "Gengibre ralado", "funcao": "Refrescancia, picancia natural e estimulo digestivo"}
    ],
    "tecnicas_intensificadoras": [
        "Tostagem a seco na frigideira de ferro ou antiaderente",
        "Finalizacao com gotas de suco de limao para realcar o sal natural",
        "Uso de ervas desidratadas na etapa de cozimento e frescas na finalizacao"
    ]
}

# ------------------------------------------------------------------------------
# DEMONSTRACAO / TESTE DO MODULO
# ------------------------------------------------------------------------------
if __name__ == "__main__":
    print("==================================================================")
    print("PROJETO 5o ELEMENTO - SISTEMA DE ATIVACAO DE NUTRIENTES")
    print("==================================================================")
    print(f"Usuario: Donizete | Perfil: 1,85m | {131.95}kg | 53 anos")
    print("------------------------------------------------------------------\n")
    
    print("1. EXEMPLO DE REGRAS DE ATIVACAO:")
    for chave, info in regras_ativacao.items():
        print(f"* [{info['nutriente']}]")
        print(f"  Ativador: {info['ativador']} ({', '.join(info['exemplos_ativador'])})")
        print(f"  Beneficio: {info['mecanismo']}\n")
        
    print("------------------------------------------------------------------")
    print("2. TESTE DA FUNCAO DE RECOMENDACAO DE PREPARO:")
    ingredientes_teste = ["couve-flor", "abobora", "feijao", "alho-poro"]
    for ing in ingredientes_teste:
        rec = recomendar_preparo(ing)
        print(f"* Ingrediente: {rec['ingrediente'].upper()}")
        print(f"  Metodo: {rec['metodo_recomendado']}")
        print(f"  Razao: {rec['beneficio_tecnico']}\n")
        
    print("------------------------------------------------------------------")
    print("3. POTENCIALIZADORES DE SABOR (SEM EXCESSO DE SODIO/GORDURA):")
    print("Bases Aromaticas:", ", ".join(potencializadores_sabor["bases_aromaticas"]))
    print("Especiarias Chave:")
    for esp in potencializadores_sabor["especiarias_termogenicas"]:
        print(f"  - {esp['nome']}: {esp['funcao']}")
    print("==================================================================")
