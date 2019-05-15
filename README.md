# Transacoes-Bancarias
#### Introdução:
- O objetivo desse projeto consiste em processar transações bancárias de correntistas, dentro de uma agência, utilizando estruturas de dados.  
#### Considerações:  
- Deverá existir um número de senha para cada cliente a ser atendido dentro da agência. Para isto, considere que o último número de senha fornecido, no início do dia, tem valor zeros;  
- Inicialização e fechamento de caixa são eventos únicos e obrigatórios durante um dia de trabalho. Opcionalmente, mais de uma reposição de valores em um  caixa, pode ocorrer.  

#### Lista de Agências Bancárias:
- Resolução utilizando Estruturas de Dados com Implementação em linguagem C++ 
-	Serão informados registros das agências contendo número (4 dígitos), nome 
(15 caracteres) e endereço (30 caracteres);  
#### Lista de Contas Correntes: 
-	Serão informados registros de contas correntes contendo número (5 dígitos), dígito verificador da conta (1 dígito), CPF do correntista (11 dígitos), nome do correntista (25 caracteres), saldo atual da conta (10 dígitos com duas decimais), número da agência que tem conta (4 dígitos); o Após digitação do dígito verificador, validá-lo através do Módulo 11 (pesquisar sobre o módulo) para ver se o mesmo está correto.  
#### Abertura – Início do caixa: 
-	Registrar-se-á, em uma Lista de Caixas, o número do caixa (2 dígitos), matrícula do operador (com 5 dígitos) e nome do operador (25 caracteres), data e hora de abertura, saldo inicial (10 dígitos com duas decimais), valor de reposição no caixa (10 dígitos com duas decimais), hora de fechamento e saldo atual do caixa (10 dígitos com duas decimais);  
- Data e hora de abertura serão as do Sistema Operacional – S.O;  
- Valor de reposição do caixa e saldo final serão zerados;  
- Demais dados serão informados, exceto hora de fechamento.  
#### Fila Circular de Senhas: 
- Solicitação de atendimento através de uma Fila Circular de Senhas:  
-	Serão registrados número de senha (3 dígitos – último número fornecido + 1), data e hora de obtenção (oriundas do S.O), status (pode ser Emitida, Atendida ou Cancelada);  
#### Atendimento ao cliente: 
-	Serão consideradas três tipos de transações bancárias para atendimento ao cliente, a saber: Saque, Depósito e Transferência de Valores. Para isto, estas transações devem ser registradas numa Lista de Transações Bancárias com a seguinte estrutura:  
-	Data e hora obtidas do S.O; o Número do caixa; o Número de senha;  
-	Transação bancária (2 caracteres: SQ – saque, DP – depósito e TV – transferência de valor);  
-	Valor da transação (10 dígitos com duas decimais);  
-	Número da agência de origem; o Número da conta corrente de origem; o Saldo da conta de origem (saldo anterior); o Número da agência de destino; o Número da conta corrente de destino; o Saldo da conta de destino (saldo anterior);  
-	Quando a transação for transferência de valores, os três últimos campos de dados acima não serão informados;  
-	Atualizar um quantitativo de senhas atendidas, bem como o saldo atual da (s) conta (s) corrente (s) e o saldo atual do caixa, além da Fila Circular de Senhas.  
#### Fechamento do caixa: 
-	Solicitar o número do caixa e: 
-	Informar matrícula e nome do operador, data e hora de abertura do caixa, além do saldo inicial;  
-	Caso tenha havido reposições de dinheiro no caixa, informar o somatório de valor correspondente;  
-	Exibir hora de fechamento e saldo atual do caixa, além do número de atendimentos de senhas.  
#### Consultas e Atualizações Avulsas:  
-	Reposição de caixa, fornecendo o número do caixa e o valor a ser adicionado ao campo valor de reposição do caixa;  
-	Cancelamento de senha, eliminando a senha que está na frente da Fila Circular de Senhas;  
-	Fornecido o número de uma agência, exibir a relação de correntistas, com respectivo número de conta) em ordem alfabética;  
-	Consulta saldo, fornecendo números da agência, conta corrente e digito verificador do correntista; e sendo exibidos o nome da agência, CPF e nome do correntista, além do saldo atual da conta;  
-	Extrato de conta corrente, fornecendo números da agência, conta corrente e digito verificador do correntista, além de um intervalo de datas (início e fim). Selecionar, na Lista de Transações Bancárias, os nós onde os dados fornecidos sejam iguais aos das contas correntes de origem ou de destino. Mostrar o histórico de transações, dispostos na seguinte ordem:  
--	Identificação do correntista (número da agência, número da conta corrente e dígito, nome do correntista e saldo inicial – obtido do primeiro nó de lista recuperado com base no intervalo de datas fornecidas);  
--	Linhas de movimentações: exibir data e hora, o valor da transação, e um campo de sinal. Quando a transação for saque o campo sinal será “-“ e “ “ se a transação for depósito. Caso a transação seja transferência de valores e a conta corrente selecionada for de origem, então o campo sinal será “-“. Mas, se a transação for transferência de valores e a conta corrente selecionada for de destino, então o campo sinal será “ “;  
--	Uma linha contendo o saldo atual, resultante da informação no Saldo da conta de origem ou de destino (saldo anterior) do último nó selecionado, adicionado (ou subtraído) o valor da transação deste último nó.  
