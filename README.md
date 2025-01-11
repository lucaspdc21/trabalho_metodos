# Trabalho de Métodos Numéricos

## Objetivos

Este trabalho tem como objetivo implementar alguns métodos numéricos para encontrar raízes de equações e aplicá-los na resolução de um problema físico envolvendo deslocamento e oscilação. Especificamente, o foco é determinar o valor do deslocamento **d** que satisfaz a equação fornecida, utilizando três métodos numéricos distintos:

1. Método de Newton-Raphson.
2. Método de Newton Modificado.
3. Método da Secante Tradicional.

## Detalhes do problema

Função que rege o movimento:

$$
f(d) = a \cdot e^d - 4 \cdot d^2
$$

Onde:

- **a** é uma constante que representa a amplitude da oscilação no movimento,
- **d** é o deslocamento do movimento, que varia com o valor de **a**,
- **e** é a precisão.

O movimento amplifica-se quando o deslocamento **d** ultrapassa 0,7 cm, o que pode causar sérios danos. O objetivo é calcular o valor do deslocamento **d** que mantém o movimento seguro, usando os métodos numéricos e fazer uma análise sobre o efeito da alteração dos valores de **a**.


## Dados de Entrada

Os dados de entrada necessários para a execução do algoritmo são:

### Dados de Entrada  
- **n**: Número de valores de **a**.  
- **a**: Valores da constante **a** para cada **n**.  
- **$$\epsilon$$**: Precisão desejada para os métodos.  



## Dados de Saída

O programa gerará as seguintes saídas:

- **Quadro de Resposta**:
- **Quadro Comparativo**: 
- **Análise de Sensibilidade**: Análise sobre o efeito da variação de **a** nos resultados para cada método considerado.

## Implementação

## Exemplo de Saída

## Requisitos

