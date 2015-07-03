<<<<<<< HEAD
#Estrutura geral do código

##ImunoForce.c
Nesse arquivo está organizado o *loop* geral do jogo, assim como todas as variáveis necessárias a seu funcionamento. Também pode ser encontrado a declaração de todos os sprites assim como suas máscaras correspondentes. Além disso ele está dividido no loop em verificação de eventos e suas consequencias e, caso a lista esteja vazia, no desenho do menu e do jogo em si. O menu é dividido em SINGLE-PLAYER, MULTI-PLAYER, UPGRADES e QUIT

* SINGLE-PLAYER: Onde são executadas as operações vitais para o desenrolar do jogo.
* MULTI-PLAYER: Este que por sua vez, é subdividido em HOST e JOIN:
 * HOST: Aqui acionado o gatilho de server, este é inicializado e o código é redirecionado para o case do SINGLE-PLAYER, onde o jogo roda normalmente mas com o acréscimo da escrita da estrutura de dados para o cliente e o recebimento de seus *inputs*
 * JOIN: É requisitado o ip de rede local do servidor em que o usuário que se conectar e em seguida o jogo é configurado como cliente. Seus *inputs* são enviados ao servidor e ele recebe a estrutura de dados do mesmo, a desenhando na tela logo em seguida
* UPGRADES: Sistema de aprimoramentos de atributos do personagem principal que diversifica a jogabilidade. Pode ser adentrado enquanto se joga, pressinanco a tecla Esc. Os atributos são TRIGGER, FORCE e BULLET:
 * TRIGGER: Seu incremento resulta no aumento da frequência com que são disparados os projéteis, diminuindo o valor da variável de delay
 * FORCE: Aumenta o dano causado pro cada projétil
 * BULLET: Seu aprimoramento resulta na adição de projéteis lançados por disparo
* QUIT: Usado para sair do jogo

##AllegroDef

##ImunoEngine

##Multiplayer
=======
# ImunoEngine

Como o nome sugere, o ImunoEngine terá todas as funções principais de renderização, movimentação, colisão além de funções de suporte para a criação de objetos.

## Object
Tudo no ImunoForce é um Object, ele carrega todas 
 

>>>>>>> origin/master
