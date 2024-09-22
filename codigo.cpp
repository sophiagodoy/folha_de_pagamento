funcionarios = {}

def calcular_salario_fixo_vendedor(volume_vendas):
    return 1500 + volume_vendas * 0.09

def calcular_desconto_por_faltas(salario_fixo, num_faltas):
    salario_diario = salario_fixo / 30
    desconto = salario_diario * num_faltas
    return salario_fixo - desconto

def calcular_salario_liquido(salario_com_desconto):
    if salario_com_desconto <= 2259.2:
        imposto = 0
    elif salario_com_desconto <= 2828.65:
        imposto = 0.075
    elif salario_com_desconto <= 3751.05:
        imposto = 0.15
    elif salario_com_desconto <= 4664.68:
        imposto = 0.225
    else:
        imposto = 0.275
    return salario_com_desconto - (salario_com_desconto * imposto)

def inserir_funcionario():
    matricula_funcionario = input("\nMatrícula: ")
    nome_funcionario = input("Nome: ")
    codigo_funcionario = int(input("Código (101 - Vendedor, 102 - Administrativo): "))
    num_faltas = int(input("Número de faltas: "))
    
    if codigo_funcionario == 101:
        volume_vendas = int(input("Volume de vendas: "))
        salario_fixo = calcular_salario_fixo_vendedor(volume_vendas)
    else:
        volume_vendas = 0
        salario_fixo = float(input("Salário fixo: "))
        while salario_fixo < 2150 or salario_fixo > 6950:
            salario_fixo = float(input("O salário está fora do intervalo válido. Digite Novamente: "))
    
    salario_com_desconto = calcular_desconto_por_faltas(salario_fixo, num_faltas)
    salario_liquido = calcular_salario_liquido(salario_com_desconto)
    funcionarios[matricula_funcionario] = [nome_funcionario, codigo_funcionario, num_faltas, volume_vendas, salario_fixo, salario_liquido]
    print("Funcionário inserido com sucesso!")

def remover_funcionario(matricula):
    if matricula in funcionarios:
        del funcionarios[matricula]
        print(f"Funcionário removido com sucesso!")
    else:
        print(f"Funcionário não encontrado.")

def calcular_folha_pagamento(matricula):
    if matricula in funcionarios:
        nome_funcionario = funcionarios[matricula][0]
        codigo_funcionario = funcionarios[matricula][1]
        num_faltas = funcionarios[matricula][2]
        volume_vendas = funcionarios[matricula][3]
        salario_fixo = funcionarios[matricula][4]
        salario_com_desconto = calcular_desconto_por_faltas(salario_fixo, num_faltas)
        imposto = calcular_imposto(salario_com_desconto)
        salario_liquido = calcular_salario_liquido(salario_com_desconto)
        
        print("\nInformações do Funcionário:")
        print(f"Matrícula: {matricula}")
        print(f"Nome: {nome_funcionario}")
        print(f"Código do funcionário: {codigo_funcionario}")
        print(f"Número de faltas: {num_faltas}")
        print(f"Volume de vendas: {volume_vendas}")
        print(f"Salário Fixo: R$ {salario_fixo:.2f}")
        print(f"Salário Líquido: R$ {salario_liquido:.2f}")
        print(f"Percentual de Imposto: {imposto * 100:.2f}%")
    else:
        print(f"Funcionário não encontrado.")

def calcular_imposto(salario_com_desconto):
    if salario_com_desconto <= 2259.2:
        return 0
    elif salario_com_desconto <= 2828.65:
        return 0.075
    elif salario_com_desconto <= 3751.05:
        return 0.15
    elif salario_com_desconto <= 4664.68:
        return 0.225
    else:
        return 0.275

def gerar_relatorio():
    matriculas = list(funcionarios.keys())
    print("\nMatrícula/Nome/Código/Salário Bruto/Salário Líquido")
    
    for matricula in matriculas:
        nome_funcionario = funcionarios[matricula][0]
        codigo_funcionario = funcionarios[matricula][1]
        salario_fixo = funcionarios[matricula][4]
        salario_liquido = funcionarios[matricula][5]
        print(f"{matricula} {nome_funcionario} {codigo_funcionario} {salario_fixo:.2f} {salario_liquido:.2f}")

def funcionario_maior_salario_liquido():
    maior_salario_liquido = 0
    funcionario_destaque = None
    
    for matricula, dados in funcionarios.items():
        salario_liquido = dados[5]
        if salario_liquido > maior_salario_liquido:
            maior_salario_liquido = salario_liquido
            funcionario_destaque = (matricula, dados)
    
    if funcionario_destaque:
        matricula, dados = funcionario_destaque
        salario_com_desconto = calcular_desconto_por_faltas(dados[4], dados[2])
        imposto = calcular_imposto(salario_com_desconto)
        nome_funcionario = dados[0]
        codigo_funcionario = dados[1]
        salario_fixo = dados[4]
        
        print("\nInformações do Funcionário com Maior Salário Líquido:")
        print(f"Matrícula: {matricula}")
        print(f"Nome: {nome_funcionario}")
        print(f"Código do funcionário: {codigo_funcionario}")
        print(f"Salário Bruto: R$ {salario_fixo:.2f}")
        print(f"Salário Líquido: R$ {maior_salario_liquido:.2f}")
        print(f"Percentual de Imposto: {imposto * 100:.2f}%")
    else:
        print("Não há funcionários cadastrados.")

def funcionario_maior_num_faltas():
    maior_num_faltas = 0
    funcionario_destaque = None
    
    for matricula, dados in funcionarios.items():
        num_faltas = dados[2]
        if num_faltas > maior_num_faltas:
            maior_num_faltas = num_faltas
            funcionario_destaque = (matricula, dados)
    
    if funcionario_destaque:
        matricula, dados = funcionario_destaque
        salario_com_desconto = calcular_desconto_por_faltas(dados[4], maior_num_faltas)
        desconto = dados[4] - salario_com_desconto
        nome_funcionario = dados[0]
        codigo_funcionario = dados[1]
        
        print("\nInformações do Funcionário com Maior Número de Faltas:")
        print(f"Matrícula: {matricula}")
        print(f"Nome: {nome_funcionario}")
        print(f"Código do funcionário: {codigo_funcionario}")
        print(f"Número de faltas: {maior_num_faltas}")
        print(f"Desconto no Salário: R$ {desconto:.2f}")
    else:
        print("Não há funcionários cadastrados com faltas.")

opcao = 0
while opcao != 7:
    print("\nEscolha uma opção:")
    print("1 - Inserir Funcionário")
    print("2 - Remover Funcionário")
    print("3 - Calcular Folha de Pagamento")
    print("4 - Gerar Relatório")
    print("5 - Funcionário com Maior Salário Líquido")
    print("6 - Funcionário com Maior Número de Faltas")
    print("7 - Sair")

    opcao = int(input("Digite: "))
    
    if opcao == 1:
        inserir_funcionario()
    elif opcao == 2:
        matricula_remover = input("\nDigite a matrícula do funcionário que deseja remover: ")
        remover_funcionario(matricula_remover)
    elif opcao == 3:
        matricula = input("\nInforme a matrícula do funcionário: ")
        calcular_folha_pagamento(matricula)
    elif opcao == 4:
        gerar_relatorio()
    elif opcao == 5:
        funcionario_maior_salario_liquido()
    elif opcao == 6:
        funcionario_maior_num_faltas()
