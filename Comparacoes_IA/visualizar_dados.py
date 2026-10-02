import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def gerar_graficos(dados, col_x, cols_y, col_categoria=None, titulo_base=None, label_x=None, label_y=None):
    """ 
    Gera gráficos a partir de um DataFrame ou caminho de CSV. 
    'dados' pode ser uma string (caminho) ou um pandas DataFrame.
    """
    try:
        # Verifica se 'dados' é caminho ou DataFrame
        if isinstance(dados, str):
            if not os.path.exists(dados):
                print(f"Erro: O arquivo '{dados}' não foi encontrado.")
                return
            df = pd.read_csv(dados)
        else:
            df = dados

        os.makedirs("resultados", exist_ok=True)
        sns.set_theme(style="whitegrid")

        categorias = df[col_categoria].unique() if col_categoria and col_categoria in df.columns else [None]

        for cat in categorias:
            plt.figure(figsize=(10, 6))
            
            dados_subset = df[df[col_categoria] == cat] if cat is not None else df
            # Ordenar por X para evitar linhas "cruzadas" no gráfico
            dados_subset = dados_subset.sort_values(by=col_x)
            
            for col_y in cols_y:
                if col_y in dados_subset.columns:
                    plt.plot(dados_subset[col_x], dados_subset[col_y], 
                             marker='o', label=col_y, linewidth=2)
            
            plt.title(titulo_base if titulo_base else str(cat), fontsize=15, fontweight='bold')
            plt.xlabel(label_x if label_x else col_x, fontsize=12)
            plt.ylabel(label_y if label_y else 'Tempo de Execução (s)', fontsize=12)
            
            plt.legend()
            plt.grid(True, linestyle="--", alpha=0.7)
            
            nome_arquivo = f"{str(cat).replace(' ', '_')}.png" if cat else "grafico.png"
            nome_saida = os.path.join("resultados", nome_arquivo)
            plt.savefig(nome_saida)
            plt.close() 
            print(f"Gráfico salvo: {nome_saida}")

    except Exception as e:
        print(f"Erro ao processar gráfico: {e}")

if __name__ == "__main__":
    # 1. Carregar benchmark das IAs
    df_benchmark = pd.read_csv('resultados/resultados_benchmark.csv')

    # 2. Plotar os gráficos para todos os benchmarks presentes no arquivo
    # Incluindo 'Torre_de_Hanoi' e qualquer outro benchmark de forma uniforme
    if not df_benchmark.empty:
        gerar_graficos(
            dados=df_benchmark, 
            col_x='Input_N', 
            cols_y=['Tempo_Grok(s)', 'Tempo_Gemini(s)', 'Tempo_GPT(s)'],
            col_categoria='Benchmark',
            label_x='N (Input Size)' # Você pode ajustar o label se desejar algo mais genérico
        )