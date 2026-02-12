#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>


struct Venda{
    std::string produto;
    double preco;
    int qtde;
};

void menu(){    
    std::cout << "-------------------" << std::endl;
    std::cout << "--Lista de venda--" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "-- 1- registrar  --" << std::endl;
    std::cout << "-- 2- visualizar --" << std::endl;
    std::cout << "-- 3- excluir    --" << std::endl;
    std::cout << "-- 4- Sair       --" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "- Escolha uma opção: " << std::endl;
}

void registrarVenda(){

    Venda novaVenda;
    printf("--------------------------\n");

    std::cin.ignore(1000, '\n');

    std::cout << "Produto: ";
    getline(std::cin, novaVenda.produto);
    printf("Preço: ");
    (std::cin >> novaVenda.preco);
    printf("Quantidade: ");
    (std::cin >> novaVenda.qtde);;
    printf("--------------------------\n");


    std::ofstream vendas;
    vendas.open("vendas.txt", std::ios::app);

    if(vendas.is_open()){
        vendas << " | " << novaVenda.produto << " | " << novaVenda.preco << " | " << novaVenda.qtde <<  " | " << std::endl; 
        
        vendas.close();
        printf("registro salvo!\n");
    }

    else{
        printf("ERRO");
    }

}

void visualizarVenda(){

    std::ifstream vendas("vendas.txt");
    std::string linha;
    int n = 1;

    if(vendas.is_open()){

        printf("--- LISTA DE PRODUTOS SALVOS ---\n");
        printf("----------------------------\n");

        

        while(std::getline(vendas, linha)){
            std::cout << n << "- " << linha << std::endl;
            n++;
        }
        vendas.close();
        printf("---------------\n");
        std::cin.ignore();
        std::cin.get();

    }
    else{
        printf("não encotrado");
    }
    

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
    
    }

    for(int i = alvo - 1 ; i < total - 1; i++){
        tarefas[i] = tarefas[i + 1];
    }
    total--;


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




int main(){
  
int opcao = 0;

while(opcao != 4){
   
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

}
return 0;
}