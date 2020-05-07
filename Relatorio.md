#Relatorio EP1
##Alexandre Muller Jones - nUSP 8038149

##Introdução
A realização deste exercício me permitiu verificar muito bem as relativas vantagens e desvantagens de cada implementação da tabela de simbolos. Neste relatório, falarei sobre cada uma delas, discutirei decisões que tomei em cada e conclusões que pude tirar.

A estrutura geral do programa foi aproveitada do arquivo de testes unitarios que nos foi passado pelos monitores. Editei o arquivo em diversos pontos, principalmente na mudança do código de uma implementação por template para tipos já definidos (utilizei o tipo dado String para a chave e Integer para o valor), porém a estrutura geral permaneceu e foi muito útil tanto para o desenvolvimento como para os testes e depuração. Outra mudança importante com relação ao que nos foi passado originalmente foi a escolha de separar cada implementação em seu próprio arquivo de header. Isso permitiu maior clareza durante o desenvolvimento e facilitou a implementação, dado que podia incluir uma implementação por vez no arquivo principal e evitar erros relacionados às outras.

O corpus que selecionei como base do desenvolvimento foi uma versão em .txt baixada do Projeto Gutemberg do livro Dom Casmurro, de Machado de Assis. Inicialemente, recortei apenas um capítulo do livro e utilizei este arquivo menor para as primeiras depurações, devido a ser mais fácil de lidar e mais rapido para ser lido por implementações mais lentas. Todos os arquivos foram, entretanto, testados com o arquivo original, fornecido junto ao meu código.

##Conteudo
Este arquivo compactado contém os headers com cada implementação, este relatório, o arquivo domcasmurro.txt, corpus dos testes para referência, o arquivo util.hpp modificado e um script simples run.sh, que compila e linka os arquivos gerando um arquivo saida a.out.

###util.hpp
Este arquivo sofre algumas mudanças. Implementei diferentes estruturas de dados para cada implementação, como uma estrutura para cada nó de uma lista ligada, cada nó de uma arvore binaria etc. Entretanto, como algumas destas foram utilizadas para mais de uma implementação (como o nó de uma lista ligada que foi utilizada em ambas as listas assim como na hashtable), escolhi implementar essas estruturas no util de modo que ficassem disponiveis para todos os arquivos mais facilmente e, assim, pudesse diminuir a duplicação do código. Nenhuma outra mudança foi feita neste arquivo além da adição dessas estruturas.

###Semelhanças entre as implementações
Uma ultima nota relevante antes de discutir cada implementação em especifico é a similaridade entre elas. Cada versão tem suas particularidades em como é feita uma inserção, remoção ou outras operações, porém uma parte em especifico foi compartilhada por todas de forma quase que identica. Com a exceção de inicializar variaveis locais que diferem entre as implementações, o código que monta a tabela de simbolos é o mesmo entre todas elas. Isso se deve ao fato de que esse código usa métodos da própria classe de forma genérica, e a interface de todas é a mesma, o que permitiu que esse código fosse reutilizado em todas as implementações e facilitou bastante o desenvolvimento, dado que não precisava me preocupar com ele e podia me concentrar apenas em implementar os métodos em si.

Outra importante semelhança é que, como os tipos que utilizei foram String e Integer conforme definidos no util, tratam-se de ponteiros, então sempre que um item é inserido ou removido, é necessário alocar/liberar a memória correspondente. Não houve nenhum problema com essa implementação, porém ela 
é comum à todas as implementações e cabe descrever aqui.

Este algoritmo é simples: ele itera por cada palavra do arquivo de entrada e a procura na tabela utilizando o método devolve(). Caso a encontre, incrementa seu valor em 1 e, caso contrário, insere esta nova palavra na tabela utilizando o insere().

Também mantive constante entre as varias implementações o espaço que era alocado para o campo chave. Durante meus testes experimentei diversos tamanhos e escolhi um tamanho máximo de 40 caracteres, com 5 bytes extras para acomodar o terminador de uma string. Esse valor foi escolhido depois de encontrar problemas com multiplos valores menores, como 10 ou 20, possivelmente devido ao corpus que selecionei.

A seguir, discutirei cada implementação, agrupando conforme adequado.

###vetorDes

Nesta implementação, utilizei um struct que chamei de Valor, na qual basicamente guardo um par chave-valor. Com isso, pude utilizar também a biblioteca <vector>, criando um vetor de objetos do tipo Valor como membro da classe. O construtor inicializa esse vetor e todas as operações são realizadas sobre ele.

A inserção é feita sempre ao final do vetor dado que não é feita nenhuma ordenação. Isso também significa que buscas e remoções de chaves no vetor são feitas linearmente, em O(N), assim como o calculo do rank, já que é necessário olhar para todos os membros do vetor para obter este valor. A falta de ordenação também impacta a eficiencia do método seleciona(), que tem comportamento O(n²) no pior caso dada a necessidade de calcular o rank de cada membro e conferir se é o desejado, um a um.

O destrutor do objeto itera pelo vetor liberando a memória de cada chave e cada valor nele. A liberação do vetor em si não é feita explicitamente já que é feita automaticamente.

###vetorOrd

Superficialmente, essa implementação é muito similar à anterior.

