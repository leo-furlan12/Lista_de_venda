#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;



struct Venda{
    std::string data;
    std::string produto;
    int qtde;
    double preco;
    double custo;
    double estorno_tarifa;
    double tarifas;
    double lucro_bruto;
    double lucro_liquído;    
};

void menu(){    
    std::cout << "-------------------" << std::endl;
    std::cout << "--Lista de venda---" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "-- 1- registrar  --" << std::endl;
    std::cout << "-- 2- visualizar --" << std::endl;
    std::cout << "-- 3- excluir    --" << std::endl;
    std::cout << "-- 4- Relatório  --" << std::endl;
    std::cout << "-- 5- Sair       --" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "- Escolha uma opção: " << std::endl;
}

void registrarVenda(){

    Venda novaVenda;
    printf("--------------------------\n");

    std::cin.ignore(1000, '\n');

    std::cout << "Data (DD/MM): ";
    getline(std::cin, novaVenda.data);

    std::cout << "Produto: ";
    getline(std::cin, novaVenda.produto);


    // estrutura de quantidade
    while(true){
        printf("Quantidade: ");
        if(std::cin >> novaVenda.qtde){
            break;
        }
        else{
            printf("ERRO: Digite Valor Válido!\n");
            std::cin.clear();
            while(std::cin.get() != '\n');
        }
    }



    // estrutura de preço
    while(true){
        printf("Preço (use ponto): ");
        if (std::cin >> novaVenda.preco && std::cin.peek() == '\n'){
            break;
        }
        else{
            printf("ERRO: Digite valor válido!\n");
            std::cin.clear();
            char c;
            while (std::cin.get(c) && c != '\n');
        }
    }


    // estrutura do custo de produto
    while(true){
        printf("Custo unitário: ");
        if(std::cin >> novaVenda.custo && std::cin.peek() == '\n'){

            break;
        }
        else{
            printf("ERRO! Digite Valor Válido!\n");
            std::cin.clear();
            char c;
            while (std::cin.get(c) && c != '\n');
        }
    }


    // estrutura de estorno da tarifa
    while(true){
        printf("Estorno da tarifa: ");
        if(std::cin >> novaVenda.estorno_tarifa && std::cin.peek() == '\n'){
            break;
        }
        else{
            printf("ERRO: Digite valor válido!!\n");
            std::cin.clear();
            char c;
            while (std::cin.get(c) && c != '\n');
        }
    }


    novaVenda.custo = novaVenda.custo * novaVenda.qtde;
    novaVenda.tarifas = (6.50 * novaVenda.qtde) + (0.14 * novaVenda.preco);
    novaVenda.lucro_bruto = novaVenda.preco - novaVenda.tarifas + novaVenda.estorno_tarifa;
    novaVenda.lucro_liquído = novaVenda.lucro_bruto - novaVenda.custo;


    printf("--------------------------\n");


    std::ofstream vendas("vendas.txt", std::ios::app);
    if(vendas.is_open()){

        vendas << std::fixed << std::setprecision(2);
        
        vendas << " | " << novaVenda.data 
               << " | " << novaVenda.produto 
               << " | " << novaVenda.qtde 
               << " | " << novaVenda.preco 
               << " | " << novaVenda.custo 
               << " | " << novaVenda.tarifas 
               << " | " << novaVenda.estorno_tarifa 
               << " | " << novaVenda.lucro_bruto 
               << " | " << novaVenda.lucro_liquído
               << " | " << std::endl;

        vendas.flush();
        vendas.close();
        printf("registro salvo com sucesso!\n");
    }

    else{
        printf("ERRO");
    }

}

void visualizarVenda(){

    std::ifstream vendas("vendas.txt");
    std::string lixo, data, produto, qtde, preco, custo, tarifas, estorno, bruto, liquido;
    int n = 1;

    if(vendas.is_open()){

        std::cout << "\n" << std::string(118, '-') << std::endl;

        std::cout << std::left << std::setw(4)  << "ID"
                  << std::setw(12) << "DATA"
                  << std::setw(20) << "PRODUTO"
                  << std::setw(6)  << "QTDE"
                  << std::setw(11) << "PRECO"
                  << std::setw(11) << "CUSTO"
                  << std::setw(11) << "TARIFAS"
                  << std::setw(11) << "EXTORNO"
                  << std::setw(11) << "L. BRUTO" 
                  << std::setw(11) << "L. LIQ" << std::endl;
        std::cout << std::string(118, '-') << std::endl;
        
        while (getline(vendas, lixo, '|') && 
               getline(vendas, data, '|') && 
               getline(vendas, produto, '|') && 
               getline(vendas, qtde, '|') && 
               getline(vendas, preco, '|') && 
               getline(vendas, custo, '|') && 
               getline(vendas, tarifas, '|') && 
               getline(vendas, estorno, '|') && 
               getline(vendas, bruto, '|') && 
               getline(vendas, liquido, '|')){

                if (produto.length() > 1){

                    

                    std::cout << std::left << std::setw(4)  << n
                          << std::setw(12) << data
                          << std::setw(20) << produto
                          << std::setw(6)  << qtde
                          << std::setw(11) << preco
                          << std::setw(11) << custo
                          << std::setw(11) << tarifas
                          << std::setw(11) << estorno
                          << std::setw(11) << bruto
                          << std::setw(11) << liquido << std::endl;


                    
                    
                          n++;
            }
            getline(vendas,lixo);
        }

       
            
        
        vendas.close();
      std::cout << std::string(118, '-') << std::endl;
    }
    else{
        std::cout << "Nenhuma venda registrada ainda (arquivo nao encontrado)." << std::endl;
    }
    std::cout << "Pressione Enter para voltar...";
    
    std::cin.clear();
    if(std::cin.peek() == '\n') std::cin.ignore();
    std::cin.get();
    

}



