### Universidade Federal de Alagoas
## Instituto de Computação

# Visão Computacional
### Professor: Thales Vieira

## 1ª lista de exercícios

### 1. Elabore e implemente um algoritmo para eliminar, a partir de duas imagens capturadas de um mesmo ponto de vista, o background (ou imagem de fundo). Aplique nas imagens abaixo.
![Primeira imagem](primeira imagem) ![Segunda imagem](segunda imagem)

### 2. Sugira, implemente e aplique filtros na imagem resultante da primeira questão com o objetivo de destacar apenas o objeto do foreground.

### 3. Implemente um aplicativo que receba o tamanho n de um filtro espacial com dimensões n x n, e a matriz com os pesos do filtro, e aplique o filtro numa imagem, gerando e salvando a imagem resultante no disco.

### 4. Implemente dois tipos de filtro para remoção de ruídos e encontre exemplos onde cada um deles funciona melhor.

### 5. Pesquise um filtro passa-alta e aplique-o em 3 imagens distintas, variando o valor de n em 3 unidades em cada imagem. O que acontece quando n cresce?

### 6. Pesquise um filtro passa-baixa e aplique-o em 3 imagens distintas, variando o valor de n em 3 unidades em cada imagem. O que acontece quando n cresce?

### 7. Pesquise um filtro que extraia arestas e aplique-o em 3 imagens distintas, variando o valor de n em 3 unidades em cada imagem. O que acontece quando n cresce?

### 8. Uma imagem híbrida é a soma de uma versão filtrada com filtro passa-baixa de uma imagem com uma versão filtrada com filtro passa-alta de uma segunda imagem. Implemente um algoritmo para calcular imagem híbrida que leve em conta dois parâmetros chamados frequÊncias de corte que determina quanto de alta frequência e quanto de baixa frequência filtrar nas imagens. Estes parâmetros podem ser associados a cada n. Aplique o algoritmo implementado em 3 imagens, com 3 frequências de corte distintas.

### 9. Um filtro passa-baixa bastante conhecido é o filtro Gaussiano. Através de uma máscara determinada por um desvio padrão <img src="https://render.githubusercontent.com/render/math?math=\sigma">, é possível fazer o que chamamos de suavização gaussiana de uma imagem. Considere o filtro <img src="https://render.githubusercontent.com/render/math?math=5x5"> de desvio padrão unitátio abaixo:

1/273  4/273  7/273  4/273 1/273

4/273 16/273 26/273 16/273 4/273

7/273 26/273 41/273 26/273 7/273

4/273 16/273 26/273 16/273 4/273

1/273  4/273  7/273  4/273 1/273

Crie uma imagem I de dimesões 100 x 100 que contém um único valor não nulo localizado no centro da imagem. Utilizando o filtro gaussiano acima, calcule g * I, I * g, g°I e I°g.

### 10. Implemente uma função que reduza um ou aumente a resolução da imagem por fatores (sx, sy). Aplique em três imagens distintas.
<img src="https://github.com/jhonnye0/ECOM100_Listas/blob/main/lista1/imagens/b64yPN6Ibi.gif" width="400px"></img>

### 11. Escolha uma imagem interessante e gere uma pirâmide aplicando sucessivamente downsampling 3 vezes com fator 1/2. Faça o mesmo com uma pirâmide gaussiana e compare os resultados. Mostre os resultados de cada pirâmide em uma única imagem lado a lado, como nos slides da aula.

### 12. Usando as funções que você implementou, crie funções que aplique filtros para calcular as imagens representando $del f/del x$, $del f/del y$ e |$grad f$|. Implemente também as mesmas usando o operador de Sobel. Aplique-as diretamente em algumas imagens de sua escolha, e compare o efeito do ruído.

### 13. DESAFIO: Implemente a supressão não máxima e aplique em algumas imagens de intensidade de gradiente.
