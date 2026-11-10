/******************************************************************************
Sistema de Registro e Gestão de Contas Bancárias – ETAPA 2
11/11/2026
Yan Moura Lima - 28195
*******************************************************************************/

#include <iostream>   // Entrada e saída (cin, cout, endl)
#include <string>     // Textos (string)
#include <iomanip>    // fixed e setprecision, para mostrar valores com 2 casas decimais
using namespace std;  // Evita escrever "std::" antes de cout, cin, string etc.

int main() {  // Função principal: onde o programa começa

	// DADOS DAS CONTAS
	const int MAX_CONTAS = 100;  // é previsto um limite máximo de 100 contas
	int numeroConta[MAX_CONTAS];     // Número de cada conta
	string nomeCliente[MAX_CONTAS];  // Nome de cada titular
	string cpf[MAX_CONTAS];          // CPF de cada titular
	int tipoConta[MAX_CONTAS];       // Tipo da conta: 1 = Corrente; 2 = Poupança
	double saldo[MAX_CONTAS];        // Saldo de cada conta
	bool contaAtiva[MAX_CONTAS];     // Situação da conta: true = ativa
	int quantidadeContas = 0;        // Quantidade de contas cadastradas

	// HISTÓRICO DE MOVIMENTAÇÕES (D = Depósito, + valor; S = Saque, - valor; T = Transferência, saída e entrada)
	const int MAX_MOVIMENTACOES = 500;            // Limite de movimentações
	int contaMovimentacao[MAX_MOVIMENTACOES];     // Conta dona de cada movimentação
	char tipoMovimentacao[MAX_MOVIMENTACOES];     // Tipo: 'D', 'S' ou 'T'
	double valorMovimentacao[MAX_MOVIMENTACOES];  // Valor de cada movimentação
	int quantidadeMovimentacoes = 0;              // Quantidade de movimentações registradas

	// VARIÁVEIS DE APOIO
	int opcao = 0;           // Opção escolhida no menu
	int indice = -1;         // Posição da conta encontrada (-1 = não encontrada)
	int indiceOrigem = -1;   // Posição da conta de origem na transferência
	int indiceDestino = -1;  // Posição da conta de destino na transferência
	int numeroDigitado = 0;  // Número de conta informado pelo usuário (ou da origem)
	int numeroDestino = 0;   // Número da conta de destino informado
	double valor = 0.0;      // Valor de depósito, saque ou transferência

	cout << fixed << setprecision(2);  // Valores decimais sempre com 2 casas (ex.: 50.00)

	do { // Laço do menu: repete até o usuário escolher sair
		cout << "\n===== BANCO PREMIUM =====\n";    // Título do menu
		cout << "1 - Cadastrar conta" << endl;       // Opção 1
		cout << "2 - Listar contas" << endl;         // Opção 2
		cout << "3 - Consultar conta" << endl;       // Opção 3
		cout << "4 - Depósito" << endl;              // Opção 4
		cout << "5 - Saque" << endl;                 // Opção 5
		cout << "6 - Transferência" << endl;         // Opção 6
		cout << "7 - Extrato" << endl;               // Opção 7
		cout << "0 - Sair" << endl;                  // Opção 0
		cout << "Opção: ";                           // Pede a escolha do usuário
		cin >> opcao;                                // Lê a opção
		cin.ignore(1000, '\n');                      // Descarta o Enter, para o getline do cadastro funcionar

		switch (opcao) { // Escolhe o que fazer conforme a opção

		case 1: // Cadastrar conta
			if (quantidadeContas >= MAX_CONTAS) {          // Se o limite de contas foi atingido
				cout << "Limite de contas atingido." << endl; // Avisa o usuário
				break;                                     // Volta ao menu
			}                                              // Fim do if

			cout << "Nome do cliente: ";                   // Pede o nome
			getline(cin, nomeCliente[quantidadeContas]);   // Lê o nome completo (com espaços)

			do { // Repete até o CPF ter 11 caracteres
				cout << "CPF (11 dígitos): ";              // Pede o CPF
				cin >> cpf[quantidadeContas];              // Lê o CPF
			} while (cpf[quantidadeContas].length() != 11); // Repete se não tiver 11 caracteres

			do { // Repete até o saldo inicial não ser negativo
				cout << "Saldo inicial: ";                 // Pede o saldo inicial
				cin >> saldo[quantidadeContas];            // Lê o saldo
			} while (saldo[quantidadeContas] < 0);         // Repete se for negativo

			do { // Repete até o tipo ser 1 ou 2
				cout << "Tipo de conta (1 = Corrente; 2 = Poupança): "; // Pede o tipo
				cin >> tipoConta[quantidadeContas];        // Lê o tipo
			} while (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2); // Repete se não for 1 nem 2

			numeroConta[quantidadeContas] = 1001 + quantidadeContas; // Gera o número da conta (1001, 1002, ...)
			contaAtiva[quantidadeContas] = true;           // A conta nasce ativa
			cout << "Conta registrada! Número: " << numeroConta[quantidadeContas] << endl; // Informa o número da conta
			quantidadeContas++;                            // Conta mais uma conta cadastrada
			break;                                         // Volta ao menu

		case 2: // Listar contas
			if (quantidadeContas == 0) cout << "Nenhuma conta cadastrada." << endl; // Avisa se não há contas
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre todas as contas cadastradas
				cout << "\nConta: " << numeroConta[i] << endl;  // Mostra o número
				cout << "Titular: " << nomeCliente[i] << endl;  // Mostra o nome
				cout << "CPF: " << cpf[i] << endl;              // Mostra o CPF
				cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupança") << endl; // Mostra o tipo
				cout << "Saldo: R$ " << saldo[i] << endl;       // Mostra o saldo
			}                                              // Fim do for
			break;                                         // Volta ao menu

		case 3: // Consultar conta pelo número
			cout << "Número da conta: ";                   // Pede o número da conta
			cin >> numeroDigitado;                         // Lê o número

			indice = -1;                                   // Começa como "não encontrada"
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre as contas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                              // Fim do for

			if (indice == -1) {                            // Se não encontrou
				cout << "Conta inexistente." << endl;      // Avisa o usuário
			} else {                                       // Se encontrou
				cout << "Titular: " << nomeCliente[indice] << endl;  // Mostra o nome
				cout << "CPF: " << cpf[indice] << endl;              // Mostra o CPF
				cout << "Tipo: " << (tipoConta[indice] == 1 ? "Corrente" : "Poupança") << endl; // Mostra o tipo
				cout << "Saldo: R$ " << saldo[indice] << endl;       // Mostra o saldo
			}                                              // Fim do if/else
			break;                                         // Volta ao menu

		case 4: // Depósito
			cout << "Número da conta: ";                   // Pede o número da conta
			cin >> numeroDigitado;                         // Lê o número
			cout << "Valor do depósito: R$ ";              // Pede o valor
			cin >> valor;                                  // Lê o valor

			indice = -1;                                   // Começa como "não encontrada"
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre as contas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                              // Fim do for

			if (indice == -1) {                            // Se a conta não existe
				cout << "Conta inexistente." << endl;      // Avisa o usuário
			} else if (valor <= 0) {                       // Se o valor não é positivo
				cout << "Valor inválido." << endl;         // Avisa o usuário
			} else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) { // Se o histórico está cheio
				cout << "Histórico cheio." << endl;        // Avisa o usuário
			} else {                                       // Tudo certo: faz o depósito
				saldo[indice] = saldo[indice] + valor;     // Soma o valor ao saldo
				contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice]; // Registra a conta da movimentação
				tipoMovimentacao[quantidadeMovimentacoes] = 'D';                  // Registra o tipo: depósito
				valorMovimentacao[quantidadeMovimentacoes] = valor;               // Registra o valor
				quantidadeMovimentacoes++;                 // Conta mais uma movimentação
				cout << "Depósito realizado. Saldo: R$ " << saldo[indice] << endl; // Confirma e mostra o saldo
			}                                              // Fim do if/else
			break;                                         // Volta ao menu

		case 5: // Saque
			cout << "Número da conta: ";                   // Pede o número da conta
			cin >> numeroDigitado;                         // Lê o número
			cout << "Valor do saque: R$ ";                 // Pede o valor
			cin >> valor;                                  // Lê o valor

			indice = -1;                                   // Começa como "não encontrada"
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre as contas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                              // Fim do for

			if (indice == -1) {                            // Se a conta não existe
				cout << "Conta inexistente." << endl;      // Avisa o usuário
			} else if (valor <= 0) {                       // Se o valor não é positivo
				cout << "Valor inválido." << endl;         // Avisa o usuário
			} else if (valor > saldo[indice]) {            // Se o saldo não é suficiente
				cout << "Saldo insuficiente." << endl;     // Avisa o usuário
			} else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) { // Se o histórico está cheio
				cout << "Histórico cheio." << endl;        // Avisa o usuário
			} else {                                       // Tudo certo: faz o saque
				saldo[indice] = saldo[indice] - valor;     // Subtrai o valor do saldo
				contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice]; // Registra a conta da movimentação
				tipoMovimentacao[quantidadeMovimentacoes] = 'S';                  // Registra o tipo: saque
				valorMovimentacao[quantidadeMovimentacoes] = valor;               // Registra o valor
				quantidadeMovimentacoes++;                 // Conta mais uma movimentação
				cout << "Saque realizado. Saldo: R$ " << saldo[indice] << endl;   // Confirma e mostra o saldo
			}                                              // Fim do if/else
			break;                                         // Volta ao menu

		case 6: // Transferência entre duas contas
			cout << "Número da conta de origem: ";         // Pede a conta de origem
			cin >> numeroDigitado;                         // Lê o número da origem
			cout << "Número da conta de destino: ";        // Pede a conta de destino
			cin >> numeroDestino;                          // Lê o número do destino
			cout << "Valor da transferência: R$ ";         // Pede o valor
			cin >> valor;                                  // Lê o valor

			indiceOrigem = -1;                             // Começa como "origem não encontrada"
			indiceDestino = -1;                            // Começa como "destino não encontrado"
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre as contas
				if (numeroConta[i] == numeroDigitado) indiceOrigem = i;  // Se bater com a origem, guarda a posição
				if (numeroConta[i] == numeroDestino) indiceDestino = i;  // Se bater com o destino, guarda a posição
			}                                              // Fim do for

			if (indiceOrigem == -1 || indiceDestino == -1) {  // Se alguma das contas não existe
				cout << "Conta de origem ou de destino inexistente." << endl; // Avisa o usuário
			} else if (indiceOrigem == indiceDestino) {    // Se as duas contas são a mesma
				cout << "Origem e destino devem ser diferentes." << endl;     // Avisa o usuário
			} else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) { // Se alguma conta está desativada
				cout << "Uma das contas está desativada." << endl;            // Avisa o usuário
			} else if (valor <= 0) {                       // Se o valor não é positivo
				cout << "Valor inválido." << endl;         // Avisa o usuário
			} else if (valor > saldo[indiceOrigem]) {      // Se a origem não tem saldo suficiente
				cout << "Saldo insuficiente." << endl;     // Avisa o usuário
			} else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) { // Se não há espaço para os 2 registros
				cout << "Histórico cheio." << endl;        // Avisa o usuário
			} else {                                       // Tudo certo: faz a transferência
				saldo[indiceOrigem] = saldo[indiceOrigem] - valor;    // Retira o valor da origem
				saldo[indiceDestino] = saldo[indiceDestino] + valor;  // Soma o valor no destino

				contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem]; // 1º registro: conta de origem
				tipoMovimentacao[quantidadeMovimentacoes] = 'T';                        // Tipo T: transferência (saída)
				valorMovimentacao[quantidadeMovimentacoes] = -valor;                    // Valor negativo: é uma saída (diminui o saldo)
				quantidadeMovimentacoes++;                 // Conta mais uma movimentação

				contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino]; // 2º registro: conta de destino
				tipoMovimentacao[quantidadeMovimentacoes] = 'T';                         // Tipo T: transferência (entrada)
				valorMovimentacao[quantidadeMovimentacoes] = valor;                     // Valor positivo: é uma entrada (aumenta o saldo)
				quantidadeMovimentacoes++;                 // Conta mais uma movimentação (total +2)

				cout << "Transferência realizada." << endl;   // Confirma a transferência
			}                                              // Fim do if/else
			break;                                         // Volta ao menu

		case 7: // Extrato de uma conta
			cout << "Número da conta: ";                   // Pede o número da conta
			cin >> numeroDigitado;                         // Lê o número

			indice = -1;                                   // Começa como "não encontrada"
			for (int i = 0; i < quantidadeContas; i++) {   // Percorre as contas
				if (numeroConta[i] == numeroDigitado) indice = i; // Se o número bater, guarda a posição
			}                                              // Fim do for

			if (indice == -1) {                            // Se a conta não existe
				cout << "Conta inexistente." << endl;      // Avisa o usuário
			} else {                                       // Se a conta existe
				cout << "\nExtrato da conta " << numeroConta[indice] << " - " << nomeCliente[indice] << endl; // Cabeçalho do extrato
				for (int i = 0; i < quantidadeMovimentacoes; i++) {   // Percorre todo o histórico
					if (contaMovimentacao[i] == numeroConta[indice]) { // Só as movimentações desta conta
						if (tipoMovimentacao[i] == 'D') {              // Se for depósito
							cout << "Deposito: R$ " << valorMovimentacao[i] << endl; // Mostra o depósito
						}                                              // Fim do if do depósito
						else if (tipoMovimentacao[i] == 'S') {         // Se for saque
							cout << "Saque: R$ " << valorMovimentacao[i] << endl;    // Mostra o saque
						}                                              // Fim do if do saque
						else if (tipoMovimentacao[i] == 'T') {         // Se for transferência
							if (valorMovimentacao[i] < 0) {            // Valor negativo: a conta enviou o dinheiro (saída)
								cout << "Transferencia (saida): - R$ " << -valorMovimentacao[i] << endl;  // Mostra a saída
							}                                          // Fim do if da saída
							else {                                     // Valor positivo: a conta recebeu o dinheiro (entrada)
								cout << "Transferencia (entrada): + R$ " << valorMovimentacao[i] << endl; // Mostra a entrada
							}                                          // Fim do else da entrada
						}                                              // Fim do if da transferência
					}                                                  // Fim do if da conta
				}                                                      // Fim do for do histórico
				cout << "Saldo atual: R$ " << saldo[indice] << endl;   // Mostra o saldo atual
			}                                              // Fim do if/else
			break;                                         // Volta ao menu

		case 0: // Sair
			cout << "Operação finalizada!" << endl;        // Mensagem de despedida
			break;                                         // Sai do switch (o laço termina em seguida)

		default: // Qualquer outro valor
			cout << "Opção inválida!" << endl;             // Avisa que a opção não existe
		}                                                  // Fim do switch

	} while (opcao != 0); // Repete o menu enquanto a opção não for 0 (Sair)

	return 0; // Fim do programa sem erros
}             // Fim da função main