using namespace std;
#define MAX_TAREFAS 1000



void excluirVenda(int alvo){
    
    string tarefas[MAX_TAREFAS];
    int total = 0;
    char buffer[256];


    FILE *arquivo = fopen("vendas.txt", "r");
    if(arquivo != NULL){
        while(fgets(buffer,sizeof(buffer), arquivo) && total < MAX_TAREFAS){
            tarefas[total] = buffer;
            total++;
        }
        fclose(arquivo);
    }

    if(alvo < 1 || alvo > total){
        printf("venda inexistente!!\n");
        return;
    }
    
    else{ for(int i = alvo - 1 ; i < total - 1; i++){
        tarefas[i] = tarefas[i + 1];
    }
    total--;
    }

    arquivo = fopen("vendas.txt", "w");
    if(arquivo == NULL){
        return;
    }

    for(int i = 0; i < total; i++){
        fputs(tarefas[i].c_str(), arquivo);
    }

    fclose(arquivo);
    printf("removido com sucesso!!\n");
    
}


void relatorioFinanceiro(){
    std::ifstream vendas("vendas.txt");
    
    
    std::string lixo, data, produto, qtde, preco, custoStr, tarifas, estorno, brutoStr, liquidoStr;
    

    float totalCusto = 0;
    float totalLucroBruto = 0;
    float totalLucroLiquido = 0;

    if (vendas.is_open()) {
        
    
        while (getline(vendas, lixo, '|') && 
               getline(vendas, data, '|') && 
               getline(vendas, produto, '|') && 
               getline(vendas, qtde, '|') && 
               getline(vendas, preco, '|') && 
               getline(vendas, custoStr, '|') &&    
               getline(vendas, tarifas, '|') && 
               getline(vendas, estorno, '|') && 
               getline(vendas, brutoStr, '|') &&    
               getline(vendas, liquidoStr, '|')) {  
            
           
            if (produto.length() > 1) {
                
             
                totalCusto        += atof(custoStr.c_str());
                totalLucroBruto   += atof(brutoStr.c_str());
                totalLucroLiquido += atof(liquidoStr.c_str());
            }
  
            getline(vendas, lixo); 
        }
        
        vendas.close();

        // MOSTRA O RELATÓRIO FINAL
        std::cout << "\n=========================================\n";
        std::cout << "      RELATÓRIO FINANCEIRO GERAL       \n";
        std::cout << "=========================================\n";
        std::cout << " CUSTO TOTAL INVESTIDO:  R$ " << std::fixed << std::setprecision(2) << totalCusto << "\n";
        std::cout << " LUCRO BRUTO TOTAL:      R$ " << totalLucroBruto << "\n";
        std::cout << "-----------------------------------------\n";
        std::cout << " LUCRO LÍQUIDO REAL:     R$ " << totalLucroLiquido << "\n";
        std::cout << "=========================================\n";

    } else {
        std::cout << "Erro: Arquivo de vendas não encontrado.\n";
    }

    std::cout << "\nPressione Enter para voltar ao menu...";
    std::cin.ignore();
    std::cin.get();
}
    


int main(){
  
int opcao = 0;

while(opcao != 5){
   
    menu();
    scanf(" %d", &opcao);

    if(opcao == 1){
        registrarVenda();
    }

    else if(opcao == 2){
        visualizarVenda();
    }

    else if(opcao == 3){

        int id = 0;

        visualizarVenda();
        printf("---------------\n");
        printf("qual venda deseja excluir?: \n");
        scanf("%d", &id);
        excluirVenda(id);
    }

    else if(opcao == 4){
        relatorioFinanceiro();
    }

}
return 0;
}