Para implementar a inserção, ponderei 2 possibilidades: realizar a inserção já na posição correta ou inserir no fim do vetor e então ordená-lo. Estudando ambas as possibilidades e a documentação do vector, cheguei à conclusão que realizar a inserção já na posição correta traria grandes benefícios em termos de eficiencia dado que buscar a posição correta poderia ser feito em O(logN), utilizando uma busca binária, ao invés de inserir em tempo constante e ordenar em O(N logN). Para isso, criei uma função bool comparaValores(), e utilizei a função upper_bound() com meu comparador pra realizar essa busca.

Para ilustrar o quanto essa escolha melhorou a eficiencia do programa, implementei também a outra versão possivel e testei ambas para o mesmo corpo de entrada. O método de inserção no final e ordenação cria a ST em, em média, 151 segundos. Já o método escolhido, de inserção já na posição, conclui em 0.157 segundos, uma melhora de aproximadamente 1,000 vezes.

Tendo um vetor ordenado, pude criar outra função auxiliar find() que realiza uma busca binária de forma recursiva. Como essa busca é O(log N), tanto a busca de um valor como a remoção e a função rank() tem todas O(log N), uma grande melhora com relação ao vetor desordenado. A maior diferença, entretanto, vem na função seleciona(), que tinha comportamento O(n²) na versao desordenada e, aqui, tem comportamento constante, O(1).

O destrutor é igual ao do vetor anterior.

###listaDes

Aqui, criei um novo struct NoLista, que guarda um par chave-valor e tem um ponteiro para o próximo. A lista foi implementada sem cabeça e, logo, a classe tem como membro apenas um ponteiro que inicia como nullptr e é atualizado com cada inserção. A inserção tem O(1) ja que um novo item é sempre inserido no começo da lista, e as operações de busca, remoção, rank e seleção tem mesma complexidade de que suas analogas do vetor desordenado já que a lista desordenada também não tem nenhum recurso para melhorar as operações.

Uma vantagem dessa implementação, entretanto, é que a iteração pela lista é mais fácilmente implementada por não ser necessário criar for loops ou usar indices, podemos apenas iterar item a item. O ponto negativo disso é que, mesmo na versão ordenada da lista, como veremos a seguir, algumas operações não tem ganho de eficiencia.

O destrutor da lista remove o primeiro item dela, o libera e repete o processo até a lista estar vazia.

###listaOrd

Esta implementação utiliza a mesma estrutura de dados da anterior. Comparar esta versão com a anterior é analogo à comparar o vetor ordenado com o desordenado, dado que muitas das mudanças feitas quando começamos a tratar de uma lista ordenada são análogas à tratar de um vetor ordenado. Entretanto, aqui temos um ganho menor em eficiencia porque, diferente de um vetor ordenado, não temos como acessar diretamente itens no meio da lista, então não é possível realizar uma busca binária. Assim, a eficiencia de buscas na lista é a mesma seja esta ordenada ou não.

Temos aqui um fenomeno interessante. Como as inserções na lista ordenada são mais complexas que a desordenada, tendo ordem O(N) ao invés de ordem constante, construção dessa lista é mais demorada, demorando mais que o dobro no pior caso.

As mudanças positivas em eficiencia vem na operação de seleção, que passa de O(n²) da desordenada para O(k), já que sabemos que o item de rank k será o k-ésimo item da lista mas precisamos passar pelos k-1 itens anteriores para acessá-lo.

O destrutor é semelhante ao anterior.

###arvoreBin

Esta implementação utiliza um novo struct, NoABB, que guarda um par de chave-valor assim como 2 ponteiros, esq e dir, para seus 2 filhos.

A construção dessa arvore pode ser ineficiente para entradas mal comportadas, como entradas já ordenadas que tornarão a estrutura basicamente uma lista ligada. Entretando, num caso geral como este, a construção é bastante eficiente, com ordem O(logN), em média, para a inserção.

A implementação desta estrutura foi bastante direta, visto como arvores binárias são bons alvos para algoritmos recursivos. Sabendo disso, implementei 4 funções auxiliares. A função liberaNo() libera a memória de um nó específico, enquanto a libera() itera recursivamente por uma árvore a partir da sua raiz liberando todos os seus nós (utilizando a liberaNo). A função coloca() recebe um ponteiro para um novo nó a ser inserido e, recursivamente, procura seu lugar na árvore. Esta função é usada apenas no método insere(), porém foi separada para que pudesse ter outra interface e, assim, pudesse ser recursiva. A ultima função, também recursiva, é a contaFilhos(), que conta o número de nós que existem abaixo de um nó qualquer. Esta função é utilizada no calculo do rank(), de modo a contar quantos itens tem chave menor que a pedida, e foi separada desta função pelo mesmo motivo das anteriores - possibilitar uma interface que se prestasse a recursão.

A maioria das operações nesta estrutura são eficientes, dado a natureza bínaria da arvore que possibilita percorre-la de maneira bastante eficiente (novamente, em casos gerais e relativamente bem comportados). A busca, inserção e remoção tem todas O(logN). Já a rank() tem O(N) dado que precisa, possivelmente, visitar todos os outros nós da árvore, e a seleciona, O(N logN), já que realiza uma busca binária calculando o rank() a cada passo.
