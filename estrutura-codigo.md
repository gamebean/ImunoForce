#Estrutura geral do código

##ImunoForce
Neste arquivo está organizado o *loop* geral do jogo, assim como todas as variáveis necessárias a seu funcionamento. Também pode ser encontrado a declaração de todos os sprites assim como suas máscaras correspondentes. Além disso ele está dividido no loop em verificação de eventos e suas consequencias e, caso a lista esteja vazia, no desenho do menu e do jogo em si. O menu é dividido em SINGLE-PLAYER, MULTI-PLAYER, UPGRADES e QUIT:

* SINGLE-PLAYER: Onde são executadas as operações vitais para o desenrolar do jogo.
* MULTI-PLAYER: Este que por sua vez, é subdividido em HOST e JOIN:
 * HOST: Aqui acionado o gatilho de server, este é inicializado e o código é redirecionado para o case do SINGLE-PLAYER, onde o jogo roda normalmente mas com o acréscimo da escrita da estrutura de dados para o cliente e o recebimento de seus *inputs*
 * JOIN: É requisitado o ip de rede local do servidor em que o usuário quer se conectar e em seguida o jogo é configurado como cliente. Seus *inputs* são enviados ao servidor e ele recebe a estrutura de dados do mesmo, a desenhando na tela logo em seguida
* UPGRADES: Sistema de aprimoramentos de atributos do personagem principal que diversifica a jogabilidade. Pode ser adentrado enquanto se joga, pressinanco a tecla Esc. Os atributos são TRIGGER, FORCE e BULLET:
 * TRIGGER: Seu incremento resulta no aumento da frequência com que são disparados os projéteis, diminuindo o valor da variável de delay
 * FORCE: Aumenta o dano causado pro cada projétil
 * BULLET: Seu aprimoramento resulta na adição de projéteis lançados por disparo
* QUIT: Usado para sair do jogo

##AllegroDef

Neste se localizam as definições necessárias as bibliotecas e também suas inicializações, com as devidas mensagens de erro caso necessário seja.

##Multiplayer

Nesta seção podem ser encontradas as funções e definições necessárias para a troca de pacotes via protocolo UDP entre *server* e *client*, bem como as devidas bibliotecas.

##ImunoEngine

Como o nome sugere, o ImunoEngine terá todas as funções principais de renderização, movimentação, colisão além de funções de suporte para a criação de objetos.

## struct Object
Object é a estrutura que define quase tudo que existe no jogo, de personagens a projéteis e até o background são Objects. Esta estrutura possui todos os atributos necessários para movimentação, animação, desenho e colisão (os últimos 3 tratados por índices referentes a uma array), além de ser organizada como uma lista duplamente encadeada, onde cada object possui um atributo que é o endereço para a estrutura seguinte (que foi declarada após ele) e a anterior (que foi declarada antes). Por este motivo se faz necessário a existencia de um *header*, que é um Object que não possui nenhuma utilidade aparente ao usuário, usado apenas como referência. Este método de duplo encadeamento das estruturas se dá muito útil uma vez que não é necessário o armazenamento de uma variável para cada Object, visto que é possível iterar entre todos eles através de seus atributos de endereços, e distinguilos através de seus atributos de tipo.
