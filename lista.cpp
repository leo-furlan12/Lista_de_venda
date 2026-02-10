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
    std::cout << "-- 3- Sair       --" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "- Escolha uma opção: " << std::endl;
}

void registrarVenda(){

    Venda novaVenda;
    printf("--------------------------\n");
    printf("Produto: ");
    (std::cin >> novaVenda.produto);
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



int main(){
  
int opcao = 0;

while(opcao != 3){
   
    menu();
    scanf(" %d", &opcao);

    if(opcao == 1){
        registrarVenda();
    }

    else if(opcao == 2){
        visualizarVenda();
    }

}
return 0;
}