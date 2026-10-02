import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np  

def gerar_grafico_e_tabela_mediana():
    arquivos_csv = [
        "iterativo_original.csv",
        "recursivo_original.csv",
        "polinomio_gemini.csv",
        "polinomio_gpt.csv",
        "polinomio_grok.csv"
    ]
    
    dfs = []
    
    for arquivo in arquivos_csv:
        if os.path.exists(arquivo):
            if os.path.getsize(arquivo) == 0:
                print(f"Aviso: O arquivo '{arquivo}' está vazio. Ignorado.")
                continue
            try:
                df = pd.read_csv(arquivo)
                if df.empty:
                    continue
                dfs.append(df)
            except Exception as e:
                print(f"Erro ao ler '{arquivo}': {e}")
                
    if not dfs:
        print("\nErro: Nenhum dado válido foi encontrado nos arquivos CSV.")
        return
        
    df_total = pd.concat(dfs, ignore_index=True)
    os.makedirs("resultados", exist_ok=True)
    
    
    df_tabela = df_total.pivot(index='n', columns='metodo', values='mediana_microssegundos')
    

   
    fig_tab, ax_tab = plt.subplots(figsize=(10, 8))
    ax_tab.axis('off')  
    
    dados_formatados = []
    for idx, row in df_tabela.iterrows():
        linha = [str(idx)] + [f"{int(val):,}" if not pd.isna(val) else "N/A" for val in row]
        dados_formatados.append(linha)
        
    colunas = ['Tamanho (n)'] + list(df_tabela.columns)
    
    tabela_plot = ax_tab.table(
        cellText=dados_formatados,
        colLabels=colunas,
        cellLoc='center',
        loc='center'
    )
    
    tabela_plot.auto_set_font_size(False)
    tabela_plot.set_fontsize(10)
    tabela_plot.scale(1.2, 1.4)  
    
    for (row_idx, col_idx), cell in tabela_plot.get_celld().items():
        if row_idx == 0:
            cell.set_text_props(weight='bold', color='white')
            cell.set_facecolor('#1B365D') 
        else:
            if row_idx % 2 == 0:
                cell.set_facecolor('#F4F7FA')  
                
    plt.title('Tabela Consolidada de Medianas (microssegundos)', fontsize=14, weight='bold', color='#1B365D', pad=20)
    caminho_tabela_png = os.path.join("resultados", "tabela_resultados_mediana.png")
    plt.savefig(caminho_tabela_png, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Sucesso! Tabela de medianas salva em: '{caminho_tabela_png}'")


   
    plt.figure(figsize=(13, 8))
    
    marcadores = ['o', 's', '^', 'D', 'v']
    metodos_unicos = df_total['metodo'].unique()
    
    for i, metodo in enumerate(metodos_unicos):
        dados_metodo = df_total[df_total['metodo'] == metodo].sort_values(by='n')
        
        x = dados_metodo['n'].values
        y = dados_metodo['mediana_microssegundos'].values
        
        
        linha_exp = plt.plot(
            x, y, 
            marker=marcadores[i % len(marcadores)], 
            linewidth=1.5, 
            linestyle='-',
            alpha=0.8,
            label=f"{metodo} (Experimental)"
        )
        
       
        cor_metodo = linha_exp[0].get_color()
        
        
        m, b = np.polyfit(x, y, 1)
        y_ajustado = m * x + b
        
        
        plt.plot(
            x, y_ajustado, 
            linestyle='--', 
            linewidth=1.5, 
            color=cor_metodo,
            alpha=0.6,
            label=f"Reta O(n) Encaixada ({metodo})"
        )
    
    plt.title('Benchmark: Avaliação Polinomial com Retas de Ajuste O(n)', fontsize=16, weight='bold')
    plt.xlabel('Tamanho da Entrada (n)', fontsize=12)
    plt.ylabel('Mediana do Tempo de Execução (microssegundos)', fontsize=12)
    
    # Posiciona a legenda fora ou ajustada de forma limpa para não cobrir o gráfico
    plt.legend(title='Métodos e Linhas de Tendência', fontsize=9, loc='upper left', bbox_to_anchor=(1.02, 1))
    plt.grid(True, which="both", ls="-", alpha=0.4)
    
    nome_saida = os.path.join("resultados", "grafico_polinomial_mediana.png")
    plt.savefig(nome_saida, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Sucesso! Gráfico com as retas encaixadas salvo em: '{nome_saida}'")

if __name__ == "__main__":
    gerar_grafico_e_tabela_mediana()