import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def gerar_grafico_e_tabela_fibonacci():
    arquivos_csv = [
        "fib_iter.csv",
        "fib_rec.csv",
        "fib_rec_buffer.csv",
        "fib_gemini.csv",
        "fib_gpt.csv",
        "fib_grok.csv"
    ]
    
    dfs = []
    for arquivo in arquivos_csv:
        if os.path.exists(arquivo) and os.path.getsize(arquivo) > 0:
            df = pd.read_csv(arquivo)
            if not df.empty:
                dfs.append(df)
                print(f"✓ Carregado: {arquivo} ({len(df)} medições)")
            else:
                print(f"Aviso: {arquivo} está vazio.")
        else:
            print(f"Aviso: {arquivo} não encontrado.")
    
    if not dfs:
        print("Nenhum dado válido.")
        return
    
    df_total = pd.concat(dfs, ignore_index=True)
    
    # Renomear para duracao
    if 'duracao_nanossegundos' in df_total.columns:
        df_total.rename(columns={'duracao_nanossegundos': 'duracao'}, inplace=True)
    
    os.makedirs("resultados", exist_ok=True)
    
    # Criar tabela pivô completa
    df_tabela = df_total.pivot(index='n', columns='metodo', values='duracao')
    
    # Renomear colunas para nomes mais bonitos
    df_tabela = df_tabela.rename(columns={
        'fib_iter_manual': 'Iterativo Manual',
        'fib_rec_manual': 'Recursivo Clássico',
        'fib_rec_buffer': 'Recursivo Buffer',
        'fib_gemini': 'Gemini',
        'fib_gpt': 'GPT',
        'fib_grok': 'Grok'
    })
    
    # Ordenar as colunas
    colunas_ordenadas = ['Iterativo Manual', 'Recursivo Buffer', 'Gemini', 'GPT', 'Grok', 'Recursivo Clássico']
    df_tabela = df_tabela[[col for col in colunas_ordenadas if col in df_tabela.columns]]
    
    # Ordenar pelo índice (n)
    df_tabela = df_tabela.sort_index()
    
    # Arredondar para 2 casas decimais
    df_tabela = df_tabela.round(2)
    
    print("\n=== Tabela COMPLETA de tempos médios (nanossegundos) ===")
    print(df_tabela.to_string())
    
    # Salvar tabela como CSV
    df_tabela.to_csv("resultados/tabela_completa.csv")
    print("\n✓ Tabela completa salva em resultados/tabela_completa.csv")
    
    # Criar imagem da tabela (apenas para n ≤ 40, que são os comparáveis)
    df_tabela_pequena = df_tabela[df_tabela.index <= 40]
    
    if not df_tabela_pequena.empty:
        fig_tab, ax_tab = plt.subplots(figsize=(16, 12))
        ax_tab.axis('off')
        
        # Preparar dados formatados
        dados_formatados = []
        for idx, row in df_tabela_pequena.iterrows():
            linha = [str(idx)]
            for val in row:
                if pd.notna(val):
                    if val < 1000:
                        linha.append(f"{val:.2f}")
                    elif val < 1000000:
                        linha.append(f"{val/1000:.2f}K")
                    else:
                        linha.append(f"{val/1000000:.2f}M")
                else:
                    linha.append("NaN")
            dados_formatados.append(linha)
        
        colunas = ['n'] + list(df_tabela_pequena.columns)
        tabela_plot = ax_tab.table(cellText=dados_formatados, colLabels=colunas,
                                   cellLoc='center', loc='center')
        tabela_plot.auto_set_font_size(False)
        tabela_plot.set_fontsize(10)
        tabela_plot.scale(1.5, 1.6)
        
        # Colorir apenas o cabeçalho (sem destacar nenhuma coluna específica)
        for (row_idx, col_idx), cell in tabela_plot.get_celld().items():
            if row_idx == 0:  # Cabeçalho
                cell.set_text_props(weight='bold', color='white')
                cell.set_facecolor('#1B365D')
            elif row_idx % 2 == 0:  # Linhas pares
                cell.set_facecolor('#F4F7FA')
            # Linhas ímpares ficam com a cor padrão (branca)
        
        plt.title('Fibonacci - Comparação de Tempos de Execução (nanossegundos)\n* K = mil, M = milhão', 
                  fontsize=14, weight='bold', pad=20)
        plt.savefig("resultados/tabela_completa_fibonacci.png", dpi=300, bbox_inches='tight')
        plt.close()
        print("✓ Imagem da tabela salva em resultados/tabela_completa_fibonacci.png")
    
    # Gráfico principal (todos métodos)
    plt.figure(figsize=(14, 8))
    
    cores = {
        'Iterativo Manual': '#1f77b4',
        'Recursivo Buffer': '#ff7f0e',
        'Gemini': '#2ca02c',
        'GPT': '#d62728',
        'Grok': '#9467bd',
        'Recursivo Clássico': '#e377c2'
    }
    
    marcadores = {
        'Iterativo Manual': 'o',
        'Recursivo Buffer': 's',
        'Gemini': '^',
        'GPT': 'D',
        'Grok': 'v',
        'Recursivo Clássico': 'x'
    }
    
    estilos = {
        'Iterativo Manual': '-',
        'Recursivo Buffer': '-',
        'Gemini': '-',
        'GPT': '-',
        'Grok': '-',
        'Recursivo Clássico': '--'
    }
    
    for coluna in df_tabela.columns:
        dados = df_tabela[coluna].dropna()
        if not dados.empty:
            plt.plot(dados.index, dados.values,
                    marker=marcadores[coluna], 
                    color=cores[coluna], 
                    linewidth=2, 
                    markersize=6,
                    linestyle=estilos[coluna],
                    label=coluna)
    
    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Tamanho da entrada (n) - escala log', fontsize=12)
    plt.ylabel('Tempo médio (nanossegundos) - escala log', fontsize=12)
    plt.title('Comparação de Desempenho - Fibonacci\n(Todos os Métodos)', fontsize=14, fontweight='bold')
    plt.legend(title='Método', loc='upper left', fontsize=10)
    plt.grid(True, which='both', linestyle='-', alpha=0.3)
    
    # Adicionar anotações
    plt.text(0.02, 0.98, ' Recursivo clássico: inviável para n > 40\n    Tempo exponencial O(2ⁿ)', 
             transform=plt.gca().transAxes, fontsize=9,
             verticalalignment='top', bbox=dict(boxstyle='round', facecolor='red', alpha=0.1))
    
    plt.tight_layout()
    plt.savefig("resultados/grafico_completo_fibonacci.png", dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico completo salvo em resultados/grafico_completo_fibonacci.png")
    
    # Gráfico apenas métodos eficientes (sem recursivo clássico)
    plt.figure(figsize=(12, 7))
    
    metodos_eficientes = [col for col in df_tabela.columns if col != 'Recursivo Clássico']
    for coluna in metodos_eficientes:
        dados = df_tabela[coluna].dropna()
        if not dados.empty:
            # Filtrar apenas n >= 1000 para melhor visualização
            dados_filtrados = dados[dados.index >= 1000]
            if not dados_filtrados.empty:
                plt.plot(dados_filtrados.index, dados_filtrados.values / 1e6,  # converter para ms
                        marker=marcadores[coluna], 
                        color=cores[coluna], 
                        linewidth=2, 
                        markersize=6,
                        label=coluna)
    
    plt.xlabel('Tamanho da entrada (n)', fontsize=12)
    plt.ylabel('Tempo médio (milissegundos)', fontsize=12)
    plt.title('Comparação de Desempenho - Métodos Eficientes O(n)', fontsize=14, fontweight='bold')
    plt.legend(title='Método', loc='upper left', fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig("resultados/grafico_eficientes.png", dpi=300, bbox_inches='tight')
    plt.close()
    print("✓ Gráfico de métodos eficientes salvo em resultados/grafico_eficientes.png")
    
    # Estatísticas
    print("\n" + "="*80)
    print("ESTATÍSTICAS DE DESEMPENHO")
    print("="*80)
    
    print("\n Recursivo Clássico (O(2ⁿ)) - n=40:")
    if 'Recursivo Clássico' in df_tabela.columns and 40 in df_tabela.index:
        tempo = df_tabela.loc[40, 'Recursivo Clássico']
        print(f"   Tempo: {tempo:.2f} ns = {tempo/1e9:.3f} segundos")
    
    print("\n⚡ Métodos O(n) para n=1,000,000:")
    for metodo in metodos_eficientes:
        if metodo in df_tabela.columns and 1000000 in df_tabela.index:
            tempo = df_tabela.loc[1000000, metodo]
            print(f"   {metodo}: {tempo:.2f} ns = {tempo/1e6:.2f} ms")
    
    print("\n Análise de Complexidade:")
    print("   • Recursivo Clássico: O(2ⁿ) - crescimento exponencial")
    print("   • Recursivo com Buffer: O(n) com overhead de recursão")
    print("   • Todos os iterativos: O(n) com O(1) espaço")
    if 100000 in df_tabela.index and 'Recursivo Buffer' in df_tabela.columns and 'Iterativo Manual' in df_tabela.columns:
        ratio = df_tabela.loc[100000, 'Recursivo Buffer'] / df_tabela.loc[100000, 'Iterativo Manual']
        print(f"   • Para n=100,000, Recursivo Buffer é ~{ratio:.1f}x mais lento que Iterativo Manual")
    
    print("\n Todos os gráficos e tabelas gerados com sucesso!")

if __name__ == "__main__":
    gerar_grafico_e_tabela_fibonacci()